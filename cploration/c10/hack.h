#ifndef __HACK_H__
#define __HACK_H__

#include <string.h>
#include <stdint.h>

#define NUM_PREDEFINED_SYMBOLS 23

typedef enum symbol_id {
	SYM_R0 = 0,
	SYM_R1 = 1,
	SYM_R2 = 2,
	SYM_R3 = 3,
	SYM_R4 = 4,
	SYM_R5 = 5,
	SYM_R6 = 6,
	SYM_R7 = 7,
	SYM_R8 = 8,
	SYM_R9 = 9,
	SYM_R10 = 10,
	SYM_R11 = 11,
	SYM_R12 = 12,
	SYM_R13 = 13,
	SYM_R14 = 14,
	SYM_R15 = 15,
	SYM_SCREEN = 16384,
	SYM_KBD = 24576,
	SYM_SP = 0,
	SYM_LCL = 1,
	SYM_ARG = 2,
	SYM_THIS = 3,
	SYM_THAT = 4
} symbol_id;

typedef struct predefined_symbol {
	char name[10];
	int16_t address;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
	{"R0", SYM_R0}, 
	{"R1", SYM_R1}, 
	{"R2", SYM_R2}, 
	{"R3", SYM_R3}, 
	{"R4", SYM_R4}, 
	{"R5", SYM_R5}, 
	{"R6", SYM_R6}, 
	{"R7", SYM_R7}, 
	{"R8", SYM_R8}, 
	{"R9", SYM_R9}, 
	{"R10", SYM_R10}, 
	{"R11", SYM_R11}, 
	{"R12", SYM_R12}, 
	{"R13", SYM_R13}, 
	{"R14", SYM_R14}, 
	{"R15", SYM_R15}, 
	{"SCREEN", SYM_SCREEN}, 
	{"KBD", SYM_KBD}, 
	{"SP", SYM_SP}, 
	{"LCL", SYM_LCL}, 
	{"ARG", SYM_ARG}, 
	{"THIS", SYM_THIS}, 
	{"THAT", SYM_THAT}, 
};

typedef enum jump_id {
	JMP_INVALID = -1,
	JMP_NULL,
	JMP_JGT = 1,
	JMP_JEQ = 2,
	JMP_JGE = 3,
	JMP_JLT = 4,
	JMP_JNE = 5,
	JMP_JLE = 6,
	JMP = 7
} jump_id;

typedef enum dest_id {
	DEST_INVALID = -1,
	DEST_NULL,
	DEST_M = 1,
	DEST_D = 2,
	DEST_MD = 3,
	DEST_A = 4,
	DEST_AM = 5,
	DEST_AD = 6,
	DEST_AMD = 7
} dest_id;

typedef enum comp_id {
	COMP_INVALID = -1,
	COMP_0 = 42,
	COMP_1 = 63,
	COMP_neg1 = 58,
	COMP_D = 12,
	COMP_A = 48,
	COMP_notD = 13,
	COMP_notA = 49,
	COMP_negD = 15,
	COMP_negA = 51,
	COMP_Dplus1 = 31,
	COMP_Aplus1 = 55,
	COMP_Dminus1 = 14,
	COMP_Aminus1 = 50,
	COMP_DplusA = 2,
	COMP_DminusA = 19,
	COMP_AminusD = 7,
	COMP_DandA = 0,
	COMP_DorA = 21,
	COMP_M = 48,
	COMP_notM = 49,
	COMP_negM = 51,
	COMP_Mplus1 = 55,
	COMP_Mminus1 = 50,
	COMP_DplusM = 2,
	COMP_DminusM = 19,
	COMP_MminusD = 7,
	COMP_DandM = 0,
	COMP_DorM = 21
} comp_id;

static inline jump_id str_to_jumpid(const char *s) {
	jump_id id = JMP_INVALID;
	if (s == NULL) {
		id = JMP_NULL;
	} else if (!strcmp(s, "JGT")) {
		id = JMP_JGT;
	} else if (!strcmp(s, "JEQ")) {
		id = JMP_JEQ;
	} else if (!strcmp(s, "JGE")) {
		id = JMP_JGE;
	} else if (!strcmp(s, "JLT")) {
		id = JMP_JLT;
	} else if (!strcmp(s, "JNE")) {
		id = JMP_JNE;
	} else if (!strcmp(s, "JLE")) {
		id = JMP_JLE;
	} else if (!strcmp(s, "JMP")) {
		id = JMP;
	}
	return id;
}

static inline dest_id str_to_destid(const char *s) {
	dest_id id = DEST_INVALID;
	if (s == NULL) {
		id = DEST_NULL;
	} else if (!strcmp(s, "M")) {
		id = DEST_M;
	} else if (!strcmp(s, "D")) {
		id = DEST_D;
	} else if (!strcmp(s, "MD")) {
		id = DEST_MD;
	} else if (!strcmp(s, "A")) {
		id = DEST_A;
	} else if (!strcmp(s, "AM")) {
		id = DEST_AM;
	} else if (!strcmp(s, "AD")) {
		id = DEST_AD;
	} else if (!strcmp(s, "AMD")) {
		id = DEST_AMD;
	}
	return id;
}

static inline comp_id str_to_compid(const char *s, int *a) {
	comp_id id = COMP_INVALID;
	if (*a == 0) {
		if (!strcmp(s, "42")) {
			id = COMP_0;
		} else if(!strcmp(s, "63")) {
			id = COMP_1;
		} else if (!strcmp(s, "58")) {
			id = COMP_neg1;
		} else if (!strcmp(s, "12")) {
			id = COMP_D;
		} else if (!strcmp(s, "48")) {
			id = COMP_A;
		} else if (!strcmp(s, "13")) {
			id = COMP_notD;
		} else if (!strcmp(s, "49")) {
			id = COMP_notA;
		} else if (!strcmp(s, "15")) {
			id = COMP_negD;
		} else if (!strcmp(s, "51")) {
			id = COMP_negA;
		} else if (!strcmp(s, "31")) {
			id = COMP_Dplus1;
		} else if (!strcmp(s, "55")) {
			id = COMP_Aplus1;
		} else if (!strcmp(s, "14")) {
			id = COMP_Dminus1;
		} else if (!strcmp(s, "50")) {
			id = COMP_Aminus1;
		} else if (!strcmp(s, "2")) {
			id = COMP_DplusA;
		} else if (!strcmp(s, "19")) {
			id = COMP_DminusA;
		} else if (!strcmp(s, "7")) {
			id = COMP_AminusD;
		} else if (!strcmp(s, "0")) {
			id = COMP_DandA;
		} else if (!strcmp(s, "21")) {
			id = COMP_DorA;
		}
	} else if (*a == 1) {
		if (!strcmp(s, "48")) {
			id = COMP_M;
		} else if (!strcmp(s, "49")) {
			id = COMP_notM;
		} else if (!strcmp(s, "51")) {
			id = COMP_negM;
		} else if (!strcmp(s, "55")) {
			id = COMP_Mplus1;
		} else if (!strcmp(s, "50")) {
			id = COMP_Mminus1;
		} else if (!strcmp(s, "2")) {
			id = COMP_DplusM;
		} else if (!strcmp(s, "19")) {
			id = COMP_DminusM;
		} else if (!strcmp(s, "7")) {
			id = COMP_MminusD;
		} else if (!strcmp(s, "0")) {
			id = COMP_DandM;
		} else if (!strcmp(s, "21")) {
			id = COMP_DorM;
		}
	}
	return id;
}


#endif