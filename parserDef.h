	//K S Sanjay Srivastav 
//2015A7PS0102P
typedef struct node{
	int num;
	char isTerminal;
	struct nodelist** head;
	int numOfRules;
}node;

typedef node* Node;

typedef struct nodelist
{
	Node n;
	struct nodelist* next;
}nodelist;

typedef nodelist* nodeList;

typedef Node* Grammar;

typedef unsigned long int* ffNode;

typedef nodeList** parseTable;

char** map_nt;
char** map_t;
int gc_nt;
int gc_t;
int* hashMap_nt;
int* hashMap_t;

typedef struct parsetree
{
	Node n;
	Token tk;
	struct parsetree* children;
	struct parsetree* next;
	struct parsetree* par;
}parsetree;

typedef parsetree* parseTree;

typedef struct stack{
	parseTree p;
	struct stack* next;
}stack;

typedef stack* Stack;
