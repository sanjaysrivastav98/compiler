//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexer.h"
#include "parser.h"
// #include "ast.h"
#include "symbolTable.h"

FILE* errorFile;
int main(int argc,char** argv){
	int n,i,s1,s2;
    int *flag= (int*)calloc(8,sizeof(int));
	error=0;
    errorFile=fopen("errorFile.txt","w");
    fclose(errorFile);
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
    size_t len = 0;
	ssize_t read;
    char * line = NULL;
    fp=fopen(argv[1],"r");
    while(n!=0){
        switch(n){
            case 1:
                if(flag[1]==0){
                    errorFile=fopen("errorFile.txt","a");    
                    fillKeyHash();
                    tkList=(tokenList)malloc(sizeof(tokenlist));
                    tkList=tokenize(fp,tkList);
                    tkList1=copyTokenList(tkList);
                    flag[1]=1;
                    fclose(errorFile);
                }
                print(tkList1);
                break;
            case 2:
                if(flag[2]==0){
                    if(flag[1]==0){
                        errorFile=fopen("errorFile.txt","a");                        
                        fillKeyHash();
                        tkList=(tokenList)malloc(sizeof(tokenlist));
                        tkList=tokenize(fp,tkList);
                        tkList1=copyTokenList(tkList);
                        fclose(errorFile);
                        flag[1]=1;
                    }
                    errorFile=fopen("errorFile.txt","a");                                            
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
                    fclose(errorFile);
                }
                if(error==0){
                    printf("Compilation Successful\n");
                }
                else{
                    printf("Compiled with errors\n");
                }
                errorFile=fopen("errorFile.txt","r");
                while((read=getline(&line,&len,errorFile))!=-1){
                    printf("%s",line);
                }
                fclose(errorFile);
                printParseTree(p,"stdout");
                break;
            case 3:
                if(flag[3]==0){
                    if(flag[2]==0){
                        if(flag[1]==0){
                            errorFile=fopen("errorFile.txt","a");                        
                            fillKeyHash();
                            tkList=(tokenList)malloc(sizeof(tokenlist));
                            tkList=tokenize(fp,tkList);
                            tkList1=copyTokenList(tkList);
                            flag[1]=1;
                            fclose(errorFile);
                        }
                        errorFile=fopen("errorFile.txt","a");                                                
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
                        fclose(errorFile);
                    }
                    if(error!=0){
                        printf("Compiled with Syntax errors. Couldn't generate AST\n");
                        break;
                    }
                    errorFile=fopen("errorFile.txt","a");                                            
                    ast=(astNode)malloc(sizeof(astnode));
                    ast->name=(char*)malloc(sizeof(char)*5);
                    strcpy(ast->name,"MAIN");
                    ast->next=NULL;
                    ast->p=NULL;
                    ast->children=buildAstTree(p);
                    flag[3]=1;
                    fclose(errorFile);
                }
                if(error==0){
                    printf("Compilation Successful\n");
                }
                else{
                    printf("Compiled with Syntax errors. AST couldn't be generated\n");
                    break;
                }
                printf("Traversal of AST: <parent><allchildren><sibling> order\n");
                printAstTree(ast);
                break;
            case 4:
                if(flag[4]==0){
                    if(flag[3]==0){
                        if(flag[2]==0){
                            if(flag[1]==0){
                                errorFile=fopen("errorFile.txt","a");                                            
                                fillKeyHash();
                                tkList=(tokenList)malloc(sizeof(tokenlist));
                                tkList=tokenize(fp,tkList);
                                tkList1=copyTokenList(tkList);
                                flag[1]=1;
                                fclose(errorFile);
                            }
                            errorFile=fopen("errorFile.txt","a");                                                                
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
                            fclose(errorFile);
                        }
                        if(error!=0){
                            printf("Compiled with Syntax errors. Couldn't generate AST\n");
                            printf("Parse Tree Number of nodes = %d\t Allocated memory = %lu Bytes\n",cal_sizeP(p),cal_sizeP(p)*sizeof(parsetree));
                            break;
                        }
                        errorFile=fopen("errorFile.txt","a");                                            
                        ast=(astNode)malloc(sizeof(astnode));
                        ast->name=(char*)malloc(sizeof(char)*5);
                        strcpy(ast->name,"MAIN");
                        ast->next=NULL;
                        ast->p=NULL;
                        ast->children=buildAstTree(p);
                        flag[3]=1;
                        fclose(errorFile);
                    }
                    if(error!=0){
                        printf("Code has Syntax errors.Couldn't generate AST\n");
                        while((read=getline(&line,&len,errorFile))!=-1){
                            printf("%s",line);
                        }
                        printf("Parse Tree Number of nodes = %d\t Allocated memory = %lu Bytes\n",cal_sizeP(p),cal_sizeP(p)*sizeof(parsetree));
                        break;
                    }
                    flag[4]=1;
                }
                double f = 100*(((double)(cal_sizeP(p)*sizeof(parsetree))-(double)(cal_sizeA(ast)*sizeof(astnode))))/((double)(cal_sizeP(p)*sizeof(parsetree)));
                printf("Parse Tree Number of nodes = %d\t Allocated memory = %lu Bytes\n",cal_sizeP(p),cal_sizeP(p)*sizeof(parsetree));
                printf("AST Number of nodes = %d\t         Allocated memory = %lu Bytes\n",cal_sizeA(ast),cal_sizeA(ast)*sizeof(astnode));
                printf("Compression Ratio = %f\n",f);
                break;
            case 5:
                if(flag[5]==0){
                    if(flag[4]==0){
                        if(flag[3]==0){
                            if(flag[2]==0){
                                if(flag[1]==0){
                                    errorFile=fopen("errorFile.txt","a");                                            
                                    fillKeyHash();
                                    tkList=(tokenList)malloc(sizeof(tokenlist));
                                    tkList=tokenize(fp,tkList);
                                    tkList1=copyTokenList(tkList);
                                    flag[1]=1;
                                    fclose(errorFile);
                                }
                                errorFile=fopen("errorFile.txt","a");                                                                
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
                                fclose(errorFile);
                            }
                            if(error!=0){
                                printf("Compiled with Syntax errors. Couldn't generate AST\n");
                                break;
                            }
                            errorFile=fopen("errorFile.txt","a");                                            
                            ast=(astNode)malloc(sizeof(astnode));
                            ast->name=(char*)malloc(sizeof(char)*5);
                            strcpy(ast->name,"MAIN");
                            ast->next=NULL;
                            ast->p=NULL;
                            ast->children=buildAstTree(p);
                            flag[3]=1;
                            fclose(errorFile);
                        }
                        if(error!=0){
                            printf("Code has Syntax errors. Couldn't generate AST and Symbol Table\n");
                            break;
                        }
                        flag[4]=1;
                    }
                    errorFile=fopen("errorFile.txt","a");                                                                
                    st=buildST(ast);
                    flag[5]=1;
                    fclose(errorFile);
                }
                if(error!=0){
                    printf("Code has Syntax errors. Couldn't generate AST and Symbol Table\n");
                    break;
                }
                printST(st);
                break;
            case 6:
                if(flag[4]==0){
                    if(flag[3]==0){
                        if(flag[2]==0){
                            if(flag[1]==0){
                                errorFile=fopen("errorFile.txt","a");                                            
                                fillKeyHash();
                                tkList=(tokenList)malloc(sizeof(tokenlist));
                                tkList=tokenize(fp,tkList);
                                tkList1=copyTokenList(tkList);
                                flag[1]=1;
                                fclose(errorFile);
                            }
                            errorFile=fopen("errorFile.txt","a");                                                                
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
                            fclose(errorFile);
                        }
                        if(error!=0){
                            printf("Compiled with Syntax errors. Couldn't generate AST\n");
                            errorFile=fopen("errorFile.txt","r");
                            while((read=getline(&line,&len,errorFile))!=-1){
                                printf("%s",line);
                            }
                            fclose(errorFile);
                            break;
                        }
                        errorFile=fopen("errorFile.txt","a");                                            
                        ast=(astNode)malloc(sizeof(astnode));
                        ast->name=(char*)malloc(sizeof(char)*5);
                        strcpy(ast->name,"MAIN");
                        ast->next=NULL;
                        ast->p=NULL;
                        ast->children=buildAstTree(p);
                        flag[3]=1;
                        fclose(errorFile);
                    }
                    if(error!=0){
                        printf("Code has Syntax errors.Couldn't generate AST\n");
                        errorFile=fopen("errorFile.txt","r");
                        while((read=getline(&line,&len,errorFile))!=-1){
                            printf("%s",line);
                        }
                        fclose(errorFile);
                        break;
                    }
                    flag[4]=1;
                }
                if(error==0){
                    printf("No Syntax errors in this file\n");
                }
                errorFile=fopen("errorFile.txt","r");
                while((read=getline(&line,&len,errorFile))!=-1){
                    printf("%s",line);
                }
                fclose(errorFile);
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