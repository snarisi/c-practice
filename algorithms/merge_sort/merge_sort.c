#include <stdio.h>

typedef int (*comp_cb)(void *, void *);
void mergesort(void **, int, int, comp_cb);
void merge(void **, int, int, comp_cb);
int num_asc(int *, int *);
void swap(void **, int, int);

void mergesort(void **arr, int start, int end, comp_cb cmp)
{
	if (end - start < 1) return;
	int mid = (start + end) / 2;

	mergesort(arr, start, mid, cmp);
	mergesort(arr, mid + 1, end, cmp);
	merge(arr, start, end, cmp);
}

void merge(void **arr, int start, int end, comp_cb cmp)
{
	int i, mid, j, k;
	void *temp[end - start];

	i = start;
	mid = (start + end) / 2;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= end) {
		if (cmp(arr[i], arr[j]) < 0) {
			temp[k] = arr[i];
			i++;
			k++;
		} else {
			temp[k] = arr[j];
			k++;
			j++;
		}
	}

	for (; i <= mid; i++, k++) temp[k] = arr[i];
	for (; j <= end; j++, k++) temp[k] = arr[j];

	for (i = start, k = 0; i <= end; i++, k++) arr[i] = temp[k];
}

void swap(void **arr, int i, int j)
{
	void *temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int num_asc(int *a, int *b)
{
	return *a - *b;
}

int main(int argc, char *argv[])
{
	int nums[] = {10, 3, 8, 5, 9, 12, 4, 1};
	int *ptrs[8];
	

	for (int i = 0; i < 8; i++) {
		ptrs[i] = &nums[i];
	}

	for (int i = 0; i < 8; i++) {
		printf("%d ", (int)*ptrs[i]);
	}
	printf("\n");

	mergesort((void **)ptrs, 0, 7, (int(*)(void*, void*))(num_asc));

	for (int i = 0; i < 8; i++) {
		printf("%d ", (int)*ptrs[i]);
	}
	printf("\n");

	return 0;
}
