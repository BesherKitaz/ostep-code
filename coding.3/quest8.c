#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pipefd[2];

    // Create the pipe
    if (pipe(pipefd) < 0) {
        perror("Pipe failed");
        exit(1);
    }

    // Create the first child
    pid_t p1 = fork();

    if (p1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (p1 == 0) {
        // First child: writes to the pipe

        close(pipefd[0]);  // Close unused read end

        // Connect standard output to the pipe's write end
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("ls", "ls", (char *)NULL);

        perror("execlp failed");
        exit(1);
    }

    // Create the second child
    pid_t p2 = fork();

    if (p2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (p2 == 0) {
        // Second child: reads from the pipe

        close(pipefd[1]);  // Close unused write end

        // Connect standard input to the pipe's read end
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);

        execlp("wc", "wc", "-l", (char *)NULL);

        perror("execlp failed");
        exit(1);
    }

    // Parent does not need either end of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}


