//
// Created by root on 14.11.19.
//

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