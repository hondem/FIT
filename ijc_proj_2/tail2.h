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

#ifndef IJC_PROJ_2_TAIL2_H
#define IJC_PROJ_2_TAIL2_H

#endif //IJC_PROJ_2_TAIL2_H

#include <vector>
#include <string.h>
#include <fstream>

void printStringVector(std::vector<std::string> data, int from_index, int to_index);

void loadIntoBuffer(std::vector<std::string> &buffer, std::istream& is);
void loadIntoBuffer(std::vector<std::string> &buffer, std::ifstream& is);
