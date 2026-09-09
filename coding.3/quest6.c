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
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());

        exit(0);
    }

    else {
        // Parent process
        printf("Parent Process\n");
        printf("Waiting for child PID: %d\n", p);

        pid_t result = waitpid(p, NULL, 0);

        if (result < 0) {
            perror("waitpid failed");
            exit(1);
        }

        printf("waitpid() returned: %d\n", result);
        printf("Child finished\n");
    }

    return 0;
}

/* 
Output:
Parent Process
Waiting for child PID: 13245
Child Process
Child PID: 13245
waitpid() returned: 13245
Child finished
*/

/* Answer: 
    I modified the previous program to use waitpid() instead of wait(). The parent calls waitpid() with the PID returned by fork(), 
    which allows it to wait specifically for that child process. When the child finishes, waitpid() returns the child's PID.

waitpid() is useful when a parent has multiple child processes and needs to wait for a particular child rather than any child. 
It also provides additional options, such as WNOHANG, which allows the parent to check whether a child has finished without blocking.
*/