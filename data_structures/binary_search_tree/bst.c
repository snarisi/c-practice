#include <stdio.h>
#include "bst.h"

int main(int argc, char *argv[])
{
	BST *tree, *found;

	tree = BST_create(20);
	BST_add(tree, 12);
	BST_add(tree, 29);
	BST_add(tree, 5);
	BST_add(tree, 90);
	BST_add(tree, 14);
	BST_add(tree, 49);
	
	BST_print(tree);

	found = BST_search(tree, 12);
	printf("Found node containing %d\n", found->val);

	BST_destroy(tree);
	return 0;
}
