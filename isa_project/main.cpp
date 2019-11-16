#include <vector>
#include <thread>

/**
 * Including utilities
 */
#include "utils/arg_parser.h"
#include "utils/exceptions.h"

#include "sniffer.h"

/**
 * Program entry point
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    Arguments parsedArgs;

    try {
        parsedArgs = arg_parser::Parse(argc, argv);

        arg_parser::DumpArguments(parsedArgs);

        // Start sniffing RELAY <-> SERVER
        thread response_sniffer(sniffer::sniffServer, parsedArgs);

        // Start sniffing CLIENT <-> RELAY
        sniffer *test = new sniffer(parsedArgs.interface, parsedArgs);
        test->start();

    } catch (AppException &e){
        closeApp(e.what(), e.code);
    }

    return 0;
}