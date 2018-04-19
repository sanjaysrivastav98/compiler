//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexer.h"
#include "parser.h"
// #include "ast.h"
#include "symbolTable.h"

int main(int argc,char** argv){
	int n,i,s1,s2;
    int *flag= (int*)calloc(8,sizeof(int));
	error=0;
	// printf("FIRST and FOLLOW set automated\nBoth lexical and syntax analysis modules implemented with Error Handling\nAll test Cases are working\n");
	// printf("Enter an option:\n");
    printf("Enter an option:");
    scanf("%d",&n);
	FILE* fp,*fp1,*fp2;
	Grammar g;
	ffNode first,follow,synch;
	parseTree p;
	parseTable M;
	tokenList tkList,tkList1;
	astNode ast=NULL; 
	symbolTable st=NULL;
    fp=fopen(argv[1],"r");
    while(n!=0){
        switch(n){
            case 1:
                if(flag[1]==0){
                    fillKeyHash();
                    tkList=(tokenList)malloc(sizeof(tokenlist));
                    tkList=tokenize(fp,tkList);
                    tkList1=copyTokenList(tkList);
                    flag[1]=1;
                }
                print(tkList1);
                break;
            case 2:
                if(flag[2]==0){
                    if(flag[1]==0){
                        fillKeyHash();
                        tkList=(tokenList)malloc(sizeof(tokenlist));
                        tkList=tokenize(fp,tkList);
                        tkList1=copyTokenList(tkList);
                        flag[1]=1;
                    }
                    g=readGrammar(fp);
                    // printGrammar(g);
                    first=getFirstSet(g);
                    // printFF(first);
                    follow=getFollowSet(g,first);
                    synch=(unsigned long int*)malloc(44*sizeof(unsigned long int));
                    for(i=0;i<44;i++){
                        synch[i]=follow[i];
                    }
                    // printFF(follow);
                    M=buildParseTable(g,first,follow);
                    // printParseTable(M);
                    p=pred_parsing(tkList,M,g,synch);
                    flag[2]=1;
                }
                if(error==0){
                    printf("Compilation Successful\n");
                }
                else{
                    printf("Compiled with errors\n");
                }
                printParseTree(p,"stdout");
                break;
            case 3:
                if(flag[3]==0){
                    if(flag[2]==0){
                        if(flag[1]==0){
                            fillKeyHash();
                            tkList=(tokenList)malloc(sizeof(tokenlist));
                            tkList=tokenize(fp,tkList);
                            tkList1=copyTokenList(tkList);
                            flag[1]=1;
                        }
                        g=readGrammar(fp);
                        // printGrammar(g);
                        first=getFirstSet(g);
                        // printFF(first);
                        follow=getFollowSet(g,first);
                        synch=(unsigned long int*)malloc(44*sizeof(unsigned long int));
                        for(i=0;i<44;i++){
                            synch[i]=follow[i];
                        }
                        // printFF(follow);
                        M=buildParseTable(g,first,follow);
                        // printParseTable(M);
                        p=pred_parsing(tkList,M,g,synch);
                        flag[2]=1;
                    }
                    ast=(astNode)malloc(sizeof(astnode));
                    ast->name=(char*)malloc(sizeof(char)*5);
                    strcpy(ast->name,"MAIN");
                    ast->next=NULL;
                    ast->p=NULL;
                    ast->children=buildAstTree(p);
                    flag[3]=1;
                }
                if(error==0){
                    printf("Compilation Successful\n");
                }
                else{
                    printf("Compiled with errors\n");
                }
                printf("Traversal of AST: <parent><allchildren><sibling> order\n");
                printAstTree(ast);
                break;
            case 4:
                if(flag[4]==0){
                    if(flag[3]==0){
                        if(flag[2]==0){
                            if(flag[1]==0){
                                fillKeyHash();
                                tkList=(tokenList)malloc(sizeof(tokenlist));
                                tkList=tokenize(fp,tkList);
                                tkList1=copyTokenList(tkList);
                                flag[1]=1;
                            }
                            g=readGrammar(fp);
                            // printGrammar(g);
                            first=getFirstSet(g);
                            // printFF(first);
                            follow=getFollowSet(g,first);
                            synch=(unsigned long int*)malloc(44*sizeof(unsigned long int));
                            for(i=0;i<44;i++){
                                synch[i]=follow[i];
                            }
                            // printFF(follow);
                            M=buildParseTable(g,first,follow);
                            // printParseTable(M);
                            p=pred_parsing(tkList,M,g,synch);
                            flag[2]=1;
                        }
                        ast=(astNode)malloc(sizeof(astnode));
                        ast->name=(char*)malloc(sizeof(char)*5);
                        strcpy(ast->name,"MAIN");
                        ast->next=NULL;
                        ast->p=NULL;
                        ast->children=buildAstTree(p);
                        flag[3]=1;
                    }
                    st=buildST(ast);
                    flag[4]=1;
                }
                printST(st);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
        }
        printf("Enter an option:");
        scanf("%d",&n);
    }
    return 0;
}