/**
 * Author: Jan Demel
 * Project: ISA DHCPv6 relay with MAC injection support
 * Compiler: gcc version 9.2.1 20191008
 * File name: exceptions.h
 * Created: 17. 10. 2019
 */

#ifndef ISA_PROJECT_EXCEPTIONS_H
#define ISA_PROJECT_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

// ========================= EXCEPTION CODES =========================
const int ARG_EXCEPTION_CODE = 100;
const int INTERFACE_EXCEPTION_CODE = 101;
const int INTERNAL_ERROR_CODE = 102;
const int NETWORK_EXCEPTION_CODE = 103;
// ====================== END OF EXCEPTION CODES =====================

void closeApp(string &message, int code);
void closeApp(char *message, int code);
void closeApp(const char *message, int code);

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

/**
 * Throw when network error occurs
 */
class NetworkException : public AppException {
public:
    explicit NetworkException (const string &arg) : AppException(arg, NETWORK_EXCEPTION_CODE){ };
    explicit NetworkException (const char *arg) : AppException(arg, NETWORK_EXCEPTION_CODE){ };
};


#endif //ISA_PROJECT_EXCEPTIONS_H
