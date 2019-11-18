//
// Created by jandemel on 05.11.19.
//

#include "network.h"
#include "exceptions.h"
#include <cstring>
#include <stdio.h>

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
    return (char *)(packet + SIZE_ETHERNET + network::getIPHeaderLength(packet) + 8);
}

int16_t network::getPayloadLength(u_char *packet) {
    return ntohs(*((int16_t*)(packet + SIZE_ETHERNET + network::getIPHeaderLength(packet) + 4)));
}

sniff_ethernet *network::getEthernet(u_char *packet) {
    return (sniff_ethernet*)(packet);
}

sniff_ip_6 *network::getIP(u_char *packet) {
    return (sniff_ip_6*)(packet + SIZE_ETHERNET);
}

int16_t network::getIPHeaderLength(u_char *packet) {
    int16_t total_length = 40;
    sniff_ip_6 *ip_header = network::getIP(packet);

    if(ip_header->next_header != 17){
        ipv6_extension_header *extension_header = (ipv6_extension_header*) (((int8_t*)ip_header) + total_length);

        while(extension_header->next_header != 17){
            total_length += extension_header->length + 8;
            extension_header = (ipv6_extension_header*) (((int8_t*)ip_header) + total_length);
        }
    }

    return total_length;
}

sniff_udp *network::getUDP(u_char *packet) {
    return (sniff_udp*)(packet + SIZE_ETHERNET + network::getIPHeaderLength(packet));
}

void network::printArray(int8_t *array, int16_t length){
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

    memcpy(message, r_relay_msg, sizeof(relay_message)); // Copying relay_message header
    memcpy(message + sizeof(relay_message), r_relay_msg_option, 4); // Copying relay_message_option header
    memcpy(message + sizeof(relay_message) + 4, r_relay_msg_option->message, relay_msg_option_length); // Copying relay_message_option_content
    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length, r_ll_option, sizeof(link_layer_option));
    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length + sizeof(link_layer_option), r_interface_id_option, 4); // Copying interface_id_option header
    memcpy(message + sizeof(relay_message) + 4 + relay_msg_option_length + sizeof(link_layer_option) + 4, r_interface_id_option->message, interface_id_option_length); // Copying interface_id_option header

    return message;
}

int8_t *network::getIPv6FromDHCPMessage(int8_t *dhcp_message, int16_t dhcp_message_length, int8_t *prefix) {
    int8_t *option = dhcp_message + 4; // First option of DHCPv6 MESSAGE!

    // We are looking for IA-NON-TEMPORARY OR IA-TEMPORARY OR IA-PD
    while(!(
            ntohs(*((int16_t*) option)) == 3 ||
            ntohs(*((int16_t*) option)) == 4 ||
            ntohs(*((int16_t*) option)) == 25
    )){
        option = option + 4 + *((int16_t*) option + 1);

        if(option > (dhcp_message + dhcp_message_length)) return nullptr;
    }

    if(ntohs(*((int16_t*) option)) == 3){ // If we found IA-NON-TEMPORARY
        option = option + 16; // Skipping header size to get another headers

        // We are looking for IA ADDRESS OPTION
        while(!(ntohs(*((int16_t*) option)) == 5)){
            option = option + 4 + *((int16_t*) option + 1);

            if(option > (dhcp_message + dhcp_message_length)) return nullptr;
        }

        // If we found IA ADDRESS OPTION
        if(ntohs(*((int16_t*) option)) == 5){
            return (option + 4);
        }
    } else if(ntohs(*((int16_t*) option)) == 3){ // If we found IA-TEMPORARY
        option = option + 8; // Skipping header

        // We are looking for IA ADDRESS OPTION
        while(!(ntohs(*((int16_t*) option)) == 5)){
            option = option + 4 + *((int16_t*) option + 1);

            if(option > (dhcp_message + dhcp_message_length)) return nullptr;
        }

        // If we found IA ADDRESS OPTION
        if(ntohs(*((int16_t*) option)) == 5){
            return (option + 4);
        }
    } else if(ntohs(*((int16_t*) option)) == 25){ // If we found IA-PD
        option = option + 16; // Skipping header

        // We are looking for IA-Prefix-option
        while(!(ntohs(*((int16_t*) option)) == 26)){
            option = option + 4 + *((int16_t*) option + 1);

            if(option > (dhcp_message + dhcp_message_length)) return nullptr;
        }

        // If we found IA-Prefix-option
        if(ntohs(*((int16_t*) option)) == 26){
            *prefix = *(option + 12);
            return (option + 13);
        }
    }

    return nullptr;
}
