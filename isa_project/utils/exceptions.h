//
// Created by Jan Demel on 17/10/2019.
//

#ifndef ISA_PROJECT_EXCEPTIONS_H
#define ISA_PROJECT_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

// ========================= EXCEPTION CODES =========================
const int ARG_EXCEPTION_CODE = 100;
const int INTERFACE_EXCEPTION_CODE = 101;
const int INTERNAL_ERROR_CODE = 102;
// ====================== END OF EXCEPTION CODES =====================

void closeApp(string&, int);
void closeApp(char*, int);
void closeApp(const char*, int);

/**
 * Base class for application exceptions
 */
class AppException : public std::runtime_error {
public:
    int code;
    explicit AppException (const string &arg, const int code) : runtime_error(arg){ this->code = code; };
    explicit AppException (const char *arg, const int code) : runtime_error(arg){ this->code = code; };
};

/**
 * Exception thrown when bad arguments are passed
 */
class ArgException : public AppException {
public:
    explicit ArgException (const string &arg) : AppException(arg, ARG_EXCEPTION_CODE){ };
    explicit ArgException (const char *arg) : AppException(arg, ARG_EXCEPTION_CODE){ };
};

/**
 * Internal error
 */
class InternalException : public AppException {
public:
    explicit InternalException (const string &arg) : AppException(arg, INTERNAL_ERROR_CODE){ };
    explicit InternalException (const char *arg) : AppException(arg, INTERNAL_ERROR_CODE){ };
};

/**
 * Thrown when something bad happens during interface scanning
 */
class InterfaceException : public AppException {
public:
    explicit InterfaceException (const string &arg) : AppException(arg, INTERFACE_EXCEPTION_CODE){ };
    explicit InterfaceException (const char *arg) : AppException(arg, INTERFACE_EXCEPTION_CODE){ };
};


#endif //ISA_PROJECT_EXCEPTIONS_H
