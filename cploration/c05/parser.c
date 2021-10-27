#include "parser.h"

void parse(FILE * file) {
	char line[MAX_LINE_LENGTH] = "";

	while (fgets(line, sizeof(line), file)) {
		strip(line);
		if (!*line) {
			continue;
		}
		char inst_type;
		if(line == is_Atype) {
			inst_type = 'A';
		}
		printf("%c  %s\n", line);
	}
}

char *strip(char *s) {
	char s_new[sizeof(s) + 1] = "";
	int i = 0;
	for(char *s2 = s; *s2; s2++) { 
		if(*s2 == '/' && *(s2+1) =='/') {
			break;
		}
		else if(!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

void is_Atype(const char *line[]) {
	for(char *l2 = line; *l2; l2++) {
		if(*l2 == '@') {
			return true;
		}
		else false;
	}
}
