#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_PATH 1024

int main(int argc,char * argv[])
{
        char buffer[BUF_PATH];
        if(getcwd(buffer,BUF_PATH)==NULL)
        {
                perror("getcwd failed");
                exit(2);
        }
        printf("Current working directory: %s\n", buffer);

        return 0;


}
~
