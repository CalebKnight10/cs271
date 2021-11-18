#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


#define SYMBOL_TABLE_SIZE 100

typedef int16_t hack_addr;

struct Symbol {
	char* name;
	hack_addr addr;
} Symbol;

struct Symbol* hashArray[SYMBOL_TABLE_SIZE]; 
struct Symbol *symtable_find(char *name);

int hash(char *str);
void symtable_insert(char* name, hack_addr addr);
void symtable_display_table();

#endif