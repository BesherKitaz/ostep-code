#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void) {
    // Open the file before calling fork()
    int fh = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fh < 0) {
        perror("Open failed");
        exit(1);
    }

    pid_t p = fork();

    if (p < 0) {
        perror("Fork failed");
        close(fh);
        exit(1);
    }

    else if (p == 0) {
        // Child process
        printf("Child Process\n");

        for (int i = 0; i < 5; i++) {
            write(fh, "Child\n", 6);
        }
    }

    else {
        // Parent process
        printf("Parent Process\n");

        for (int i = 0; i < 5; i++) {
            write(fh, "Parent\n", 7);
        }
    }

    close(fh);
    return 0;
}

// Answer to the question:

/* 
Yes, both the child and parent can access the file descriptor returned by open() because the file is opened before fork() is called. 
The child inherits the parent's open file descriptor, and both processes refer to the same underlying open file description.

When both processes write to the file, their writes can occur in different orders depending on how the operating system schedules them. 
For example, some parent writes may appear before child writes, or the writes may alternate. 
Both processes share the file offset, so each write advances the position in the file. 
The resulting file contains the data written by both processes, but the order is not guaranteed unless synchronization is used.
*/