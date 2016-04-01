#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "wordtree.h"

#define MAX_WORD 100

char *getword(FILE *file)
{
	char c, *word, *p;

	word = malloc(MAX_WORD * sizeof(char));
	p = word;

	c = tolower(getc(file));

	while (!isalpha(c)) {
		if (c == EOF) {
			return NULL;
		}
		c = tolower(getc(file));
	}

	while (isalpha(c) || c == '\'') {
		*p = c;
		p++;
		c = getc(file);
	}
	*p = '\0';
	return word;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Please specify a file.");
		return 1;
	}

	FILE *file;
	char *word, *path;
	WordTree *words,  **words_sorted;
	int size, limit;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'l':
					limit = atoi(argv[i + 1]);
					i++;
					break;
				default:
					printf("Option %c doesn't exist.\n", argv[i][1]);
					break;
			}
		} else {
			path = argv[i];
		}
	}

	file = fopen(path, "r");

	while ((word = getword(file))) {
		if (!words) {
			words = WordTree_create(word);
		} else {
			WordTree_add(words, word);
		}
	}

	words_sorted = WordTree_sort(words);
	size = WordTree_size(words);
	if (limit > size) {
		limit = size;
	}

	for (int i = 0; i < limit; i++) {
		printf("%s: %d\n", words_sorted[i]->word, words_sorted[i]->count);
	}
	
//	WordTree_print(words);
	fclose(file);

	return 0;
}
