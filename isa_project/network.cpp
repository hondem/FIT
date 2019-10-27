//
// Created by Jan Demel on 18/10/2019.
//

#include "network.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <cstdio>
#include <string>

#include "utils/exceptions.h"
#include "utils/arg_parser.h"

/**
 * Return IPv6 address of interface if exists
 * @return
 *
 * Inspired by: https://stackoverflow.com/questions/33125710/how-to-get-ipv6-interface-address-using-getifaddr-function
 */
vector<string> *network::getTargetInterfaces(const string &interface_name) {
    vector<string> *interfaces = new vector<string>();

    struct ifaddrs *ifAddress;
    size_t addrSize = 100;
    char addr[addrSize];

    if (getifaddrs(&ifAddress) == -1) throw InterfaceException("Error with parsing interfaces");

    while (ifAddress) {
        if(ifAddress->ifa_addr && ifAddress->ifa_addr->sa_family == AF_INET6){
            sockaddr_in6 *adrs = (sockaddr_in6*) ifAddress->ifa_addr;
            inet_ntop(AF_INET6, &adrs->sin6_addr, addr, (socklen_t) addrSize);
        }

        if(
            arg_parser::isIPV6Address(addr) &&
            !(find(interfaces->begin(), interfaces->end(), string(addr)) != interfaces->end())
        ){
            if(!interface_name.empty() && strcmp(ifAddress->ifa_name, interface_name.c_str()) == 0){
                interfaces->push_back(string(addr));
            } else if(interface_name.empty()){
                interfaces->push_back(string(addr));
            }
        }

        ifAddress = ifAddress->ifa_next;
    }

    return interfaces;
}