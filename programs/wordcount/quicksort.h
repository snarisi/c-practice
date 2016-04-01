#include <stdio.h>
#include <string.h>

typedef int (*comp_cb)(void *, void *);

void quicksort(void **, int, int, comp_cb);
int partition(void **, int, int, comp_cb);
void swap(void **, int, int);
int num_asc(int *, int *);
int str_asc(char *, char *);

void quicksort(void **arr, int l, int r, comp_cb comp)
{
	if (l >= r) return;

	int p;

	p = partition(arr, l, r, comp);
	quicksort(arr, l, p - 1, comp);
	quicksort(arr, p, r, comp);
}

int partition(void **arr, int l, int r, comp_cb comp)
{
	int i, j, p;

	i = l; // i is the current element being looked at
	j = l; // j is the lower bound for elements greater than the p val
	p = r; // p is the value the partition is based on

	while (i < p) {
		if (comp(arr[i], arr[p]) < 1) {
			swap(arr, i, j);
			j++;
		}
		i++;
	}
	swap(arr, p, j);
	return j;
}

void swap(void **arr, int i, int j)
{
	void *temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int num_asc(int *a, int *b)
{
	return *a - *b;
}

int str_asc(char *a, char *b)
{
	return strcmp(a, b);
}
