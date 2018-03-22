/***********************************************************************
* FILENAME : eratosthenes.c
*
* DESCRIPTION :
* Program to generate prime numbers from bit_array_t
* Part A
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

#include <math.h>
#include "eratosthenes.h"

void Eratosthenes(bit_array_t array){
    unsigned long array_size = bit_array_size(array);
    double maxIterations = sqrt(array_size);

    for(unsigned long i = 2; i < maxIterations; i++){
        if(bit_array_getbit(array, i) == 0){
            for(unsigned long y = 2; y * i < array_size; y++){
                bit_array_setbit(array, y * i, 1);
            }
        }
    }
}
