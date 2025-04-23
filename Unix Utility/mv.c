#include <unistd.h>    // for read(), write(), close()
#include <stdio.h>     // for perror()
#include <stdlib.h>    // for exit()
#include <fcntl.h>     // for open()
#include <string.h>    // for strlen()

#define MAX_READ 1024
#define NUM_FILE_NAME 1024

int main() {
    char a[NUM_FILE_NAME] = "";
    char b[NUM_FILE_NAME] = "";
    int fd_src, fd_dest;
    ssize_t bytesRead;
    char buffer[MAX_READ];

    printf("mv ");
    scanf("%s %s", a, b);

    if (strlen(a) == 0 || strlen(b) == 0) {
        fprintf(stderr, "File names cannot be empty\n");
        exit(EXIT_FAILURE);
    }

    fd_src = open(a, O_RDONLY);
    if (fd_src < 0) {
        perror("open source");
        exit(EXIT_FAILURE);
    }

    fd_dest = open(b, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("open destination");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    // Copy the contents from the source to the destination
    while ((bytesRead = read(fd_src, buffer, MAX_READ)) > 0) {
        if (write(fd_dest, buffer, bytesRead) != bytesRead) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            exit(EXIT_FAILURE);
        }
    }

    // Handle read errors
    if (bytesRead == -1) {
        perror("read");
        close(fd_src);
        close(fd_dest);
        exit(EXIT_FAILURE);
    }

   
    if (close(fd_src) == -1) {
        perror("close source");
    }
    if (close(fd_dest) == -1) {
        perror("close destination");
    }

    
    if (remove(a) != 0) {
        perror("remove source file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
