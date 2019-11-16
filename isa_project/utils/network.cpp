//
// Created by jandemel on 05.11.19.
//

#include "network.h"
#include "exceptions.h"
#include <cstring>

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

sockaddr_in6 *network::getDeviceIPV6GlobAddress(pcap_if *device) {
    pcap_addr *tmp = device->addresses;
    while(tmp != NULL){
        if(tmp->addr->sa_family == AF_INET6){
            return (sockaddr_in6*)tmp->addr;
        } else {
            tmp = tmp->next;
        }
    }

    return nullptr;
}

char *network::getPayload(u_char *packet) {
    return (char *)(packet + SIZE_ETHERNET + 40 + 8); // TODO: Constants shouldn't be there because of optional size!
}

int16_t network::getPayloadLength(u_char *packet) {
    return ntohs(*((int16_t*)(packet + SIZE_ETHERNET + 40 + 4)));
}

sniff_ethernet *network::getEthernet(u_char *packet) {
    return (sniff_ethernet*)(packet);
}

sniff_ip_6 *network::getIP(u_char *packet) {
    return (sniff_ip_6*)(packet + SIZE_ETHERNET);
}

sniff_udp *network::getUDP(u_char *packet) {
    return (sniff_udp*)(packet + SIZE_ETHERNET + 40);
}

void printArray(int8_t *array, int16_t length){
    for(int16_t i = 0; i < length; i++){
        printf("%02X ", array[i]);
    }
    printf("\n");
    fflush(stdout);
}

void clearArray(int8_t *array, int16_t length){
    for(int16_t i = 0; i < length; i++){
        array[i] = 0;
    }
}

int8_t *network::serializeMessage(relay_message *r_relay_msg, relay_message_option *r_relay_msg_option,
                                  link_layer_option *r_ll_option, relay_message_option *r_interface_id_option, int16_t *message_length) {

    int16_t relay_msg_option_length = ntohs(r_relay_msg_option->option_length);
    int16_t interface_id_option_length = ntohs(r_interface_id_option->option_length);

    int16_t total_length =
            sizeof(relay_message) +
            sizeof(link_layer_option) +
            relay_msg_option_length +
            4 +
            interface_id_option_length +
            4; // 4 because of option and option_len in relay_msg_option

    *message_length = total_length;

    // Message to be send
    int8_t *message = (int8_t*) malloc(total_length * sizeof(int8_t));
    clearArray(message, total_length);

    //printArray(message, total_length);
    memcpy(message, r_relay_msg, sizeof(relay_message)); // Copying relay_message header
    //printArray(message, total_length);
    memcpy(message + sizeof(relay_message), r_relay_msg_option, 4); // Copying relay_message_option header
    //printArray(message, total_length);
    memcpy(message + sizeof(relay_message) + 4, r_relay_msg_option->message, relay_msg_option_length); // Copying relay_message_option_content
    //printArray(message, total_length);
    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length, r_ll_option, sizeof(link_layer_option));
    //printArray(message, total_length);
    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length + sizeof(link_layer_option), r_interface_id_option, 4); // Copying interface_id_option header

    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length + sizeof(link_layer_option) + 4, r_interface_id_option->message, interface_id_option_length); // Copying interface_id_option header

    return message;
}
