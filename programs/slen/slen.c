#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define IN 1
#define OUT 0

int main(int argc, char **argv)
{
	int c, trigger, curline, curlen, status;
	char *filename;
	FILE *file;

	if (argc < 3) {
		printf("Usage: <filename> <trigger>\n");
		return 1;
	}

	filename = argv[1];
	trigger = atoi(argv[2]);

	file = fopen(filename, "r");

	curline = 1;
	curlen = 0;
	status = OUT;

	while ((c = getc(file)) != EOF) {
		if (c =='\n') {
		
			curline++;
		
		} else if (isspace(c)) {
			
			if (status == IN) {
				status = OUT;
				curlen++;
			}
		
		} else if (ispunct(c)) {
			
			if (status == IN) {
				status = OUT;
				curlen++;
			}
			
			if (curlen >= trigger) {
				printf("Sentence with %d words found on line %d\n", curlen, curline);
			}
			curlen = 0;
		} else if (isalpha(c)) {
			if (status == OUT) {
				status = IN;
			}
		}
	}

	return 0;
}
