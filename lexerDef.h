#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	char token_id[10];
	char* value;
	int line_no;
}token;


typedef struct{
	token *tk;
	struct tokenNode* next;
}tokenNode;

typedef struct tokenList{
	tokenNode* head;
}tokenList;