//K S Sanjay Srivastav 
//2015A7PS0102P
#include "parserDef.h"

char** lhsAndRhs(char* line);

Grammar fillRule(char* lhs,char* rhs,Grammar g);

Grammar fillGrammarTable(char* line,Grammar g);

Grammar readGrammar();

void printGrammar(Grammar g);

unsigned long int set(int n,unsigned long int t);

unsigned long int Union(unsigned long int a,unsigned long int b);

int in(int n,unsigned long int t);

unsigned long int Remove(int n, unsigned long int t);

ffNode FIRST(int nt,Grammar g,ffNode f);

ffNode getFirstSet(Grammar g);

void printFF(ffNode f);

int noChanges(unsigned long int* now,unsigned long int* prev);

void copy(unsigned long int* now,unsigned long int* prev);

ffNode getFollowSet(Grammar g,ffNode first);

parseTable buildParseTable(Grammar g,ffNode first,ffNode follow);

void printParseTable(parseTable p);

Stack pop(Stack s);

Node top(Stack s);

void insert(nodeList n,parseTree* p,Stack* s);

void printTree(parseTree p,FILE* fp);

parseTree pred_parsing(tokenList tk,parseTable M,Grammar g,unsigned long int* synch);

void printParseTree(parseTree PT, char *outfile);
