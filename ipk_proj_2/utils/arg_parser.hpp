#ifndef ARG_PARSER
#define ARG_PARSER

#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

/**
 * Default structure for program arguments
 */
typedef struct S_ProgArgs{
	string domain_name;
	string ip_address;
	string interface;
	vector<int> *UDP_ports;
	vector<int> *TCP_ports;
} ProgArgs;


ProgArgs *ParseArguments(int, char**);

#endif