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
#include <stdio.h>
#ifndef HTAB_MOVE
#define HTAB_MOVE


htab_t *htab_move(size_t newSize, htab_t *source){
    htab_t *new = NULL;
    if((new = htab_init(newSize)) != NULL){
        fprintf(stderr, "ERROR: Failed to alocate memory\n");
        return NULL;
    }

    for(size_t i = 0; i < source->arr_size; i++){
        htab_listitem *item = source->items[i];
        while(item != NULL){
            htab_lookup_add(new, item->key);
            item = item->next;
        }
    }

    htab_clear(source);
    return new;
}

#endif