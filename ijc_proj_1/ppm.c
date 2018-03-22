/***********************************************************************
* FILENAME : ppm.c
*
* DESCRIPTION :
* Program to read and write data of .ppm file format.
* Part B
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

#include "ppm.h"


struct ppm *ppm_read(const char *filename){
    FILE *picture;
    unsigned width, height, maxcolor;

    picture = fopen(filename, "r");

    if(picture == NULL){
        warning_msg("File failed to read!");
        return NULL;
    } else if(fscanf(picture, "P6 %u %u %u ", &width, &height, &maxcolor) != 3){
        fclose(picture);
        warning_msg("Bad file header!");
        return NULL;
    }

    if(width <= 0 || height <= 0 || maxcolor > 255){
        fclose(picture);
        warning_msg("File header contains non-valid numbers!");
        return NULL;
    }

    unsigned long size = width * height * 3 * sizeof(char);

    if(size > 3000000 * sizeof(char)) error_exit("Max image resolution is 1000px x 1000px!");

    struct ppm *image = malloc(size + sizeof(struct ppm));
    image->xsize = width;
    image->ysize = height;

    if(image == NULL){
        fclose(picture);
        warning_msg("Internal error - memory allocation failed!");
        return NULL;
    }

    int readedValues = fread(&image->data, sizeof(char), size, picture);
    if(ferror(picture) || fgetc(picture) != EOF || readedValues != size){
        fclose(picture);
        warning_msg("File format error!");
        return NULL;
    }

    fclose(picture);
    return image;
}

int ppm_write(struct ppm *p, const char *filename)
{
    FILE *fileToWrite;
    int wroteNumbers;

    fileToWrite = fopen(filename, "wb");
    if(fileToWrite == NULL){
        warning_msg("Failed to create a file");
        return -1;
    }

    wroteNumbers = fprintf(fileToWrite, "P6\n%u %u\n255\n", p->xsize, p->ysize);

    if(wroteNumbers < 0){
        warning_msg("Failed to write a header");
        fclose(fileToWrite);
        return -1;
    }

    unsigned long size = p->xsize * p->ysize * sizeof(char) * 3;

    wroteNumbers = fwrite(p->data, sizeof(char), size, fileToWrite);
    if(wroteNumbers != size){
        warning_msg("Failed to write data to the image");
        fclose(fileToWrite);
        return -1;
    }
    fclose(fileToWrite);
    return 0;
}
