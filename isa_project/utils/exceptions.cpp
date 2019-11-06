//
// Created by Jan Demel on 17/10/2019.
//
#include "exceptions.h"

/**
 * Handler that closes app with certain message and error code
 * @param message
 * @param code
 */
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