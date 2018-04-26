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

#include <iostream>
#include <stdio.h>
#include "tail2.h"

#define E_BAD_ARGS -1
#define E_FAILED_TO_OPEN_FILE -2
#define E_N_GT_ZERO -3

#define FATAL_ERROR(error_message, error_code) \
    do{ \
        fprintf(stderr, error_message); \
        return error_code; \
    } while(1); \

using namespace std;

int main(int argc, char *argv[]){
    unsigned short mode = 0;

    if(argc == 1){ // ./tail2
        mode = 1;
    } else if(argc == 3 && strcmp(argv[1], "-n") == 0){ // ./tail2 -n <int>
        mode = 2;
    } else if(argc == 2){ // ./tail2 <file>
        mode = 3;
    } else if(argc == 4 && strcmp(argv[1], "-n") == 0){ // ./tail2 -n <int> <file>
        mode = 4;
    } else {
        FATAL_ERROR("ERROR: Bad argments passed\n", E_BAD_ARGS);
    }

    vector<string> buffer;

    if(mode == 1){
        loadIntoBuffer(buffer, cin);
        printStringVector(buffer, ((int)(buffer.size() - 10) >= 0) ? buffer.size() - 10 : 0, buffer.size());

    } else if(mode == 2){
        int lineAmount = atoi(argv[2]);
        if(lineAmount <= 0) FATAL_ERROR("ERROR: -n parameter has to be greater than 0\n", E_N_GT_ZERO);

        loadIntoBuffer(buffer, cin);
        printStringVector(buffer, ((int)(buffer.size() - lineAmount) >= 0) ? buffer.size() - lineAmount : 0, buffer.size());

    } else if(mode == 3){

        ifstream file;
        file.open(argv[1]);

        if(file.is_open()){
            loadIntoBuffer(buffer, file);
            file.close();
            printStringVector(buffer, ((int)(buffer.size() - 10) >= 0) ? buffer.size() - 10 : 0, buffer.size());

        } else {
            FATAL_ERROR("ERROR: Failed to open file\n", E_FAILED_TO_OPEN_FILE);
        }

    } else if(mode == 4){
        int lineAmount = atoi(argv[2]);
        if(lineAmount <= 0) FATAL_ERROR("ERROR: -n parameter has to be greater than 0\n", E_N_GT_ZERO);
        ifstream file;
        file.open(argv[3]);

        if(file.is_open()){
            loadIntoBuffer(buffer, file);
            file.close();
            printStringVector(buffer, ((int)(buffer.size() - lineAmount) >= 0) ? buffer.size() - lineAmount : 0, buffer.size());
        } else {
            FATAL_ERROR("ERROR: Failed to open file\n", E_FAILED_TO_OPEN_FILE);
        }
    }
    return 0;
}

void printStringVector(vector<string> data, int from_index, int to_index){
    for(int i = from_index; i < to_index; i++){
        printf("%s\n", data[i].c_str());
    }
}

void loadIntoBuffer(vector<string> &buffer, istream &is){
    string line;
    getline(is, line);
    while(line.length() > 0){
        buffer.push_back(line);
        getline(is, line);
    }
}

void loadIntoBuffer(vector<string> &buffer, ifstream &is){
    string line;
    getline(is, line);
    while(line.length() > 0){
        buffer.push_back(line);
        getline(is, line);
    }
}
