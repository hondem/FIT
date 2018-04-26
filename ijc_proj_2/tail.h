/***********************************************************************
* DESCRIPTION :
* Program that outputs n last lines of file
*
* AUTHOR : Jan Demel (xdemel01)
* START DATE : 10. 4. 2018
*
* NOTES :
* This file has been created as a part of university project. No commercial use is allowed!
*
* COMPILED :
* ﻿gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
************************************************************************/

#include <stdbool.h>

#ifndef IJC_PROJ_2_TAIL_H
#define IJC_PROJ_2_TAIL_H

#endif //IJC_PROJ_2_TAIL_H

int readLine(char *dest, int charsAmount, FILE *stream);
void clearArray(char *array, int length);
bool isArrayEmpty(char *array, int length);
void shiftList(char **list, int listLength);
void freeList(char **list, int listLength);
void readLines(char **list, int listLength, int charsAmount, FILE *stream);
void printList(char **list, int listLength, int charsAmount);
void processData(int linesAmount, int charsAmount, FILE *stream);
