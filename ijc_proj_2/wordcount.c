/***********************************************************************
* DESCRIPTION :
* Program to count words file
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
#include "htab.h"
#include "io.c"

void callback_function(char *key, unsigned int value){
    printf("%s\t%u\n", key, value);
}

int main(){
    htab_t *table = htab_init(7000);
    htab_listitem *tmp = NULL;

    int word_size = 0;
    char word[128];
    while((word_size = get_word(word, 127, stdin)) != EOF){
        if(word_size > 127) fprintf(stderr, "WARNING: Word length is over the limit (127)!\n");
        if((tmp = htab_lookup_add(table, word)) != NULL){
            tmp->data++;
        } else {
            fprintf(stderr, "ERROR: Failed to allocate memory\n");
            return -1;
        }
    }

    htab_foreach(table, &callback_function);
    htab_free(table);
    return 0;
}
