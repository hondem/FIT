#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tail.h"

#define E_BAD_ARGS -1

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
        fprintf(stderr, "CHYBA: Spatny format argument\n");
        return E_BAD_ARGS;
    }

    if(mode == 1){
        char buffer[11];
        readLine(buffer, 11, stdin);
        printf("%s\n", buffer);
    } else if(mode == 2){

    } else if(mode == 3){

    } else if(mode == 4){

    }


    return 0;
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
        }
    }
    return charsOnLine;
}

void clearArray(char *array, int length){
    for(int i = 0; i < length; i++){
        array[i] = 0;
    }
}
