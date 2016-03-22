#include <stdio.h>
#include "bst.h"

int main(int argc, char *argv[])
{
	BST *tree, *found;

	tree = BST_create(20);
	BST_add(tree, 12);
	BST_add(tree, 29);

	found = BST_search(tree, 12);
	printf("Found node containing %d\n", found->val);

	BST_destroy(tree);
	return 0;
}
