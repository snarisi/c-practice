#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct hashtable HashTable;

HashTable *HashTable_create(int);
void HashTable_set(HashTable *, char *, char *);
char *HashTable_get(HashTable *, char *);
void HashTable_destroy(HashTable *);
static int hash(char *, int);

struct hashtable {
	LinkedList **entries;
	int numrows;
};

HashTable *HashTable_create(int numrows)
{
	HashTable *newtable;
	LinkedList **newdata;

	newtable = malloc(sizeof(HashTable));
	newdata = calloc(numrows, sizeof(LinkedList *));
	
	newtable->entries = newdata;
	newtable->numrows = numrows;

	return newtable;
}

void HashTable_set(HashTable *table, char *key, char *val)
{
	int hashval;
	LinkedList *row;

	hashval = hash(key, table->numrows);
	if (table->entries[hashval] == NULL) {
		table->entries[hashval] = LinkedList_create();
	}

	row = table->entries[hashval];
	LinkedList_addtotail(row, key, val);
}

char *HashTable_get(HashTable *table, char *key)
{
	int hashval;
	LinkedList *row;
	Node *n;

	hashval = hash(key, table->numrows);
	row = table->entries[hashval];
	
	if(!row) return NULL;
	
	n = row->head;

	while (n) {
		if (strcmp(n->key, key) == 0) {
			return n->val;
		}
		n = n->next;
	}
	return NULL;
}

void HashTable_destroy(HashTable *table)
{
	for (int i = 0; i < table->numrows; i++) {
		if (table->entries[i]) {
			LinkedList_destroy(table->entries[i]);
		}
	}
	free(table->entries);
	free(table);
}

static int hash(char *key, int num)
{
	int sum, i;

	sum = 0;

	for (i = 0; key[i] != '\0'; i++) {
		sum += key[i];
	}

	return sum % num;
}
