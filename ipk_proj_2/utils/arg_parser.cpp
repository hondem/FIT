#include "arg_parser.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <regex>
#include "error_handler.hpp"
#include <sstream>
#include <algorithm>

vector<int> *validateAndGetPorts(string inputParam){
	vector<int> *ret = new vector<int>;
	/**
	 * There is only one port specified on input - 10
	 */
	if(regex_match(inputParam, regex("^([0-9]|[1-9][0-9]*)$"))){
		ret->push_back(stoi(inputParam));

	/**
	 * We have array of numbers - 10,20,30
	 */
	} else if(regex_match(inputParam, regex("^([0-9]|[1-9][0-9]*)(,([0-9]|[1-9][0-9]*))+$"))){
		string tmp = "";

		for(size_t i = 0; i < inputParam.length(); i++){
			if(inputParam[i] == ','){
				ret->push_back(stoi(tmp));
				tmp = "";
			} else {
				tmp += inputParam[i];
			}
		}

		ret->push_back(stoi(tmp));

	/**
	 * We have range of numbers - 10-30
	 */
	} else if(regex_match(inputParam, regex("^([0-9]|[1-9][0-9]*)-([0-9]|[1-9][0-9]*)$"))){
		string tmp = "";

		int from = 0;
		int to = 0;

		for(size_t i = 0; i < inputParam.length(); i++){
			if(inputParam[i] == '-'){
				from = stoi(tmp);
				tmp = "";
			} else {
				tmp += inputParam[i];
			}
		}

		to = stoi(tmp);

		if(from >= to){
			THROW_ERROR_PARAMS();
		} else {
			for(int i = from; i < to; i++){
				ret->push_back(i);
			}
		}

	} else {
		THROW_ERROR_PARAMS();
	}

	return ret;
}

/**
 * Validates interface
 */
string validateAndGetInterface(string inputParam){
	return inputParam;
}

/**
 * Validates domain
 */
bool validateDomain(string inputParam){
	return true;
}

/**
 * Validates IP adress
 */
bool validateAdress(string inputParam){
	return regex_match(inputParam, regex("^([0-9]|[1-9][0-9]{1,2})(.([0-9]|[1-9][0-9]{1,2})){3}$"));
}

/**
 * Method responsible for parsing arguments
 */
ProgArgs *ParseArguments(int argc, char **argv){
	ProgArgs *_progArgs = (ProgArgs*) malloc(sizeof(struct S_ProgArgs));
	_progArgs->UDP_ports = new vector<int>;
	_progArgs->TCP_ports = new vector<int>;

	/**
	 * Parsing arguments
	 */
	for(int i = 1; i < argc; i++){
		//TODO: Ověřovat, jestli další parametr vůbec existuje!
		if(strcmp(argv[i], "-pu") == 0){
			_progArgs->UDP_ports = validateAndGetPorts(argv[++i]);
		} else if(strcmp(argv[i], "-pt") == 0){
			_progArgs->TCP_ports = validateAndGetPorts(argv[++i]);
		} else if(strcmp(argv[i], "-i") == 0){
			_progArgs->interface = validateAndGetInterface(argv[++i]);
		} else {
			if(validateAdress(argv[i])){
				_progArgs->ip_address = argv[i];
			} else if(validateDomain(argv[i])){
				_progArgs->domain_name = argv[i];
			} else {
				THROW_ERROR_PARAMS();
			}
		}
	}


	return _progArgs;
}