//
// Created by Jan Demel on 16/10/2019.
//

#ifndef ISA_PROJECT_ARG_PARSER_H
#define ISA_PROJECT_ARG_PARSER_H

#include <string>
using namespace std;

/**
 * Structure for parsed arguments
 */
struct Arguments {
    string server;
    string interface;
    bool log;
    bool debug;
};

/**
 * Class for parsing arguments from CLI
 */
class arg_parser {
public:
    static Arguments Parse(int, char**);
    static void DumpArguments(Arguments&);
    static bool isIPV6Address(char*);
};


#endif //ISA_PROJECT_ARG_PARSER_H
