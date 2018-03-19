/***********************************************************************
* FILENAME : steg-decode.c
*
* DESCRIPTION :
* Decrypts message stored inside .ppm picture
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
#include "ppm.h"
#include "eratosthenes.h"

int main(int argc, char *argv[]){
    struct ppm *picture;
    picture = ppm_read(argv[1]);

    bit_array_create(prime_numbers, 204480L);

    Eratosthenes(prime_numbers);

    int c = 0;
    int bit_offset = 0;

    for (unsigned long i = 11; i < 204480L; i++) {
        if(bit_array_getbit(prime_numbers, i) == 0){
            int bit_to_write = (picture->data[i] & 1);

            if(bit_to_write == 0){
                bit_to_write = ~(1 << bit_offset);
                c &= bit_to_write;
            } else {
                bit_to_write <<= bit_offset;
                c |= bit_to_write;
            }

            if(bit_offset == 7){
                if(c == 0) return 0;
                bit_offset = 0;
                putchar(c);
                c = 0;
            } else {
                bit_offset++;
            }
        }
    }

    return 0;
}
