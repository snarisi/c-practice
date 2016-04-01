#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quicksort.h"

typedef struct wordtree WordTree;

WordTree *WordTree_create(char *);
void WordTree_add(WordTree *, char *);
void WordTree_print(WordTree *);
WordTree **WordTree_sort(WordTree *);
void WordTree_toarray(WordTree *, WordTree **);
void _toarrayrecur(WordTree *, WordTree **);
int WordTree_size(WordTree *);
void WordTree_printsorted(WordTree *);
void WordTree_destroy(WordTree *);
int wordcmp(WordTree *, WordTree *);

struct wordtree {
	char *word;
	int count;
	WordTree *left;
	WordTree *right;
};

WordTree *WordTree_create(char *word)
{
	WordTree *newtree;

	newtree = malloc(sizeof(WordTree));
	newtree->word = word;
	newtree->count = 1;
	newtree->left = NULL;
	newtree->right = NULL;

	return newtree;
}

void WordTree_add(WordTree *tree, char *word)
{
	if (strcmp(word, tree->word) < 0) {
		if (!tree->left) {
			tree->left = WordTree_create(word);
		} else {
			WordTree_add(tree->left, word);
		}
	} else if (strcmp(word, tree->word) > 0) {
		if (!tree->right) {
			tree->right = WordTree_create(word);
		} else {
			WordTree_add(tree->right, word);
		}
	} else {
		tree->count++;
	}
}

void WordTree_print(WordTree *tree) {
	printf("%s: %d\n", tree->word, tree->count);
	if (tree->left) {
		WordTree_print(tree->left);
	}
	if (tree->right) {
		WordTree_print(tree->right);
	}
}

int WordTree_size(WordTree *tree)
{
	int c = 0;

	if (tree) c += 1;
	if (tree->left) c += WordTree_size(tree->left);
	if (tree->right) c += WordTree_size(tree->right);
	return c;
}

WordTree **WordTree_sort(WordTree *tree)
{
	int size = WordTree_size(tree);
	WordTree **words = malloc(size * sizeof(*words));

	WordTree_toarray(tree, words);
	quicksort((void **)words, 0, size - 1, (int(*)(void*, void*))wordcmp);
	return words;
}

// this is pretty lame ... need to do to put the elements into the right array index
static int i;

void WordTree_toarray(WordTree *tree, WordTree **array)
{
	i = -1;
	_toarrayrecur(tree, array);
}

void _toarrayrecur(WordTree *tree, WordTree **array)
{
	i++;
	array[i] = tree;
	if (tree->left) _toarrayrecur(tree->left, array);
	if (tree->right) _toarrayrecur(tree->right, array);
}

int wordcmp(WordTree *a, WordTree *b)
{ 
	return b->count - a->count;
}
