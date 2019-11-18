/**
 * Author: Jan Demel
 * Project: ISA DHCPv6 relay with MAC injection support
 * Compiler: gcc version 9.2.1 20191008
 * File name: main.cpp
 * Created: 16. 10. 2019
 */

#include <vector>
#include <map>
#include <thread>

/**
 * Including utilities
 */
#include "utils/arg_parser.h"
#include "utils/exceptions.h"
#include "utils/network.h"

#include "sniffer.h"
#include <syslog.h>


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

        //arg_parser::DumpArguments(parsedArgs);

        // Start sniffing RELAY <-> SERVER
        thread response_sniffer(sniffer::sniffServer, parsedArgs);
        response_sniffer.detach();

        // Start sniffing CLIENTs <-> RELAY
        vector<pcap_if_t> *devices = network::getDevices(parsedArgs.interface);;

        for(int i = 0; i < devices->size(); i++){
            string device_name = string(devices->at(i).name);

            thread interface_sniffer([](Arguments args) {
                sniffer *device_sniffer = new sniffer(args.interface, args);
                device_sniffer->start();
            }, (Arguments){
                .server = parsedArgs.server,
                .interface =  device_name,
                .log = parsedArgs.log,
                .debug = parsedArgs.debug
            });

            interface_sniffer.detach();
        }

        /*sniffer *test = new sniffer(parsedArgs.interface, parsedArgs);
        test->start();*/

    } catch (AppException &e){
        closeApp(e.what(), e.code);
    }

    while(true);

    return 0;
}