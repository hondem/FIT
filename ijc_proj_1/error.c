/***********************************************************************
* FILENAME : error.c
*
* DESCRIPTION :
* Program to handle any errors and warnings.
* Part B
*
* AUTHOR : Jan Demel (xdemel01)
* START DATE : 11. 3. 2018
*
* NOTES :
* This file has been created as a part of university project. No commercial use is allowed!
*
* COMPILED :
* ﻿gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
************************************************************************/

#include "error.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void error_exit(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);

    fprintf(stderr,"ERROR: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(1);
}

void warning_msg(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);

    fprintf(stderr,"WARNING: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}
