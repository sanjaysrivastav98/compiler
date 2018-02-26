//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexerDef.h"

tokenList tokenize(FILE* fp,tokenList tkList);

void print(tokenList t);

void printToken(Token tk);

char* renewBuffer(char* b);

Token fillStruct(char* b,char* f,char* valuebuffer,char* s,int line_no);

char* retract(char* forward);

int checkKeyWord(char* b,char* f,char* valuebuffer);

char* extractWord(char* b,char* f,char* valuebuffer);

FILE* getStream(FILE* fp,char* buffer);

Token getNextToken(tokenList tkList);

tokenList addtoTkList(Token tk,tokenList tkList);

void removeComments(char* filename);

int hash(char *str,int m);

void fillKeyHash();