//
// Created by jandemel on 05.11.19.
//

#include "sniffer.h"

#include "utils/network.h"

sniffer::sniffer() = default;

sniffer::sniffer(string &targetDevice) {
    this->device = targetDevice;
}

void sniffer::setInterface(string &targetDevice) {
    this->device = targetDevice;
}

void sniffer::start() {
    vector<pcap_if_t> *devices = nullptr; // Devices to sniff on
    pcap_t *handle = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE]; // LIBPCAP error buffer

    try{
        // Get target devices that are relevant for us
        devices = network::getDevices(this->device);
        if(devices->empty()) throw InterfaceException("Interface not usable\n");

        // Create sniffer handler
        handle = this->getHandle(devices->front().name, errbuf);

        // Apply sniff filter
        this->setFilter(handle, "dst port 547");

        pcap_loop(handle, -1, [](u_char *instance, const pcap_pkthdr *pkthdr, const u_char *packet) {
            sniffer *obj = (sniffer *)instance;
            obj->packetReceived(pkthdr, packet);
        }, (u_char*)this);

    } catch (AppException &e){
        closeApp(e.what(), e.code);
    }

    printf("Hi, im here\n");
}

pcap_t *sniffer::getHandle(char *targetDevice, char *errbuf) {
    if(targetDevice == NULL) throw InternalException("Trying to sniff on undefined interface\n");
    pcap_t *handle = pcap_open_live(targetDevice, BUFSIZ, 1, 1000, errbuf);
    if(handle == NULL) throw InterfaceException("Couldn't open device\n");
}

void sniffer::setFilter(pcap_t *handle, char *filterExpression) {
    bpf_program *fp = new bpf_program;

    if(pcap_compile(handle, fp, filterExpression, 0, 0) == PCAP_ERROR){
        throw InternalException("Couldn't parse filter\n");
    }

    if(pcap_setfilter(handle, fp) == PCAP_ERROR){
        throw InternalException("Couldn't apply filter\n");
    }
}

void sniffer::packetReceived(const pcap_pkthdr *pkthdr, const u_char *packet) {
    printf("Recieved packet!\n");
}

