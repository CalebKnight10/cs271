const char *error_messages[] = {
	[EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]", 
}; 

void exit_prgoram(enum exitcode code, ...) {
	va_list programs;
	va_start(arguments, code);

	printf("ERROR: ");
	vprintf(sstdout, erro_messages[code], arguments);

	va_end(arguments);
	exit(code);
}