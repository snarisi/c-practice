#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedlist LinkedList;
typedef struct node Node;

LinkedList *LinkedList_create(void);
void LinkedList_addtotail(LinkedList *, char *, char *);
void LinkedList_addtohead(LinkedList *, char *, char *);
void LinkedList_insert(LinkedList *, int, char *, char *);
void LinkedList_print(LinkedList *);
void LinkedList_destroy(LinkedList *);

Node *Node_create(char *, char *);
void Node_destroyall(Node *node);

struct linkedlist {
	Node *head;
};

struct node {
	char *key;
	char *val;
	Node *next;
};

LinkedList *LinkedList_create(void)
{
	LinkedList *newlist = malloc(sizeof(LinkedList));
	newlist->head = NULL;

	return newlist;
}

void LinkedList_addtotail(LinkedList *list, char *key, char *val)
{
	Node *newnode = Node_create(key, val);
	
	if (!list->head) {
		list->head = newnode;
		return;
	}

	Node *p = list->head;
	while (p->next != NULL) p = p->next;
	p->next = newnode;
}

void LinkedList_addtohead(LinkedList *list, char *key, char *val)
{
	Node *newnode, *temp;

	newnode = Node_create(key, val);
	temp = list->head;

	list->head = newnode;
	newnode->next = temp;
}

void LinkedList_insert(LinkedList *list, int pos, char *key, char *val)
{
	if (pos == 0) return LinkedList_addtohead(list, key, val);
	
	Node *before, *after, *newnode;
	int i;

	after = list->head;
	before = after->next;

	for (i = pos; i > 1; i--) {
		after = after->next;
		before = before->next;
	}

	newnode = Node_create(key, val);

	after->next = newnode;
	newnode->next = before;
}

void LinkedList_print(LinkedList *list)
{
	Node *p = list->head;
	while(p) {
		printf("%s: %s\n", p->key, p->val);
		p = p->next;
	}
}

void LinkedList_destroy(LinkedList *list)
{
	Node_destroyall(list->head);
	free(list);
}

Node *Node_create(char *key, char *val)
{
	Node *newnode = malloc(sizeof(Node));
	newnode->key = strdup(key);
	newnode->val = strdup(val);
	newnode->next = NULL;

	return newnode;
}

void Node_destroyall(Node *node)
{
	free(node->key);
	free(node->val);
	if (node->next) Node_destroyall(node->next);
	free(node);
}
