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

#ifndef IJC_PROJ_2_HTAB_H
#define IJC_PROJ_2_HTAB_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct htab_listitem{
    char *key;
    unsigned data;
    struct htab_listitem *next;
} htab_listitem;

typedef struct htab_t{
    size_t size;
    size_t arr_size;
    htab_listitem **items;
} htab_t;

htab_t *htab_init(size_t size);
htab_t *htab_move(size_t newSize, htab_t *source);

size_t htab_size(htab_t *table);
size_t htab_bucket_count(htab_t *table);

htab_listitem *htab_lookup_add(htab_t *t, const char *key);
htab_listitem *htab_find(htab_t *t, const char *key);

unsigned int htab_hash_function(const char *str);

bool htab_remove(htab_t *t, char *key);

void htab_free(htab_t *table);
void htab_free_listitem(htab_listitem *item);
void htab_clear(htab_t *table);
void htab_foreach(htab_t *table, void (*callback)(char *key, unsigned int value));

#endif //IJC_PROJ_2_HTAB_H
