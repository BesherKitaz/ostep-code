#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t p = fork();

    if (p < 0) {

        perror("Fork failed");
        exit(1);
    }

    else if (p == 0) {
        // Child process
        printf("Child process: running ls\n");

        execl("/bin/ls", "ls", NULL);

        // This only runs if execl() fails
        perror("execl failed");
        exit(1);
    }

    else {
        // Parent process
        wait(NULL);
        printf("Parent process: child finished\n");
    }

    return 0;
}