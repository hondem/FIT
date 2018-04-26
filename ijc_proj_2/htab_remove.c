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

#ifndef HTAB_REMOVE
#define HTAB_REMOVE

bool htab_remove(htab_t *t, char *key){
    bool retValue = false;
    unsigned index = htab_hash_function(key) % t->arr_size;
    htab_listitem *item = t->items[index];
    htab_listitem *tmp = NULL;

    /* Removing item on beginning of list at certain pointer */
    if(item != NULL && strcmp(item->key, key) == 0){
        tmp = item->next;
        htab_free_listitem(item);
        t->items[index] = tmp;
        item = NULL;
        t->size--;
        return true;
    } else if(item == NULL){
        return false;
    }

    tmp = item;
    item = item->next;

    while(item != NULL){
        if(strcmp(item->key, key) == 0){
            tmp->next = item->next;
            htab_free_listitem(item);
            retValue = true;
            break;
        }
        tmp = item;
        item = item->next;
    }

    return retValue;
}

#endif