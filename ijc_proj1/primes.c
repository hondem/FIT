/***********************************************************************
* FILENAME : primes.c
*
* DESCRIPTION :
* Program that generates prime numbers to 222000000.
*
* AUTHOR : Jan Demel (xdemel01)
* START DATE : 14. 3. 2018
*
* NOTES :
* This file has been created as a part of university project. No commercial use is allowed!
*
* COMPILED :
* ﻿gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
************************************************************************/

#include <stdio.h>
#include "eratosthenes.h"

int main(){
    bit_array_create(pole, 222000000L);
    Eratosthenes(pole);

    int foundNumbers = 0;
    unsigned long numbers[10];

    unsigned long array_index = bit_array_size(pole) - 1;

    while(foundNumbers != 10){
        if(bit_array_getbit(pole, array_index) == 0){
            numbers[9 - foundNumbers] = array_index;
            foundNumbers++;
        }
        array_index--;
    }

    for(int i = 0; i < 10; i++){
        printf("%lu\n", numbers[i]);
    }

    return 0;
}
