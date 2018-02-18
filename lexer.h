#include "lexerDef.h"

tokenList* tokenize(FILE* fp,tokenList *tkList);

void print(tokenList t);

void printToken(token* tk);

char* renewBuffer(char* b);

token* fillStruct(char* b,char* f,char* valuebuffer,char* s,int line_no);

char* retract(char* forward);

int checkKeyWord(char* b,char* f,char* valuebuffer);

char* extractWord(char* b,char* f,char* valuebuffer);

FILE* fillBuffer(FILE* fp,char* buffer);

token* getNextToken(tokenList* tkList);

tokenList* addtoTkList(token* tk,tokenList* tkList);