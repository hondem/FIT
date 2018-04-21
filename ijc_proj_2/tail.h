//
// Created by Jan Demel on 18.04.18.
//

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
