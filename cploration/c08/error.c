#include "error.h"
#include <stdio.h>
#include <stdlib.h>

const char *error_messages[] = {
	[EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]", 
	[EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s", 
	[EXIT_TOO_MANY_INSTRUCTIONS] = "File contains than the maximum %u instructions", 
	[EXIT_INVALID_LABEL] = "Line %u: %s: Invalid label name", 
	[EXIT_SYMBOL_ALREADY_EXISTS] = "ine %u: %s: Symbol is already defined", 
}; 

void exit_prgoram(enum exitcode code, ...) {
	va_list arguments;
	va_start(arguments, code);

	printf("ERROR: ");
	vfprintf(stdout, error_messages[code], arguments);

	va_end(arguments);
	exit(code);
}