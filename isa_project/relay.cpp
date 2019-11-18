/**
 * Author: Jan Demel
 * Project: ISA DHCPv6 relay with MAC injection support
 * Compiler: gcc version 9.2.1 20191008
 * File name: relay.cpp
 * Created: 11. 11. 2019
 */

#include "relay.h"

#include <stdio.h>
#include <cstring>

map<string, string> GLOB_IP_MAC;

void relay::sendMessage(relay_message *r_relay_msg, relay_message_option *r_relay_msg_option,
                        link_layer_option *r_ll_option, relay_message_option *r_interface_id_option, Arguments &args) {

    int16_t message_length;
    int8_t *message = network::serializeMessage(r_relay_msg, r_relay_msg_option, r_ll_option, r_interface_id_option, &message_length);

    int sock;
    int dest_port = 547;
    sockaddr_in6 server;

    if((sock = socket(PF_INET6, SOCK_DGRAM, 0)) == -1){
        throw NetworkException("Couldn't open socket");
    }

    server.sin6_family = AF_INET6;
    server.sin6_port = htons(dest_port);

    inet_pton(AF_INET6, args.server.c_str(), (void*)&server.sin6_addr);

    if(sendto(sock, (const void*) message, (size_t) message_length, 0, (const sockaddr*) &server, (socklen_t) sizeof(sockaddr_in6)) == -1){
        perror("Error");
    }
}

void relay::receiveMessage(char *payload, socklen_t buffer_size, Arguments &args) {
    relay_message *p_relay_message = (relay_message*) payload; // Whole Relay forward/reply message

    if(p_relay_message->msg_type != 13){
        printf("Recieved message that is not MSG_TYPE = 13");
        return;
    }

    int8_t *option = (int8_t*) payload + 34; // First option

    relay_message_option *p_relay_message_option = new relay_message_option();
    char *interface_name = nullptr;
    size_t interface_name_length = NULL;

    while(true){
        int16_t option_id = ntohs(*((int16_t*) option)); // ID of option
        int16_t option_length = ntohs(*((int16_t*) option + 1)); // Length of option

        if(option_id == 18){ // Option is Interface ID
            interface_name = (char*)malloc(sizeof(char) * option_length + 1);
            memset(interface_name, 0, option_length + 1);
            memcpy(interface_name, option + 4, option_length);
            interface_name_length = option_length;
        } else if(option_id == 9){ // Option is Relay message
            p_relay_message_option->option = *((int16_t*) option);
            p_relay_message_option->option_length = *((int16_t*) option + 1);
            int8_t *option_payload = (int8_t*)malloc(sizeof(int8_t) * ntohs(p_relay_message_option->option_length));
            memcpy(option_payload, option + 4, ntohs(p_relay_message_option->option_length));
            p_relay_message_option->message = option_payload;
        }

        if((option + option_length + 4) >= ((int8_t*)payload + buffer_size)) break; // If we WILL try to access memory out of payload
        option = option + option_length + 4;
    }

    // If we have received Reply message
    if(*(p_relay_message_option->message) == 7){

        char peer_addr[INET6_ADDRSTRLEN];
        char assigned_ipv6[INET6_ADDRSTRLEN];
        int8_t prefix = 0;

        int8_t *assigned_ipv6_addr = network::getIPv6FromDHCPMessage(p_relay_message_option->message, p_relay_message_option->option_length, &prefix);

        if(assigned_ipv6_addr == nullptr){
            printf("Failed to retrieve IPv6 address\n");
        } else {
            inet_ntop(AF_INET6, assigned_ipv6_addr, assigned_ipv6, INET6_ADDRSTRLEN);
            inet_ntop(AF_INET6, p_relay_message->peer_address, peer_addr, INET6_ADDRSTRLEN);

            // Print DEBUG
            if(args.debug){
                printf("%s,%s\n", assigned_ipv6, GLOB_IP_MAC[string(peer_addr)].c_str());
            }

            // Print LOG
            if(args.log){
                openlog("ISA-DHCPV6-RELAY", LOG_NDELAY, LOG_DAEMON);
                syslog(LOG_INFO, "%s,%s\n", assigned_ipv6, GLOB_IP_MAC[string(peer_addr)].c_str());
                closelog();
            }
        }
    }

    relay::sendMessageToClient(interface_name, interface_name_length, p_relay_message, p_relay_message_option);
}

void relay::sendMessageToClient(char *interface_name, size_t interface_name_length,
        relay_message *p_relay_message, relay_message_option *p_relay_message_option) {
    if(p_relay_message == nullptr) throw NetworkException("Failed to parse RELAY REPLY MESSAGE");
    if(interface_name == nullptr) throw NetworkException("Couldn't retrieve Interface ID option (REQUIRED)");
    if(p_relay_message_option == nullptr) throw NetworkException("Couldn't retrieve Relay Message option (REQUIRED)");

    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock == -1) throw NetworkException("Failed to open socket\n");

    sockaddr_in6 client;
    memset(&client, 0, sizeof(client));

    client.sin6_family = AF_INET6;
    client.sin6_port = htons(546);
    memcpy(&client.sin6_addr, p_relay_message->peer_address, 16);

    ifreq interface;
    memset(&interface, 0, sizeof(interface));

    snprintf(interface.ifr_name, sizeof(interface.ifr_name), "%s", interface_name);

    if(setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (const void*) &interface, sizeof(ifreq))){
        throw NetworkException("Failed to bind socket");
    }

    if(sendto(sock, p_relay_message_option->message, 84, 0, (sockaddr*) &client, sizeof(sockaddr_in6)) == -1){
        perror("ERROR");
        fflush(stderr);
    }

    close(sock);
}
