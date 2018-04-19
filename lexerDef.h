//K S Sanjay Srivastav 
//2015A7PS0102P
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token
{
	char token_id[10];
	char* value;
	int line_no;
}token;
typedef token* Token;


typedef struct tokennode{
	Token tk;
	struct tokennode* next;
}tokennode;
typedef tokennode* tokenNode;

typedef struct tokenlist{
	tokenNode head;
	tokenNode tail;
}tokenlist;

typedef tokenlist* tokenList;

typedef struct keyword{
	char* name;
	struct keyword* next; 
}keyword;
typedef keyword* keyWord;

keyWord keyHash[33];
extern FILE* errorFile;
int error;
