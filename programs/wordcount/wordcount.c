#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "wordtable.h"

#define MAX_WORD 100

char *getword(FILE *file)
{
	char c, *word, *p;

	word = malloc(MAX_WORD * sizeof(char));
	p = word;

	c = tolower(getc(file));

	while (!isalpha(c)) {
		if (c == EOF) {
			*p = '\0';
			return word;
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
	WordTable *wordtable;
	int limit;

	limit = 0;

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

	wordtable = WordTable_create(48);
	word = getword(file);
	while (strlen(word) > 0) {
		WordTable_add(wordtable, word);
		word = getword(file);
	}

	free(word);
	
	if (limit > wordtable->numwords || !limit) {
		limit = wordtable->numwords;
	}

	WordTable_print_sorted(wordtable, limit);
	WordTable_destroy(wordtable);
	fclose(file);

	return 0;
}
