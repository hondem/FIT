/**
 * Author: Jan Demel
 * Project: ISA DHCPv6 relay with MAC injection support
 * Compiler: gcc version 9.2.1 20191008
 * File name: exceptions.cpp
 * Created: 17. 10. 2019
 */
#include "exceptions.h"

void closeApp(string &message, int code){
    fprintf(stderr, "Error: %s", message.c_str());
    exit(code);
}

/**
 * Handler that closes app with certain message and error code
 * @param message
 * @param code
 */
void closeApp(char *message, int code){
    fprintf(stderr, "Error: %s", message);
    exit(code);
}

/**
 * Handler that closes app with certain message and error code
 * @param message
 * @param code
 */
void closeApp(const char *message, int code){
    fprintf(stderr, "Error: %s", message);
    exit(code);
}