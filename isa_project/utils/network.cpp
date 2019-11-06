//
// Created by jandemel on 05.11.19.
//

#include "network.h"
#include "exceptions.h"

vector<pcap_if_t> *network::getDevices(string &device) {
    vector<pcap_if_t> *devices = new vector<pcap_if_t>();

    pcap_if_t *allDevices;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Get all available devices and store them in allDevices variable
    if(pcap_findalldevs(&allDevices, errbuf) == PCAP_ERROR){
        throw InterfaceException("Failed to obtain devices");
    }

    // Iterate through devices and pick only those with IPv6 address
    // If device is specified, it will pick only that one (if found)
    pcap_if_t *tmp = allDevices;
    while(tmp->next != NULL){
        bool hasIPV6Address = false;

        // Lets check if device has IPv6 address
        pcap_addr_t *addrTmp = tmp->addresses;
        while(addrTmp != NULL) {
            if (addrTmp->addr->sa_family == AF_INET6) {
                hasIPV6Address = true;
                break;
            }
            addrTmp = addrTmp->next;
        }

        if(hasIPV6Address && (device.empty() || (!device.empty() && device == string(tmp->name)))){
            devices->push_back(*tmp);
        }

        tmp = tmp->next;
    }


    return devices;
}
