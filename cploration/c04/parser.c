#include "parser.h"

void parse(FILE * file) {
	char line[MAX_LINE_NUMBER] = "";

	while (fgets(line, sizeof(line), fin)) {
		strip(line);
		if (!*line) {
			continue;
		}
		printf("%s\n", line);
	}
}
