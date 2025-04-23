#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int femtoshell_main(int argc, char *argv[]) {
    char input[10240];
    char command[10240];
    
    while (1) {
        printf("Femto shell prompt > ");
        
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            return 0;
        }
        
        size_t len = strcspn(input, "\n");
        input[len] = '\0';
        
        if (len == 0) {
            printf("\n");
            continue;
        }
        
        int i = 0;
        while (i < len && input[i] != ' ' && input[i] != '\0') {
            command[i] = input[i];
            i++;
        }
        command[i] = '\0';
        
        if (strcmp(command, "exit") == 0) {
            printf("\nGood Bye\n");
            return 0;
        }
        else if (strcmp(command, "echo") == 0) {
            if (i + 1 < len) {
                printf("\n%s\n", &input[i + 1]);
            } else {
                printf("\n\n");
            }
        }
        else if (i < len && input[i] == ' ') {
            printf("\nInvalid command\n");
        }
        else {
            printf("\n%s\n", input);
        }
    }
    
    return 0;
}
