#include "lexer.h"

typedef struct node{
	char* name;
	char isTerminal;
	struct nodeList* head;
}node;

typedef struct nodeList
{
	node* n;
	node* next;
}nodelist;

typedef node Grammar[85];