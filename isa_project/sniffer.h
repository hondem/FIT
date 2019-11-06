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

using namespace std;

void testPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
class sniffer {
private:
    /**
     * Interface to sniff on
     */
    string device;

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
     * Default constructor
     */
    sniffer();

    /**
     * Constructs sniffer with interface
     * @param interface
     */
    explicit sniffer(string &targetDevice);

    /**
     * Sets interface that sniffer handles
     * @param interface
     */
    void setInterface(string &targetDevice);

    /**
     * Start sniffing
     */
    void start();

    /**
     * Wrapper for callback function
     * @param args
     * @param header
     * @param packet
     */
    static void packetReceivedWrapper(u_char *instance, const pcap_pkthdr *pkthdr, const u_char *packet);
};


#endif //ISA_PROJECT_SNIFFER_H
