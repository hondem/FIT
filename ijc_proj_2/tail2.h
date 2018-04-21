#ifndef IJC_PROJ_2_TAIL2_H
#define IJC_PROJ_2_TAIL2_H

#endif //IJC_PROJ_2_TAIL2_H

#include <vector>
#include <string>
#include <fstream>

void printStringVector(std::vector<std::string> data, int from_index, int to_index);

void loadIntoBuffer(std::vector<std::string> &buffer, std::istream& is);
void loadIntoBuffer(std::vector<std::string> &buffer, std::ifstream& is);
