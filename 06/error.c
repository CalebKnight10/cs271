#include "error.h"
#include <stdio.h>
#include <stdlib.h>

const char *error_messages[] = {
	[EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]", 
	[EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s", 
	[EXIT_TOO_MANY_INSTRUCTIONS] = "File contains than the maximum %u instructions", 
	[EXIT_INVALID_LABEL] = "Line %u: %s: Invalid label name", 
	[EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s: Symbol is already defined", 
	[EXIT_INVALID_A_INSTRUCTION] = "Line %u: %s : Invalid A-instruction operand", 
	[EXIT_INVALID_C_DEST] = "Line %u: %s : Invalid destination part of C-instruction",
	[EXIT_INVALID_C_COMP] = "Line %u: %s : Invalid compare part of C-instruction",
	[EXIT_INVALID_C_JUMP] = "Line %u: %s : Invalid jump part of C-instruction",
}; 

void exit_program(enum exitcode code, ...) {
	va_list arguments;
	va_start(arguments, code);

	printf("ERROR: ");
	vfprintf(stdout, error_messages[code], arguments);

	va_end(arguments);
	exit(code);
}