#include "parser.h"

Grammar* readGrammar(FILE* fp){
	fp=fopen("grammar.txt","r");
	Grammar* g;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int j;
	char* lhs,*rhs,*saveptr1,*str1,*token,*p;
	lhs=(char*)malloc(sizeof(char)*22);
	rhs=(char*)malloc(sizeof(char)*100);
	while ((read = getline(&line, &len, fp)) != -1) {
		lhs=(char*)malloc(sizeof(char)*22);
		for (j = 1, str1 = line; ; j++, str1 = NULL) {
			token = strtok_r(str1," ", &saveptr1);
			if (token == NULL)
				break;
			printf("%s\n",token);
			rhs=(char*)malloc(sizeof(char)*100);
			break;
		}
	}
	return g;
}

int main(){
	Grammar* g;
	FILE* fp;
	g=readGrammar(fp);
	return 0;
}