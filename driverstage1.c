//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "symbolTable.h"

int main(int argc,char** argv){
	int n,i,s1,s2;
	error=0;
	// printf("FIRST and FOLLOW set automated\nBoth lexical and syntax analysis modules implemented with Error Handling\nAll test Cases are working\n");
	// printf("Enter an option:\n");
	scanf("%d",&n);
	FILE* fp;
	Grammar g;
	ffNode first,follow,synch;
	parseTree p;
	parseTable M;
	tokenList tkList;
	astNode ast=NULL; 
	symbolTable st=NULL;
	if(n==0){
		fillKeyHash();
		fp=fopen(argv[1],"r");
		tkList=(tokenList)malloc(sizeof(tokenlist));
		tkList=tokenize(fp,tkList);
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
		if(error==0){
			printf("Compilation Successful\n");
		}
		else{
			printf("Compiled with errors\n");
		}
		printParseTree(p,argv[2]);
		ast=(astNode)malloc(sizeof(astnode));
		ast->name=(char*)malloc(sizeof(char)*5);
		strcpy(ast->name,"MAIN");
		ast->next=NULL;
		ast->p=NULL;
		ast->children=buildAstTree(p);
		printAstTree(ast);
		st=buildST(ast);
		printST(st);
		s1=cal_sizeP(p);
		s2=cal_sizeA(ast);
		printf("%d %d\n",s1,s2);
		fclose(fp);
	}
	else if(n==1){
		removeComments(argv[1]);
	}
	else if(n==2){
		fp=fopen(argv[1],"r");
		fillKeyHash();
		tkList=(tokenList)malloc(sizeof(tokenlist));
		tkList=tokenize(fp,tkList);
		print(tkList);
		fclose(fp);
	}
	else if(n==3){
		fillKeyHash();
		fp=fopen(argv[1],"r");
		tkList=(tokenList)malloc(sizeof(tokenlist));
		tkList=tokenize(fp,tkList);
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
		printParseTable(M);
		p=pred_parsing(tkList,M,g,synch);
		// if(error==0){
		// 	printf("Compilation Successful\n");
		// }
		// else{
		// 	printf("Compiled with errors\n");
		// }
		fclose(fp);
	}
	else if(n==4){
		fillKeyHash();
		fp=fopen(argv[1],"r");
		tkList=(tokenList)malloc(sizeof(tokenlist));
		tkList=tokenize(fp,tkList);
		g=readGrammar();
		// printGrammar(g);
		first=getFirstSet(g);
		// printFF(ff);
		follow=getFollowSet(g,first);
		synch=(unsigned long int*)malloc(44*sizeof(unsigned long int));
		for(i=0;i<44;i++){
			synch[i]=follow[i];
		}
		// printFF(follow);
		M=buildParseTable(g,first,follow);
		// printParseTable(M);
		p=pred_parsing(tkList,M,g,synch);
		if(error==0){
			printf("Compilation Successful\n");
		}
		else{
			printf("Compiled with errors\n");
		}
		printParseTree(p,argv[2]);
		fclose(fp);
	}
	return 0;
}