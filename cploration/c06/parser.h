#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH-2

typedef int16_t hack_addr;
typedef int16_t opcode;
typedef struct C_instruction {
	opcode a:1;
	opcode comp:7;
	opcode dest:3;
	opcode jump:3;
} c_instruction;

typedef struct A_instruction {
	union AddyOrLabel {
		hack_addr addy;
		char *label;
	}
	bool is_addr;
} a_instruction;

typedef struct Instruction {
	union AorC {
		a_instruction;
		c_instruction;
	}
	instr_type type_stored;
} instruction;

char *strip(char *s);
char *extract_label(const char *line, char* label);
void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

enum instr_type {Inv_instr = -1, A-instr, C-instr};
