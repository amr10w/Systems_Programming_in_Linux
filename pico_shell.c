#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    while (1) {

        int numargs = 0;


        printf("Pico shell prompt > ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = 0;
        if (strlen(buf) == 0)
            continue;
        //Count the number of Args:
        char *buftemp = strdup(buf);
        char *tokentemp = strtok(buftemp, " ");
        while (buftemp != NULL) {
            buftemp = strtok(NULL, " '");
            numargs++;

        }

        char *token = strtok(buf, " '");

        if (!strcmp(token, "echo")) {
            while (token != NULL) {
                token = strtok(NULL, " ");
                if (token != NULL)
                    // printf("%s \n", token);
                {
                    write(1, token, strlen(token));
                    write(1, " ", 1);
                }
  }
            printf("\n\r");
        } else if (!strcmp(token, "exit")) {
            printf("bye bye friend\n");
            exit(0);
        } else if (!strcmp(token, "pwd")) {
            char cwd[1024];

            getcwd(cwd, sizeof(cwd));

            write(1, cwd, strlen(cwd));
            write(1, "\n", 1);
        } else if (!strcmp(token, "cd")) {

            if (numargs == 1) {

                chdir(getenv("HOME"));
                continue;
            }
else if (numargs == 2 && buf[3] == '/') {

                chdir("/");
                continue;
            }
            while (token != NULL) {
                token = strtok(NULL, " /");

                if (token != 0 && strcmp(token, "~") == 0) {

                    chdir(getenv("HOME"));

                } else if (token != 0 && (chdir(token) != 0)) {
                    char cwd[1024];
                    printf("pico shell:cd: %s: %s\n", getcwd(cwd, 100),
                           strerror(errno));
                    break;
                }
            }
 } else {
            pid_t pid = fork();
            if (pid > 0) {
                int status;
                wait(&status);
                WEXITSTATUS(status);
            } else if (pid == 0) {

                char **newargv = malloc(sizeof(char *) * (numargs + 1));
                // Tokenize the buffer
                char *cmd = token;

                int i = 0;      // Index for newargv
                while (token != NULL) {
                    newargv[i++] = token;
                    token = strtok(NULL, " '"); // Get the next token
                }
                newargv[i] = NULL;

                execvp(cmd, newargv);
printf("Exec failed\n");
                exit(-1);
            } else {
                printf("failed to fork\n");
            }
        }
    }
}
                                                             

