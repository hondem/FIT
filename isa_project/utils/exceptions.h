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
// ====================== END OF EXCEPTION CODES =====================

void closeApp(string&, int);
void closeApp(char*, int);
void closeApp(const char*, int);

/**
 * Base class for application exceptions
 */
class AppException : public std::runtime_error {
public:
    explicit AppException (const string &arg) : runtime_error(arg){ };
    explicit AppException (const char *arg) : runtime_error(arg){ };
};

/**
 * Exception thrown when bad arguments are passed
 */
class ArgException : public AppException {
public:
    explicit ArgException (const string &arg) : AppException(arg){ };
    explicit ArgException (const char *arg) : AppException(arg){ };
};

/**
 * Internal error
 */
class InternalException : public AppException {
public:
    explicit InternalException (const string &arg) : AppException(arg){ };
    explicit InternalException (const char *arg) : AppException(arg){ };
};

/**
 * Thrown when something bad happens during interface scanning
 */
class InterfaceException : public AppException {
public:
    explicit InterfaceException (const string &arg) : AppException(arg){ };
    explicit InterfaceException (const char *arg) : AppException(arg){ };
};


#endif //ISA_PROJECT_EXCEPTIONS_H
