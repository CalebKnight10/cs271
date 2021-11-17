#include "parser.h"
void parse(FILE * file) {
	char line[MAX_LINE_LENGTH] = "";
	unsigned int line_num;
	unsigned int inst_num;
	while (fgets(line, sizeof(line), file)) {
		line_num ++;
		strip(line);
		if (!*line) {
			continue;
		} 
		char inst_type = '\0';
		if(is_Atype(line)) {
			inst_type = 'A';
		} 
		else if(is_label(line)) {
			inst_type = 'L';
			char label[MAX_LABEL_LENGTH] = {0};
			strcpy(line, extract_label(line, label));
		}
		else if(is_Ctype(line)) {
			inst_type = 'C';
		}
		printf("%c  %s\n", inst_type, line);
		inst_num ++;
	}
}

if(inst_num > MAX_INSTRUCTION) {
	exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION + 1);
}

char *strip(char *s) {
	char s_new[strlen(s)+1];
	int i = 0;
	for(char *s2 = s; *s2; s2++) { 
		if(*s2 == '/' && *(s2+1) =='/') {
			break;
		}
		else if(!isspace(*s2)) {
			s_new[i++] = *s2;
		}
		s_new[i] = '\0';
	}
	strcpy(s, s_new);
	return s;
}

char *extract_label(const char *line, char* label) {
	int i = 0;
	for(const char *label2 = line; *label2; label2++) {
		if(*label2=='(' || *label2==')') {
			continue;
		}
		else {
			label[i++] = *label2;
		}
	}
	label[i] = '\0';
	return label;
}

bool is_Atype(const char *line) {
	return line[0] == '@';
}

bool is_label(const char *line) {
	return line[0] == '(' && line[strlen(line) - 1] == ')';
}

bool is_Ctype(const char *line) {
	return !is_label(line) && !is_Atype(line);
}