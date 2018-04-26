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

#ifndef HTAB_INIT
#define HTAB_INIT

htab_t *htab_init(size_t size){
    htab_t *table = malloc(sizeof(htab_t));
    if(table == NULL) return table;

    table->items = malloc(size * sizeof(htab_listitem*));
    table->size = 0;
    table->arr_size = size;
    for(size_t i = 0; i < table->arr_size; i++){
        table->items[i] = NULL;
    }
    return table;
}

#endif
