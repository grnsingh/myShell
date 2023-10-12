#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"

#define BUFLEN 1024

typedef struct {
    pid_t pid;
    int status; 
} BackgroundProcess;

int main() {
    char buffer[1024];
    char* parsedinput;
    char* firstWord;
    char* firstArgument;
    char* secondArgument;
    char* args[9];
    char* path;
    char* pathToGo;

    BackgroundProcess* backgroundProcesses = NULL;
    int numBackgroundProcesses = 0;

    printf("Welcome to the Group13 shell! Enter commands, enter 'quit' to exit\n");
    do {
        int i = 0;
        while (i < numBackgroundProcesses) {
            pid_t terminated_pid = waitpid(backgroundProcesses[i].pid, NULL, WNOHANG);
            if (terminated_pid > 0) {
                for (int j = i; j < numBackgroundProcesses - 1; ++j) {
                    backgroundProcesses[j] = backgroundProcesses[j + 1];
                }
                numBackgroundProcesses--;
                backgroundProcesses = realloc(backgroundProcesses, numBackgroundProcesses * sizeof(BackgroundProcess));
                printf("Background process %d terminated.\n", terminated_pid);

            } else {
                i++;
            }
        }
        printf("$ ");
        char *input = fgets(buffer, sizeof(buffer), stdin);
        if(!input)
        {
            fprintf(stderr, "Error reading input\n");
            return -1;
        }


        parsedinput = (char*) malloc(BUFLEN * sizeof(char));
        path = (char*) malloc(BUFLEN * sizeof(char));
        firstWord = (char*) malloc(1024 * sizeof(char));
        pathToGo = (char*) malloc(1024 * sizeof(char));

        trimstring(parsedinput, input, BUFLEN);

        int pipe = findpipe(parsedinput, BUFLEN);

        int bgRun = (runinbackground(parsedinput, 1024) ? 1 : 0);

        wordFinder(firstWord, parsedinput, 1024, 1);
        // wordFinder(firstArgument, parsedinput, 1024, 2);
        // wordFinder(secondArgument, parsedinput, 1024, 3);

         if(firstWord[0]!='/'){
            strncpy(path,getenv("PATH"),1024*sizeof(char));
            char* token = strtok(path, ":");
            while(token != NULL){
                strncpy(pathToGo,token,1024*sizeof(char));
                strncat(pathToGo,"/",1024*sizeof(char));
                strncat(pathToGo,firstWord,1024*sizeof(char));
                if(access(pathToGo, X_OK) == 0) {
                    // printf("Found at %s\n",pathToGo);
                    break;
                }
                token = strtok(NULL, ":");
            }}
            else{
                strncpy(pathToGo,firstWord,BUFLEN);
            }
        args[0] = pathToGo;
        for(int i =1; i<10; i++){
            args[i] = (char*)malloc(BUFLEN*sizeof(char));
            wordFinder(args[i], parsedinput, 1024, i+1);
            // if(strlen(args[i])!=0)
            // printf("%s\n",args[i]);
            if(strlen(args[i]) == 0){
                args[i] = NULL;
            }
        }
       
        if ( strcmp(parsedinput, "quit") == 0 ) {
            
            if(backgroundProcesses!= NULL){
                free(backgroundProcesses);
            }
            if (parsedinput != NULL) {
                free(parsedinput);
            }
            if (path != NULL) {
                free(path);
            }
            if (firstWord != NULL) {
                free(firstWord);
            }
            if (pathToGo != NULL) {
                free(pathToGo);
            }
            for (int i = 1; i < 10; i++) {
                if (args[i] != NULL) {
                    free(args[i]);
                }
            }
            printf("Bye!!\n");
            return 0;
        }

        if (bgRun) {
            // BG RUN
            pid_t forkV = fork();
            if (forkV == 0) {
                if (execvp(args[0], args) == -1) {
                    fprintf(stderr, "Error running command in execvp\n");
                    return -1;
                }
            } else {
                backgroundProcesses = realloc(backgroundProcesses, (numBackgroundProcesses + 1) * sizeof(BackgroundProcess));
                backgroundProcesses[numBackgroundProcesses].pid = forkV;
                backgroundProcesses[numBackgroundProcesses].status = 1; 
                numBackgroundProcesses++;
            }
        } 
        // NOTE : PIPES DONOT WORK , ONLY PART WITH SEGMENTATION FAULT :(
        // else if(pipe){
        //     int pos =-1;
        //     for(int i =1; i< 9 ; i++){
        //         if(!strcmp(args[i],"|")){
        //             pos = i;
        //         }
        //     }
        //     // char* rightSide[10 - pos][BUFLEN];
        //     // for(int i = pos; i < 10; i++){
        //     //     strcpy(rightSide[i - pos], args[i]);
        //     //     printf("%s\n", rightSide[i - pos]);
        //     // }
        //     pid_t forkV = fork();

        //     if (forkV == 0) {
        //         // write into the pipe
        //     }
        //     else{
        //         waitpid(forkV, NULL, 0);
        //     }
            

        // }
        else {
            pid_t forkV = fork();
            if (forkV == 0) {
                if (execvp(args[0], args) == -1) {
                    fprintf(stderr, "Error running command in execvp\n");
                    return -1;
                }
            } else {
                waitpid(forkV, NULL, 0); 
            }
        }
            if (parsedinput != NULL) {
                free(parsedinput);
            }
            if (path != NULL) {
                free(path);
            }
            if (firstWord != NULL) {
                free(firstWord);
            }
            if (pathToGo != NULL) {
                free(pathToGo);
            }
            for (int i = 1; i < 10; i++) {
                if (args[i] != NULL) {
                    free(args[i]);
                }
            }
    } while (1);
    if(backgroundProcesses!= NULL)
    free(backgroundProcesses);
    return 0;
}
