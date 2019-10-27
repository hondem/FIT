#include <vector>
#include <string>
#include <pcap.h>
/**
 * Including utilities
 */
#include "utils/arg_parser.h"
#include "utils/exceptions.h"

/**
 * Including application parts
 */
 #include "network.h"

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
        closeApp(e.what(), ARG_EXCEPTION_CODE);
    }

    arg_parser::DumpArguments(parsedArgs);


    //vector<string> *interfaces = network::getTargetInterfaces(parsedArgs.interface);

    char *dev, errbuf[PCAP_ERRBUF_SIZE];

    dev = pcap_lookupdev(errbuf);

    if(dev == NULL){
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return(2);
    }
    printf("Device: %s\n", dev);

    pcap_t *handle;

    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }



    return 0;
}