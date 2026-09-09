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
        printf("hello\n");
    }

    else {
        // Parent process
        wait(NULL);
        printf("goodbye\n");
    }

    return 0;
}


/* I struggled to do it without wait, but I believe there is some way to do it */