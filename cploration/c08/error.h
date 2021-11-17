#ifndef __ERROR_H__
#define __ERROR_H__
#include <stdarg.h>

typedef enum exitcode {
	/*
 * Error code 1 represents that given file does not exist.
 */
	EXIT_INCORRECT_ARGUMENTS = 1,
	EXIT_CANNOT_OPEN_FILE = 2,
	EXIT_TOO_MANY_INSTRUCTIONS = 3, 
} exitcode;

void exit_program(enum exitcode code, ...); // ... means arg list size can vary

#endif