//
// Created by root on 11.11.19.
//

#include "relay.h"

#include <stdio.h>
#include <cstring>

void relay::sendMessage(relay_message *r_relay_msg, relay_message_option *r_relay_msg_option,
                        link_layer_option *r_ll_option, relay_message_option *r_interface_id_option, Arguments &args) {

    int16_t message_length;
    int8_t *message = network::serializeMessage(r_relay_msg, r_relay_msg_option, r_ll_option, r_interface_id_option, &message_length);

    int sock;
    int dest_port = 547;
    sockaddr_in6 server;

    if((sock = socket(PF_INET6, SOCK_DGRAM, 0)) == -1) throw NetworkException("Couldn't open socket");
    printf("Socket created\n");

    server.sin6_family = AF_INET6;
    server.sin6_port = htons(dest_port);

    inet_pton(AF_INET6, args.server.c_str(), (void*)&server.sin6_addr);


    if(sendto(sock, (const void*) message, (size_t) message_length, 0, (const sockaddr*) &server, (socklen_t) sizeof(sockaddr_in6)) == -1){
        perror("Error");
    }
}

void relay::receiveMessage(char *payload, socklen_t buffer_size) {
    int8_t *option = (int8_t*) payload + 34; // First option

    relay_message_option *relay_message = nullptr;
    char *interface_name = nullptr;
    size_t interface_name_length = NULL;

    while(true){
        int16_t option_id = ntohs(*((int16_t*) option)); // ID of option
        int16_t option_length = ntohs(*((int16_t*) option + 1)); // Length of option

        if(option_id == 18){ // Option is Interface ID
            interface_name = (char*)malloc(sizeof(char) * option_length);
            memcpy(interface_name, option + 4, option_length);
            interface_name_length = option_length;
        } else if(option_id == 9){ // Option is Relay message
            relay_message = (relay_message_option*) option;
        }

        if((option + option_length + 4) >= ((int8_t*)payload + buffer_size)) break; // If we WILL try to access memory out of payload
        option = option + option_length + 4;
    }

    relay::sendMessageToClient(interface_name, interface_name_length, relay_message);
}

void relay::sendMessageToClient(char *interface_name, size_t interface_name_length,
        relay_message_option *relay_message) {
    if(interface_name == nullptr) throw NetworkException("Couldn't retrieve Interface ID option (REQUIRED)");
    if(relay_message == nullptr) throw NetworkException("Couldn't retrieve Relay Message option (REQUIRED)");


}
