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

tokenList* tokenize(FILE* fp,tokenList *tkList);

void print(tokenList t);

void printToken(token* tk);

char* renewBuffer(char* b);

token* fillStruct(char* b,char* f,char* valuebuffer,char* s,int line_no);

void retract();

int checkKeyWord(char* b,char* f,char* valuebuffer);

char* extractWord(char* b,char* f,char* valuebuffer);

FILE* fillBuffer(FILE* fp,char* buffer);

token* getNextToken(tokenList* tkList);

tokenList* addtoTkList(token* tk,tokenList* tkList);