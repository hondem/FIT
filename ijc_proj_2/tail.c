#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tail.h"

#define E_BAD_ARGS -1
#define E_N_NOT_G -2

#define FATAL_ERROR(error_message, error_code) \
    fprintf(stderr, error_message); \
    return error_code;

#define DEF_CHARSAMOUNT 1024
#define DEF_LINESAMOUNT 10

int main(int argc, char *argv[]){
    unsigned short mode = 0;

    if(argc == 1){ // ./tail
        mode = 1;
    } else if(argc == 3 && strcmp(argv[1], "-n") == 0){ // ./tail -n <int>
        mode = 2;
    } else if(argc == 2){ // ./tail <file>
        mode = 3;
    } else if(argc == 4 && strcmp(argv[1], "-n") == 0){ // ./tail -n <int> <file>
        mode = 4;
    } else {
        FATAL_ERROR("ERROR: Bad argments passed\n", E_BAD_ARGS);
    }

    if(mode == 1){
        processData(DEF_LINESAMOUNT, DEF_CHARSAMOUNT, stdin);
    } else if(mode == 2){
        int lineAmount;
        if((lineAmount = atoi(argv[2])) > 0){
            char **buffer = NULL;
            buffer = malloc((lineAmount + 1) * sizeof(char*));
            readLines(buffer, (lineAmount + 1), (DEF_CHARSAMOUNT + 1), stdin);
            printList(buffer, lineAmount, DEF_CHARSAMOUNT);
            freeList(buffer, lineAmount);
        } else {
            FATAL_ERROR("ERROR: -n param must be greater than 0\n", E_N_NOT_G);
        }
    } else if(mode == 3){
        char **buffer = NULL;
        buffer = malloc((DEF_LINESAMOUNT + 1) * sizeof(char*));
        FILE *file = fopen(argv[1], "r");
        readLines(buffer, (DEF_LINESAMOUNT + 1), (DEF_CHARSAMOUNT + 1), file);
        fclose(file);
        printList(buffer, DEF_LINESAMOUNT, DEF_CHARSAMOUNT);
        freeList(buffer, DEF_LINESAMOUNT);
    } else if(mode == 4){
        int lineAmount;
        if((lineAmount = atoi(argv[2])) > 0){
            char **buffer = NULL;
            buffer = malloc((lineAmount + 1) * sizeof(char*));
            FILE *file = fopen(argv[3], "r");
            readLines(buffer, (lineAmount + 1), (DEF_CHARSAMOUNT + 1), file);
            fclose(file);
            printList(buffer, lineAmount, DEF_CHARSAMOUNT);
            freeList(buffer, lineAmount);
        } else {
            FATAL_ERROR("ERROR: -n param must be greater than 0\n", E_N_NOT_G);
        }
    }

    return 0;
}

void readLines(char **list, int listLength, int charsAmount, FILE *stream){
    for(int i = 0; i < listLength; i++){
        list[i] = malloc(charsAmount * sizeof(char));
        int charsOnLine = readLine(list[i], charsAmount, stream);
        if(charsOnLine > charsAmount - 1) fprintf(stderr, "WARNING: More characters on line, than allowed (1024)\n");
        if(!isArrayEmpty(list[i], charsAmount) && i == listLength - 1){
            shiftList(list, listLength);
            list[i--] = malloc(charsAmount * sizeof(char));
        }
    }
}

int readLine(char *dest, int charsAmount, FILE *stream){
    clearArray(dest, charsAmount);
    int c, charsOnLine = 0, readChars = 0;
    while((c = fgetc(stream)) != EOF){
        if(c != '\n'){
            if(readChars < charsAmount - 1){
                dest[readChars++] = (char)c;
            }
            charsOnLine++;
        } else {
            break;
        }
    }
    return charsOnLine;
}

void clearArray(char *array, int length){
    for(int i = 0; i < length; i++){
        array[i] = 0;
    }
}

void printList(char **list, int listLength, int charsAmount){
    for(int i = 0; i < listLength; i++){
        if(!isArrayEmpty(list[i], charsAmount)) printf("%s\n", list[i]);
    }
}

bool isArrayEmpty(char *array, int length){
    bool isEmpty = true;
    for(int i = 0; i < length; i++){
        if(array[i] != 0){
            isEmpty = false;
            break;
        }
    }
    return isEmpty;
}

void shiftList(char **list, int listLength){
    free(list[0]);
    for(int i = 0; i < listLength - 1; i++){
        list[i] = list[i + 1];
    }
}

void freeList(char **list, int listLength){
    for(int i = 0; i < listLength; i++){
        free(list[i]);
    }
    free(list);
}

void processData(int linesAmount, int charsAmount, FILE *stream){
    char **buffer = NULL;
    buffer = malloc((linesAmount + 1) * sizeof(char*));
    readLines(buffer, (linesAmount + 1), (charsAmount + 1), stream);
    printList(buffer, linesAmount, charsAmount);
    freeList(buffer, linesAmount);
}
