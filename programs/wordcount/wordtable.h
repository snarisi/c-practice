#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "quicksort.h"

typedef struct node WordNode;
typedef struct table WordTable;

WordTable *WordTable_create(int);
void WordTable_add(WordTable *, char *);
static WordNode *WordNode_create(char *);
static WordNode **WordTable_sort(WordTable *);
void WordTable_print(WordTable *);
void WordTable_print_sorted(WordTable *, int);
static int wordcomp(WordNode *, WordNode *);
static int hash(char *, int);

struct table {
	WordNode **buckets;
	int numbuckets;
	int numwords;
};

struct node {
	char *word;
	int count;
	WordNode *next;
};

WordTable *WordTable_create(int numbuckets)
{
	WordTable *newtable = malloc(sizeof(WordTable));
	newtable->numbuckets = numbuckets;
	newtable->numwords = 0;
	newtable->buckets = calloc(numbuckets,  sizeof(WordNode));

	return newtable;
}

void WordTable_add(WordTable *table, char *word)
{
	int i;
	WordNode *currentnode;

	i = hash(word, table->numbuckets);
	if (!table->buckets[i]) {
		table->buckets[i] = WordNode_create(word);
		table->numwords++;
	} else {
		currentnode = table->buckets[i];
		while (currentnode) {
			if (strcmp(currentnode->word, word) == 0) {
				currentnode->count++;
				return;
			} else if (!currentnode->next) {
				currentnode->next = WordNode_create(word);
				table->numwords++;
				return;
			} else {
				currentnode = currentnode->next;
			}
		}

	}
}

WordNode *WordNode_create(char *word)
{
	WordNode *newnode = malloc(sizeof(WordNode));
	newnode->word = word;
	newnode->count = 1;
	newnode->next = NULL;

	return newnode;
}

WordNode **WordTable_sort(WordTable *table) {
	WordNode **array = malloc(table->numwords * sizeof(WordNode));
	WordNode **ptr = array;
	WordNode *currentnode;

	for (int i = 0; i < table->numbuckets; i++) {
		currentnode = table->buckets[i];
		while (currentnode) {
			*ptr++ = currentnode;
			currentnode = currentnode->next;
		}
	}

	quicksort((void **)array, 0, table->numwords - 1, (int(*)(void*,void*))wordcomp);
	return array;
}

void WordTable_print(WordTable *table)
{
	int i;
	WordNode *currentnode;

	for (i = 0; i < table->numbuckets; i++) {
		currentnode = table->buckets[i];
		while (currentnode) {
			printf("%s: %d\n", currentnode->word, currentnode->count);
			currentnode = currentnode->next;
		}
	}
}

void WordTable_print_sorted(WordTable *table, int lim)
{
	WordNode **arr;
	arr = WordTable_sort(table);
	for (int i = 0; i < lim; i++) {
		printf("%s: %d\n", arr[i]->word, arr[i]->count);
	}
	free(arr);
}

int hash(char *word, int num)
{
	int total, i;

	total = 0;
	for (i = 0; word[i] != '\0'; i++) {
		total += word[i];
	}

	return i % num;
}

static int wordcomp(WordNode *a, WordNode *b)
{
	return b->count - a->count;
}
