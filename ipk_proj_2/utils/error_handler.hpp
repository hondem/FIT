#include <stdio.h>
#include <stdlib.h>

/**
 * ERROR CODES
 */
int const CODE_ERROR_PARAMS = -1;
int const CODE_ERROR_GET_TARGET_IP = -2;

/**
 * Methods for throwing errors
 */
int THROW_ERROR_PARAMS();
int THROW_ERROR_GET_TARGET_IP();