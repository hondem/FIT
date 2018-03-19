/***********************************************************************
* FILENAME : bit_array.h
*
* DESCRIPTION :
* Header file which includes macros and inline functions to handle
* bit array changes.
*
* AUTHOR : Jan Demel (xdemel01)
* START DATE : 12. 3. 2018
*
* NOTES :
* This file has been created as a part of university project. No commercial use is allowed!
*
* COMPILED :
* ﻿gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
************************************************************************/

#include <limits.h>
#include "error.h"

#ifndef IJC_PROJ1_BIT_ARRAY_H
#define IJC_PROJ1_BIT_ARRAY_H

#endif //IJC_PROJ1_BIT_ARRAY_H

typedef unsigned long bit_array_t[];

#define ULONG_SIZE (sizeof(unsigned long))

#define bit_array_create(arr_name, size) unsigned long arr_name[(1 + (size / ULONG_SIZE) + (size % ULONG_SIZE > 0 ? 1 : 0))] = {0};\
        arr_name[0] = size;

#ifdef USE_INLINE
    inline unsigned long bit_array_size(bit_array_t arr_name){
        return arr_name[0];
    }

    inline unsigned long bit_array_getbit(bit_array_t arr_name, int index){
        if(index > bit_array_size(arr_name) - 1 || index < 0){
            error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(arr_name) - 1);
        } else {
            return (unsigned long)((arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] & ((unsigned long)1 << (index % (ULONG_SIZE * CHAR_BIT))) ) > 0);
        }
        return -1;
    }

    inline void bit_array_setbit(bit_array_t arr_name, int index, int value){
        if(!(value == 1 || value == 0)) error_exit("Value: %lu je mimo povolené hodnoty 0, 1", (unsigned long)value);
        if(index > bit_array_size(arr_name) - 1 || index < 0) {
            error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(arr_name) - 1);
        } else if(value) {
            arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] |= (unsigned long)1 << (index % (ULONG_SIZE * CHAR_BIT));
        } else {
            arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] &= (unsigned long)0 << (index % (ULONG_SIZE * CHAR_BIT));
        }
    }
#else
    #define bit_array_size(arr_name) arr_name[0]

    #define bit_array_getbit(arr_name, index) \
                (index > bit_array_size(arr_name) - 1 || index < 0) ? \
                    error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(arr_name) - 1), 0 \
                : \
                    (unsigned long)((arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] & ((unsigned long)1 << (index % (ULONG_SIZE * CHAR_BIT))) ) > 0)

    #define bit_array_setbit(arr_name, index, value) \
            if(!(value == 1 || value == 0)) error_exit("Value: %lu je mimo povolené hodnoty 0, 1", (unsigned long)value); \
            if(index > bit_array_size(arr_name) - 1 || index < 0) { \
                error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(arr_name) - 1); \
            } else if(value) { \
                arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] |= (unsigned long)1 << (index % (ULONG_SIZE * CHAR_BIT)); \
            } else { \
                arr_name[index / (ULONG_SIZE * CHAR_BIT) + 1] &= (unsigned long)0 << (index % (ULONG_SIZE * CHAR_BIT)); \
            }
#endif

#define print_bit_array(arr_name) \
    printf("Values stored inside '%s': \n", #arr_name); \
    for(unsigned long i = 0; i < bit_array_size(arr_name); i++) { \
        printf("Bit %lu: %lu\n", i, bit_array_getbit(arr_name, i)); \
    }
