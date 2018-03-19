/***********************************************************************
* FILENAME : ppm.h
*
* DESCRIPTION :
* Program to read and write data of .ppm file format.
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

#ifndef IJC_PROJ1_PPM_H
#define IJC_PROJ1_PPM_H

#endif //IJC_PROJ1_PPM_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

struct ppm{
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm *ppm_read(const char *filename);
int ppm_write(struct ppm *p, const char *filename);
