#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;
    pid_t p = fork();

    if (p<0) {
        perror("Fork Failed!");
        exit(1);
    }
    
    else if (p==0) {
        // child process
        printf("child Process\n");
        printf("Value Before change %d", x);
        printf("\n");

        x = 120;
        printf("Value After change %d", x);
        printf("\n");
    }

    else {
        // parent process
        printf("Parent Process\n");
        printf("Value Before change %d", x);
        printf("\n");

        x = 80;
        printf("Value After change %d", x);
        printf("\n");
    }

   
    return 0;
}


// Answer to the question: 

/* 
Before calling fork(), the main process sets x to 100. When the child process is created, it receives its own copy of the parent's memory, 
so the value of x in the child is also 100.

When the child changes x to 120, the parent's value does not change. Similarly, when the parent changes x to 80,
the child's value remains 120. This happens because the parent and child have separate memory spaces after fork().
Although they initially contain the same value, changes made by one process do not affect the other.
*/