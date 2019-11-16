//
// Created by jandemel on 05.11.19.
//

#ifndef ISA_PROJECT_NETWORK_H
#define ISA_PROJECT_NETWORK_H

#include <pcap.h>
#include <string>
#include <vector>

using namespace std;

/**
 * Inspired by
 * https://www.tcpdump.org/pcap.html
 * https://www.winpcap.org/docs/docs_412/html/group__wpcap__tut6.html
 */

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* ethernet headers are always exactly 14 bytes */
#define SIZE_ETHERNET 14

/* Ethernet header */
struct sniff_ethernet {
    u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
    u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
    u_short ether_type; /* IP? ARP? RARP? etc */
};

/* IPv6 header */
struct sniff_ip_6{
    unsigned int
            version : 4,
            traffic_class : 8,
            flow_label : 20;
    uint16_t length;
    uint8_t  next_header;
    uint8_t  hop_limit;
    struct in6_addr src;
    struct in6_addr dst;
};

/* UDP header */
struct sniff_udp{
    int16_t sport;          // Source port
    int16_t dport;          // Destination port
    int16_t len;            // Datagram length
    int16_t crc;            // Checksum
};

/* ================== END OF: FROM https://www.tcpdump.org/pcap.html =================*/

/**
 * Struct for relay message
 */
struct relay_message {
    int8_t msg_type;
    int8_t hop_count;
    int8_t link_address[16];
    int8_t peer_address[16];
};

/**
 * Relay message option
 */
struct relay_message_option {
    int16_t option;
    int16_t option_length;
    int8_t *message;
};

/**
 * Link layer option
 */
struct link_layer_option {
    int16_t option;
    int16_t option_length;
    int16_t link_layer_type;
    int8_t link_layer_addr[6];
};



class network {
public:
    /**
     * Get all devices that we should use
     * @param device
     * @return
     */
    static vector<pcap_if_t> *getDevices(string &device);

    /**
     * Returns first IPv6 found
     * @param device
     * @return
     */
    static sockaddr_in6 *getDeviceIPV6GlobAddress(pcap_if *device);

    /**
     * Returns data payload of Ethernet frame
     * @param packet
     * @return
     */
    static sniff_ethernet *getEthernet(u_char *packet);

    /**
     * Returns UDP header
     * @param packet
     * @return
     */
    static sniff_udp *getUDP(u_char *packet);

    /**
     * Returns data payload of IP packet
     * @param packet
     * @return
     */
    static sniff_ip_6 *getIP(u_char *packet);

    /**
     * Returns data payload of UDP packet
     * @param packet
     * @return
     */
    static char *getPayload(u_char *packet);

    /**
     * Returns length of data payload from UDP packet
     * @param packet
     * @return
     */
    static int16_t getPayloadLength(u_char *packet);

    /**
     * Serialize relay message
     * @param r_relay_msg
     * @param r_relay_msg_option
     * @param r_ll_option
     * @return
     */
    static int8_t *serializeMessage(relay_message *r_relay_msg, relay_message_option *r_relay_msg_option,
                                    link_layer_option *r_ll_option, relay_message_option *r_interface_id_option, int16_t *message_length);
};


#endif //ISA_PROJECT_NETWORK_H
