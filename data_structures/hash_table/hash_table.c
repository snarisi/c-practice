#include <stdio.h>
#include "hash_table.h"

int main(int argc, char *argv[])
{
	HashTable *table = HashTable_create(12);
	HashTable_set(table, "first", "one");
	HashTable_set(table, "second", "two");

	char *word = HashTable_get(table, "first");
	printf("Found val at key 'first': %s\n", word);
	
	word = HashTable_get(table, "second");
	printf("Found val at key 'second': %s\n", word);
	
	word = HashTable_get(table, "third");
	printf("Found val at key 'third': %s\n", word);
	
	HashTable_destroy(table);
	return 0;
}
