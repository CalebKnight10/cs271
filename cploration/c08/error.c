const char *error_messages[] = {
	[EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]", 
	[EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s", 
	[EXIT_TOO_MANY_INSTRUCTIONS] = "File contains than the maximum %u instructions", 
	[EXIT_INVALID_LABEL] = "Line %u: %s: Invalid label name", 
	[EXIT_SYMBOL_ALREADY_EXISTS] = "ine %u: %s: Symbol is already defined", 
}; 

void exit_prgoram(enum exitcode code, ...) {
	va_list programs;
	va_start(arguments, code);

	printf("ERROR: ");
	vprintf(sstdout, erro_messages[code], arguments);

	va_end(arguments);
	exit(code);
}