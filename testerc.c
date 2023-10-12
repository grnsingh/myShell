#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(){
    char buffer[1024];
    char* parsedinput;
    char* firstWord;
    char* args[3];
    char newline;
    while(1){
        printf("$ ");
        char *input = fgets(buffer, sizeof(buffer), stdin);
        if(!input)
        {
            fprintf(stderr, "Error reading input\n");
            return -1;
        }

        parsedinput = (char*) malloc(1024 * sizeof(char));
        size_t parselength = trimstring(parsedinput, input, 1024);
        printf("%s\n", findpipe(parsedinput,1024) ? "true" : "false");

        printf("-----------------------------------------------\n");
    }
    
}