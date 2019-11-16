//
// Created by jandemel on 05.11.19.
//

#include <netinet/in.h>
#include "sniffer.h"
#include "relay.h"

#include "utils/network.h"

sniffer::sniffer(string &targetDevice, Arguments &args) {
    this->device = targetDevice;
    this->args = args;
}

void sniffer::start() {
    vector<pcap_if_t> *devices = nullptr; // Devices to sniff on
    pcap_t *handle = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE]; // LIBPCAP error buffer

    try{
        // Get target devices that are relevant for us
        devices = network::getDevices(this->device);
        if(devices->empty()) throw InterfaceException("Interface not usable\n");

        // Lets store pointer to device we are using
        this->device_interface = devices->front();

        // Create sniffer handler
        handle = this->getHandle(devices->front().name, errbuf);

        // Apply sniff filter
        this->setFilter(handle, "dst port 547");

        // Define callback function (yeah... I used lambda!)
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
    printf("\nStarting sniffing on: %s\n\n", targetDevice);
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
    // Parts of relay_forward_message
    relay_message *p_relay_msg = new relay_message();
    relay_message_option *p_relay_msg_option = new relay_message_option();
    relay_message_option *p_interface_id_option = new relay_message_option();
    link_layer_option *p_ll_option = new link_layer_option();

    // Helpful stuff
    sockaddr_in6 *device_address = network::getDeviceIPV6GlobAddress(&this->device_interface);
    sniff_ip_6 *ipv6_header = network::getIP((u_char*) packet);
    sniff_ethernet *ethernet_header = network::getEthernet((u_char*) packet);
    int16_t payload_length = network::getPayloadLength((u_char*) packet) - 8;
    char *payload = network::getPayload((u_char*) packet);

    // Setting up relay_forward_message
    p_relay_msg->msg_type = 12;
    p_relay_msg->hop_count = 0;
    memcpy(&p_relay_msg->link_address, &device_address->sin6_addr, 16);
    memcpy(&p_relay_msg->peer_address, &ipv6_header->src, 16);

    // Setting up relay_message_option
    p_relay_msg_option->option = htons(9);
    p_relay_msg_option->option_length = htons(payload_length);
    p_relay_msg_option->message = (int8_t*) payload;

    // Setting up link_layer_option
    p_ll_option->option = htons(79);
    p_ll_option->option_length = htons(8);
    p_ll_option->link_layer_type = htons(1);
    memcpy(&p_ll_option->link_layer_addr, &ethernet_header->ether_shost, 6); // 20:6e:a6:87:6b:32 for development

    // Setting up interface_id_option
    p_interface_id_option->option = htons(18);
    p_interface_id_option->option_length = htons(this->device.size());
    p_interface_id_option->message = (int8_t*) this->device.c_str();

    relay::sendMessage(p_relay_msg, p_relay_msg_option, p_ll_option, p_interface_id_option, this->args);
}

void sniffer::sniffServer(Arguments args) {
    int i;
    const int BUFFER_SIZE = 1024;

    // Create socket
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock == -1) throw NetworkException("Couldn't open socket for server sniffing");

    // Set server listener
    sockaddr_in6 server;
    server.sin6_family = AF_INET6;
    server.sin6_port = htons(547);
    server.sin6_addr = in6addr_any;
    socklen_t len = sizeof(server);

    char buffer[BUFFER_SIZE];

    if(bind(sock, (sockaddr*) &server, len) == -1) throw NetworkException("Failed to bind socket");

    while(true){
        i = recvfrom(sock, buffer, BUFFER_SIZE, 0, (sockaddr*) &server, &len);
        if(i == -1) throw NetworkException("Failed to recieve packet");
        else if(i > 0) relay::receiveMessage(buffer, BUFFER_SIZE);
    }
}

