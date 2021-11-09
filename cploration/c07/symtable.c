#include <symtable.h>


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

