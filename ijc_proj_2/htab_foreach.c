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

#ifndef HTAB_FOREACH
#define HTAB_FOREACH

void htab_foreach(htab_t *table, void (*callback)(char *key, unsigned int value)){
    htab_listitem *item;
    for(size_t i = 0; i < table->arr_size; i++){
        item = table->items[i];
        while(item != NULL){
            callback(item->key, item->data);
            item = item->next;
        }
    }
}

#endif