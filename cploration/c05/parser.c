#include "parser.h"

void parse(FILE * file) {
	char line[MAX_LINE_LENGTH] = "";

	while (fgets(line, sizeof(line), file)) {
		strip(line);
		if (!*line) {
			continue;
		} 
		char inst_type = '\0';
		if(is_Atype(line)) {
			inst_type = 'A';
		} 
		else if (is_label(line)) {
			inst_type = 'L';
		}
		else if (is_Ctype(line)) {
			inst_type = 'C';
		}
		printf("%c  %s\n", inst_type, line);
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

bool is_Atype(const char *line) {
	return line[0] == '@';
}

bool is_label(const char *line) {
	return line[0] == '(' && line[sizeof(line) -1] == ')';
}

bool is_Ctype(const char *line) {
	return line[0] == !is_label(line) && !is_Atype(line);
}
