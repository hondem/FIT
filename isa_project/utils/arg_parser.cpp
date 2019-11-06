//
// Created by Jan Demel on 16/10/2019.
//

#include "arg_parser.h"
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <regex>

#include "exceptions.h"

/**
 * Parse arguments form CLI
 * @param argc
 * @param argv
 * @return
 */
Arguments arg_parser::Parse(int argc, char *argv[]) {
    Arguments args = { "", "", false, false};

    int opt;
    opterr = 0; // Disable implicit stderr output
    std::ostringstream errStream; // Stream for string formatting (C++...) - Errors

    while ((opt = getopt(argc, argv, "s:ldi:")) != -1){ // Iterate through all command line arguments
        switch(opt){
            case 'l':
                args.log = true;
            break;

            case 'd':
                args.debug = true;
            break;

            case 'i':
                args.interface = optarg;
            break;

            case 's':
                if(!isIPV6Address(optarg)) throw ArgException("Given server IP does not match IPv6 schema\n");
                args.server = optarg;
            break;

            case '?':
                if (optopt == 'i' || optopt == 's'){
                    errStream << "Option -" << (char)optopt << " requires an argument" << endl;
                    throw ArgException(errStream.str());
                } else if (isprint(optopt)){
                    errStream << "Unknown option `-" << (char)optopt << "`" << endl;
                    throw ArgException(errStream.str());
                } else {
                    errStream << "Unknown option character" << endl;
                    throw ArgException(errStream.str());
                }

            default:
                abort();
        }
    }

    // -s argument is mandatory so we have to check it...
    if(args.server.empty()) {
        throw ArgException("-s parameter is mandatory\n");
    }

    return args;
}

/**
 * Dump arguments to console
 * @param args
 */
void arg_parser::DumpArguments(Arguments &args) {
    printf("Server: %s\nInterface: %s\nDebug: %d\nLog: %d\n",
            args.server.c_str(), args.interface.c_str(), args.debug, args.log);
}

/**
 * Checks whether given IP address matches IPv6 schema
 * @param address
 * @return
 */
bool arg_parser::isIPV6Address(char *address) {
    return (regex_match(address, regex("(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))")));
}
