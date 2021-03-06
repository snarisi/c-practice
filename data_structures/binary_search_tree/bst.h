#include <stdio.h>
#include <stdlib.h>

typedef struct bst BST;

BST *BST_create(int);
void BST_add(BST *, int);
BST *BST_search(BST *, int);
void BST_print(BST *);
void BST_print_recur(BST *, int);
void BST_destroy(BST *);

struct bst {
	int val;
	BST *left;
	BST *right;
};

BST *BST_create(int val)
{
	BST *newbst;

	newbst = malloc(sizeof(BST));
	newbst->val = val;
	newbst->left = NULL;
	newbst->right = NULL;

	return newbst;
}

void BST_add(BST *tree, int val)
{
	if (val < tree->val) {
		if (tree->left) BST_add(tree->left, val);
		else tree->left = BST_create(val);
	} else {
		if (tree->right) BST_add(tree->right, val);
		else tree->right = BST_create(val);
	}
}

BST *BST_search(BST *tree, int val)
{
	BST *p;
	p = tree;

	while (p) {
		if (val < p->val) p = p->left;
		else if (val > p->val) p = p->right;
		else return p;
	}
	return NULL;
}

void BST_destroy(BST *tree)
{
	if (!tree) return;
	BST_destroy(tree->right);
	BST_destroy(tree->left);
	free(tree);
}

// Prints tree, with root node farthest to the left
void BST_print(BST *tree)
{
	BST_print_recur(tree, 4);
}

void BST_print_recur(BST *tree, int space)
{
	if (!tree) return;

	BST_print_recur(tree->right, space + 4);
	printf("%*d\n", space, tree->val);
	BST_print_recur(tree->left, space + 4);
}
