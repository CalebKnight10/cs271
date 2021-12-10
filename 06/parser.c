#include "parser.h"

int parse(FILE * file, instruction *instructions) {
	char line[MAX_LINE_LENGTH] = "";
	instruction instr;

	unsigned int line_num = 0;
	unsigned int instr_num = 0;

	add_predefined_symbols();
	symtable_display_table();

	while (fgets(line, sizeof(line), file)) {
		line_num ++;
		if(instr_num > MAX_INSTRUCTION) { 
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION + 1);
		}
		strip(line);
		if (!*line) {
			continue;
		} 
		char inst_type = '\0';
		if(is_Atype(line)) {
			if (!parse_A_instruction(line, &instr.A_or_C.a_instr)){
				exit_program(EXIT_INVALID_A_INSTRUCTION, line_num, line);
			}
			instr.in_type = A_instr;
			inst_type = 'A';
		} 
		if(is_label(line)) {
			inst_type = 'L';
			char label[MAX_LABEL_LENGTH] = {0};
			strcpy(line, extract_label(line, label));
			if(!(isalpha(label[0]))) {
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if(symtable_find(label) != NULL) {
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			} 
			symtable_insert(label, instr_num);
			continue;
			
		}
		if (is_Ctype(line)) {
			inst_type = 'C';
			char temp_line[MAX_LINE_LENGTH];
			strcpy(temp_line, line);
			parse_C_instruction(temp_line, &instr.A_or_C.c_instr);
			if (instr.A_or_C.c_instr.dest == DEST_INVALID) {
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			else if (instr.A_or_C.c_instr.comp == COMP_INVALID) {
				exit_program(EXIT_INVALID_C_COMP, line_num, line); 
			}
			else if (instr.A_or_C.c_instr.jump == JMP_INVALID) {
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			instr.in_type = C_instr;

		}
		printf("%c  %s\n", inst_type, line);
		instructions[instr_num++] = instr;
	}
	return instr_num;
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
	if (!is_label(line) && !is_Atype(line)){
		return true;
	} else {
		return false;
	}
}

void add_predefined_symbols() {
	int i = 0;
	for(i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
		predefined_symbol symbol= predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
	char* s = (char*) malloc(strlen(line));
	strcpy(s, line + 1);
	char* s_end = NULL;
	long result = strtol(s, &s_end, 10); //string to long in base 10
	if(s == s_end) {
		instr->inst_type.label = (char*) malloc(strlen(line));
		strcpy(instr->inst_type.label, s);
		instr->is_addr = false;
	}
	else if(*s_end != 0) {
		return false;
	}
	else {
		instr->inst_type.addy = result;
		instr->is_addr = true;
	}
	return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {
	int a;
	char* temp = strtok(line, ";");
	char* jump = strtok(NULL, ";");
	char* dest = strtok(temp, "=");
	char* comp = strtok(NULL, "=");
	if (comp == NULL) {
		comp = dest;
		dest = NULL;
	}
	// printf("%s\n", dest);
	// printf("%s\n", jump);
	// printf("%s\n", comp);

	instr->comp = str_to_compid(comp, &a);
	instr->dest = str_to_destid(dest);
	instr->jump = str_to_jumpid(jump);
	instr->a = (a == 0 ? 0 : 1);
}


void assemble(const char * file_name, instruction* instructions, int num_instructions) {

	char *hack_file = strncat((char*)file_name, ".hack", 5);
	FILE *hack = fopen(hack_file, "w");

	opcode op;
	int new_addy = 16;

	for(int i = 0; i < num_instructions; i++) {
		instruction instr = instructions[i];

		if(instr.in_type == 0) {
			//A type
			if(instructions[i].A_or_C.a_instr.is_addr == false) {
				if(symtable_find(instr.A_or_C.a_instr.inst_type.label)) {
					op = symtable_find(instr.A_or_C.a_instr.inst_type.label) -> addr;
				}

				//C type
				else {
					symtable_insert(instr.A_or_C.a_instr.inst_type.label, new_addy++);
					op = symtable_find(instr.A_or_C.a_instr.inst_type.label) -> addr;
				}
				free(instr.A_or_C.a_instr.inst_type.label);
			}


			else {
				op = instr.A_or_C.a_instr.inst_type.addy;
			}
		}
		else if (instr.in_type == 1) {
			op = instruction_to_opcode(instr.A_or_C.c_instr);
		}
		fprintf(hack, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(op));

	}
	fclose(hack);
}

opcode instruction_to_opcode(c_instruction instr) {
	opcode op = 0;
	op |= (7 << 13);
	op |= (instr.a << 12);
	op |= (instr.comp << 6);
	op |= (instr.dest << 3);
	op |= (instr.jump << 0);
	return op;
}

