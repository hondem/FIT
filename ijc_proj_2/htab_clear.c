/***********************************************************************
* DESCRIPTION :
* HTAB library + functions
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

#include "htab.h"

#ifndef HTAB_CLEAR
#define HTAB_CLEAR

void htab_clear(htab_t *table){
    htab_listitem *tmp = NULL;
    for(size_t i = 0; i < table->arr_size; i++){
        if(table->items[i] != NULL){
            do{
                tmp = table->items[i]->next;
                htab_remove(table, table->items[i]->key);
            } while(tmp != NULL);
        }
    }
}

#endif