typedef struct astnode{
    char* name;
    parseTree p;
    struct astnode* children;
    struct astnode* next;
    struct astnode* par;
}astnode;

typedef astnode* astNode;

typedef struct stnode{
    char* var_name;
    char* type;
    int offset;
    struct stnode* next;
}stnode;

typedef struct stnode* stNode;

typedef struct st_hashtable{
    char* scope;
    int size;
    stNode* s;
}st_hashtable;

typedef struct st_hashtable* st_hashTable;

typedef struct symboltable{
    st_hashTable ht;
    struct symboltable* next;
    struct symboltable* children;
}symboltable;

typedef struct symboltable* symbolTable;