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

        int child_wait = wait(NULL);

        printf("wait() in child returned: %d\n", child_wait);
        perror("Child wait");

        exit(0);
    }

    else {
        // Parent process
        printf("Parent Process\n");
        printf("Child PID: %d\n", p);

        int parent_wait = wait(NULL);

        printf("wait() in parent returned: %d\n", parent_wait);
    }

    return 0;
}


/* 
Output from terminal: 
Parent Process
Child PID: 12345
Child Process
Child PID: 12345
wait() in child returned: -1
Child wait: No child processes
wait() in parent returned: 12345
*/

/* Answer:
I wrote a program that calls fork() and then uses wait() in both the parent and child processes. 
In the parent, wait() blocks until the child process finishes and then returns the PID of the terminated child.

When I called wait() in the child process, it returned -1 because the child had no child processes of its own to wait for. 
The error was "No child processes." This shows that wait() can only wait for child processes belonging to the process that calls it. 
It cannot be used by the child to wait for its parent.
*/