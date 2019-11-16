//
// Created by root on 11.11.19.
//

#ifndef ISA_PROJECT_RELAY_H
#define ISA_PROJECT_RELAY_H

#include "utils/network.h"
#include "utils/arg_parser.h"
#include "utils/exceptions.h"

class relay {
public:
    /**
     * Send message to server through sockets
     * @param r_relay_msg
     * @param r_relay_msg_option
     * @param r_ll_option
     * @param args
     */
    static void sendMessage(relay_message *r_relay_msg, relay_message_option *r_relay_msg_option,
            link_layer_option *r_ll_option, relay_message_option *r_interface_id_option, Arguments &args);

    /**
     * Recieve message from DHCP server
     * @param message
     * @param buffer_size
     */
    static void receiveMessage(char *message, socklen_t buffer_size);

    /**
     * Send message from server to client
     * @param interface_name
     * @param interface_name_length
     * @param relay_message
     */
    static void sendMessageToClient(char *interface_name, size_t interface_name_length, relay_message_option *relay_message);
};


#endif //ISA_PROJECT_RELAY_H
