#include "symtable.h"

// Unsigned long extended size variable for storing numbers (32 bits or 4 bytes)
// Won't store negatives... range [0-2^32-1]
unsigned long hash(unsigned char *str) {
	unsigned long hash = 5381;
	int c = 0;

	while (c == *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		// This allows us to wrap around the hash table
		// Basically we can index without going over
		// {[1],[2],[...],[end]-> back to [1]}
		return hash %= SYMBOL_TABLE_SIZE;
}

void insert(char *name, hack_addr addr) {

	struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
	item->name = name;  
	item->addr = addr;

   //get the hash 
	int hashIndex = hash(addr);

   //move in array until an empty or deleted cell
	while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->addr != -1) {
      //go to next cell
		++hashIndex;
		
      //wrap around the table
		hashIndex %= SYMBOL_TABLE_SIZE;
	}
	
	hashArray[hashIndex] = item;
}

struct Symbol *find(char *name) {
   //get the hash 
	int hashIndex = hash(name);  
	
   //move in array until an empty 
	while(hashArray[hashIndex] != NULL) {

		if(hashArray[hashIndex]->name == name)
			return hashArray[hashIndex]; 

      //go to next cell
		++hashIndex;
		
      //wrap around the table
		hashIndex %= SYMBOL_TABLE_SIZE;
	}        
	
	return NULL;        
}

void display_table() {
	int i = 0;
	
	for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {

		if(hashArray[i] != NULL)
			printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->addr);
		else
			printf(" ~~ ");
	}
	
	printf("\n");
}