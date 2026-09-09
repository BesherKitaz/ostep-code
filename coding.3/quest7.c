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
        close(STDOUT_FILENO);

        printf("Hello from child\n");
        fflush(stdout);

        exit(0);
    }

    else {
        // Parent process
        wait(NULL);
        printf("Hello from parent\n");
    }

    return 0;
}

/* Output:
Hello from parent
*/

/* 
I wrote a program that creates a child process and then closes STDOUT_FILENO in the child. 
After closing standard output, the child calls printf() to print a message.
The child's message does not appear in the terminal because standard output is closed.
Although printf() may initially place the text in a buffer, the attempt to write it to the closed descriptor fails. 
The parent can still print normally because the parent and child have separate file descriptor tables after fork(). 
Closing standard output in the child does not affect the parent's standard output.
*/