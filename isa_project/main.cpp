#include <vector>
#include <string>
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
    } catch (ArgException &e){
        closeApp(e.what(), e.code);
    }

    arg_parser::DumpArguments(parsedArgs);

    sniffer *test = new sniffer(parsedArgs.interface);
    test->start();

    return 0;
}