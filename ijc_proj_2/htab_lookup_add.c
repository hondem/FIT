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

#ifndef HTAB_LOOKUP_ADD
#define HTAB_LOOKUP_ADD

htab_listitem *htab_lookup_add(htab_t *t, const char *key){
    htab_listitem *item = t->items[htab_hash_function(key) % t->arr_size];
    while(item != NULL){
        if(strcmp(key, item->key) == 0) return item;
        item = item->next;
    }

    item = malloc(sizeof(htab_listitem));
    if(item == NULL) return NULL;
    item->key = malloc(sizeof(char) * (strlen(key) + 1));
    if(item->key == NULL) return NULL;

    memcpy(item->key, key, strlen(key) + 1);
    item->next = NULL;
    item->data = 0;

    htab_listitem *target = t->items[htab_hash_function(key) % t->arr_size];
    if(target == NULL){
        t->items[htab_hash_function(key) % t->arr_size] = item;
    } else {
        while(target->next != NULL) target = target->next;
        target->next = item;
    }
    t->size++;
    return item;
}

#endif