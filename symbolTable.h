#include "ast.h"

int ht_size;

symbolTable insertToHT(symbolTable st,astNode root,int* offset);
symbolTable buildST(astNode root);
matSize getOffset(astNode s,matSize m);
void printST(symbolTable st);
int checkinHash(symbolTable st,char* name);