#include "error_handler.hpp"

int THROW_ERROR_PARAMS(){
	fprintf(stderr, "Error: Something went wrong with parsing your arguments\n");
	exit(CODE_ERROR_PARAMS);
}

int THROW_ERROR_GET_TARGET_IP(){
	fprintf(stderr, "Error: Couldn't get target IP address\n");
	exit(CODE_ERROR_GET_TARGET_IP);
}