#include "parser.h"
#include "error.h"
#include "symtable.h"
#include "hack.h"

void parse(FILE * file) {
	char line[MAX_LINE_LENGTH] = "";
	instruction instr;

	unsigned int line_num = 0;
	unsigned int instr_num = 0;

	 add_predefined_symbols();
	 symtable_display_table();

	while (fgets(line, sizeof(line), file)) {
		++line_num;
		if(instr_num > MAX_INSTRUCTION){ 
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION + 1);
		}
		strip(line);
		if (!*line) {
			continue;
		} 
		char instr_type = '\0';
		if(is_Atype(line)) {
			if (!parse_A_instruction(line, &instr.a_instr)){
				exit_program(EXIT_INVALID_A_INSTRUCTION, line_num, line);
			}
			instr.instr_type = A_instr;
			instr_type = 'A';
		} 
		else if(is_label(line)) {
			instr_type = 'L';
			char label[MAX_LABEL_LENGTH] = {0};

			if(!isalpha(line[0])) {
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if(symtable_find(line) == NULL) {
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			} else{
				symtable_insert(line, instr_num);
			}
			continue;
			strcpy(line, extract_label(line, label));
		}
		else if(is_Ctype(line)) {
			instr_type = 'C';
		}
		printf("%c  %s\n", instr_type, line);
		++instr_num;
	}
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
	}
	s_new[i] = '\0';
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

void add_predefined_symbols() {
	int i = 0;
	for(i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
		predefined_symbol symbol= predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
	char *s = malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10); //string to long in base 10
	if(s == s_end) {
		instr->label = malloc(strlen(line));
		strcpy(instr->label, s);
		instr->is_addr = false;
	}
	else if(*s_end != 0) {
		return false;
	}
	else {
		instr->addy = result;
		instr->is_addr = true;
	}
	return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {
	char *temp;
	int a;
	char *jump;
	char *dest;
	char *comp;
	temp = strtok(line, ";");
	jump = strtok(NULL, " ");
	dest = strtok(temp, "=");
	comp = strtok(NULL, "=");
	if (comp == NULL) {
		comp = dest;
		dest = NULL;
	}
	instr->comp = str_to_compid(comp, &a);
	instr->dest = str_to_destid(dest);
	instr->jump = str_to_jumpid(jmp);
	instr->a = a == 0 ? 0 : 1;

}
