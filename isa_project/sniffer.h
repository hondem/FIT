//
// Created by jandemel on 05.11.19.
//

#ifndef ISA_PROJECT_SNIFFER_H
#define ISA_PROJECT_SNIFFER_H

#include <string>
#include <cstring>
#include <vector>
#include <pcap.h>

#include "utils/exceptions.h"
#include "utils/arg_parser.h"

using namespace std;


class sniffer {
private:
    /**
     * Interface to sniff on
     */
    string device;

    /**
     * Interface instance
     */
    pcap_if device_interface;

    /**
     * Program input arguments
     */
    Arguments args;

    /**
     * Create sniffer for target device
     * @param targetDevice
     * @param errbuf
     * @return
     */
    pcap_t *getHandle(char *targetDevice, char *errbuf);

    /**
     * Compiles filter and applies it to given handler
     * @param handle
     * @param filterExpression
     */
    void setFilter(pcap_t *handle, char *filterExpression);

    /**
     * Callback function
     * @param pkthdr
     * @param packet
     */
    void packetReceived(const struct pcap_pkthdr* pkthdr,const u_char* packet);
public:
    /**
     * Constructs sniffer with interface
     * @param interface
     */
    explicit sniffer(string &targetDevice, Arguments &args);

    /**
     * Start sniffing
     */
    void start();

    /**
     * Start sniffing on server
     * @param args
     */
    static void sniffServer(Arguments args);
};


#endif //ISA_PROJECT_SNIFFER_H
