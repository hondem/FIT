#include <stdio.h>
#include <stdlib.h>

#include "utils/arg_parser.hpp"
#include "utils/addres.hpp"
#include <pcap.h>

using namespace std;

int main(int argc, char **argv){	
	ProgArgs *myProgArgs = ParseArguments(argc, argv);

	if(myProgArgs->ip_address.empty()) myProgArgs->ip_address = getTargetIP(myProgArgs->domain_name).c_str();

	if(myProgArgs->interface.empty()){

		/*
		* Title: pcap_findalldevs example 
		* Author: Embedded Guru
		* Date: January 21, 2014
		* Availability: https://embeddedguruji.blogspot.com/2014/01/pcapfindalldevs-example.html?fbclid=IwAR1oNBFb6uZUxvSW0kPt9v_LJPwqwnfjk8EW2lLhx1TlbuFZakgDidyzLPw
		*/
		char error[PCAP_ERRBUF_SIZE];
		pcap_if_t *interfaces, *tmp;

		if(pcap_findalldevs(&interfaces,error)==-1){
        //TODO: THROW AN ERROR! 
        return -1;
    }

    for(tmp=interfaces; tmp; tmp=tmp->next){
			if(tmp->flags != PCAP_IF_LOOPBACK){
				myProgArgs->interface = tmp->name;
				break;
			}
    }
	}

	string myAddress = getSourceIP(myProgArgs->interface).c_str();
	return 0;
}