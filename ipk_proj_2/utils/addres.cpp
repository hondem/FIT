#include "addres.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include "error_handler.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>

/*
* Title: Linux Programmer's Manual
* Author: -
* Date: 2019-03-06
* Availability: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
*/
string getTargetIP(string domainName){
	struct addrinfo hints;
	struct addrinfo *result;
	char addrstr[100];
	void *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	int error = getaddrinfo(domainName.c_str(), NULL, &hints, &result);

	if(error != 0) {
		printf("Error code: %s\n", gai_strerror(error));
		THROW_ERROR_GET_TARGET_IP();
	}

	while(result){
		inet_ntop (result->ai_family, result->ai_addr->sa_data, addrstr, 100);
		ptr = &((struct sockaddr_in *) result->ai_addr)->sin_addr;
		inet_ntop (result->ai_family, ptr, addrstr, 100);
		result = result->ai_next;
	}

	return addrstr;
}

/*
* Title: Get IP address of an interface on Linux
* Author: Filip Ekberg
* Date: Feb 17'10 at 18:59
* Availability: https://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux
*/
string getSourceIP(string interface){
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	
	if(interface != ""){
		strcpy(ifr.ifr_name, interface.c_str());
	} else {
		return "";
	}

	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}