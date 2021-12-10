#include "symtable.h"
#include <stdio.h>


// Unsigned long extended size variable for storing numbers (32 bits or 4 bytes)
// Won't store negatives... range [0-2^32-1]
int hash(char* str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		// This allows us to wrap around the hash table
		// Basically we can index without going over
		// {[1],[2],[...],[end]-> back to [1]}
	}
	return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char* key, hack_addr addr) {

	struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
	item->addr = addr;  
	item->name = (char*) malloc(strlen(key) + 1);
	strcpy(item->name, key);
   //get the hash 
	int hashIndex = hash(key);

   //move in array until an empty or deleted cell
	while(hashArray[hashIndex] != NULL && hashArray[hashIndex] -> name != NULL) {
      //go to next cell
		++hashIndex;
		
      //wrap around the table
		hashIndex %= SYMBOL_TABLE_SIZE;
	}
	
	hashArray[hashIndex] = item;
}

struct Symbol *symtable_find(char* key) {
   //get the hash 
	int hashIndex = hash(key);  
	
   //move in array until find an empty spot
	while(hashArray[hashIndex] != NULL) {

		if(hashArray[hashIndex]->name == key) {
			return hashArray[hashIndex];
		}

      //go to next cell
		++hashIndex;
		
      //wrap around the table
		hashIndex %= SYMBOL_TABLE_SIZE;
	}        
	
	return NULL;        
}

void symtable_display_table() {	
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++) {

		if(hashArray[i] != NULL)
			printf(" (%s,%d)",hashArray[i] -> name, hashArray[i] -> addr);
		else
			printf(" {~~,~~}, ");
	}
	
	printf("\n");
}