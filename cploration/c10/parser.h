#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH-2
#define MAX_HASH_ADDRESS INT16_MAX
#define MAX_INSTRUCTION MAX_HASH_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type {
	Inv_instr = -1, 
	A_instr, 
	C_instr
};

typedef struct c_instruction {
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;
} c_instruction;

typedef struct a_instruction {
	union {
		hack_addr addy;
		char * label;
	};
	bool is_addr;
} a_instruction;

typedef struct instruction {
	union {
		a_instruction a_instr;
		c_instruction c_instr;
	};
	 bool instr_type;
} instruction;

char *strip(char *s);
char *extract_label(const char *line, char* label);

void add_predefined_symbols();
void parse(FILE * file);

bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);


#endif
