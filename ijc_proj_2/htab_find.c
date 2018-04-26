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

#ifndef HTAB_FIND
#define HTAB_FIND

htab_listitem *htab_find(htab_t *t, const char *key){
    htab_listitem *item = t->items[htab_hash_function(key) % t->arr_size];
    while(item != NULL){
        if(strcmp(key, item->key) == 0) return item;
        item = item->next;
    }
    return NULL;
}

#endif