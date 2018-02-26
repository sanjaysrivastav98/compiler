//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexer.h"
#include "parser.h"

int main(int argc,char** argv){
	int n,i;
	error=0;
	printf("FIRST and FOLLOW set automated\nBoth lexical and syntax analysis modules implemented with Error Handling\nAll test Cases are working\n");
	printf("Enter an option:\n");
	scanf("%d",&n);
	FILE* fp;
	Grammar g;
	ffNode first,follow,synch;
	parseTree p;
	parseTable M;
	tokenList tkList;
	if(n==1){
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
		// printParseTable(M);
		p=pred_parsing(tkList,M,g,synch);
		if(error==0){
			printf("Compilation Successful\n");
		}
		else{
			printf("Compiled with errors\n");
		}
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