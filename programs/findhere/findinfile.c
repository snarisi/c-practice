#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define COLOR "\x1B[32m"
#define NORM "\x1B[0m"

int find(char *, char *, int);

int find(char *str, char *pat, int start)
{
	int i, j, k;

	i = start;
	j = 0;

	while(str[i] != '\0') {
		k = i;
		while (str[k] == pat[j]) {
			k++;
			j++;
			if (pat[j] == '\0') {
				return i;
			}
		}
		i++;
		j = 0;
	}

	return -1;
}

int main(int argc, char **argv)
{
	char *line[MAXLINE], *filename, pattern[MAXLINE], space[2];
	size_t size, *ptr;
	FILE *file;
	int i, col, patlen, j;

	if (argc < 3) {
		printf("USAGE: <filename> <pattern>\n");
		return 1;
	}

	filename = argv[1];
	pattern[0] = '\0';
	space[0] = ' ';
	space[1] = '\0';
	file = fopen(filename, "r");
	size = MAXLINE;
	ptr = &size;
	i = 0;
	patlen = 0;

	for (j = 2; j < argc; j++) {
		patlen = strlcat(pattern, argv[j], MAXLINE);
		if (j < argc - 1) {
			patlen = strlcat(pattern, space, MAXLINE);
		}
	}

	while ((getline(line, ptr, file) != EOF)) {
		i++;
		col = 0;
		while ((col = find(*line, pattern, col)) > -1) {
			printf(NORM "line %d, col %d:\n", i, col);
			for (j = 0; j < col; j++) printf("%c", (*line)[j]);
			printf(COLOR);
			for (; j < col + patlen; j++) printf("%c", (*line)[j]);
			printf(NORM);
			for (; (*line)[j] != '\0'; j++) printf("%c", (*line)[j]);
			printf("\n");

			col = col + patlen;
		}
	}

	fclose(file);
	return 0;
}
