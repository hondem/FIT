/***********************************************************************
* DESCRIPTION :
* Reads word from given file input
*
* AUTHOR : Jan Demel (xdemel01)
* START DATE : 21. 4. 2018
*
* NOTES :
* This file has been created as a part of university project. No commercial use is allowed!
*
* COMPILED :
* ﻿gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
************************************************************************/

#include <stdio.h>
#include <ctype.h>

#ifndef IO_OPERATIONS
#define IO_OPERATIONS

void clear_word(char *s, int length){
    for(int i = 0; i < length; i++){
        s[i] = 0;
    }
}

int get_word(char *s, int max, FILE *f){
    int c, charCount = 0;
    c = fgetc(f);

    while(isspace(c)){
        c = fgetc(f);
    }

    if(c != EOF){
        clear_word(s, max + 1);
        for(int i = 0; i < max; i++){
            s[i] = c;
            c = fgetc(f);
            if(isspace(c)){
                break;
            } else {
                charCount++;
            }
        }
    } else {
        return EOF;
    }
    return charCount;
}
#endif