#include <symtable.h>

// Unsigned long extended size variable for storing numbers (32 bits or 4 bytes)
// Won't store negatives... range [0-2^32-1]
unsigned long
hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		// This allows us to wrap around the hash table
		// Basically we can index without going over
		// {[1],[2],[...],[end]-> back to [1]}
		return hash %= SYMBOL_TABLE_SIZE;
}

void insert(hack_addr addr,char *name[]) {

   struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
   item->name = name;  
   item->addr = addr;

   //get the hash 
   int hashIndex = hashCode(addr);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->addr != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}