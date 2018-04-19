//K S Sanjay Srivastav
// 2015A7PS0102P
#include "lexer.h"
#include "parserDef.h"

//Split one line in the grammar.txt into lhs and rhs
char** lhsAndRhs(char* line){
	char** res=(char**)malloc(2*sizeof(char*));
	res[0]=(char*)malloc(24*sizeof(char));
	res[1]=(char*)malloc(240*sizeof(char));
	char* temp=line;
	int i=0;
	while(temp[i]!='\0'){
		res[0][i]=temp[i];
		if(temp[i]==' ' && temp[i+1]=='='&& temp[i+2]=='=' && temp[i+3]=='=' && temp[i+4]=='>' && temp[i+5]==' '){
			res[0][i]='\0';
			strcpy(res[1],&line[i+6]);
			break;
		}		
		i++;
	}
	return res;
}

//Split the right hand side of one rule into terminals and non-terminals and save it in linked lists.
Grammar fillRule(char* lhs,char* rhs,Grammar g){
	// printf("%s===>%s\n",lhs,rhs);
	char** rhsList=(char**)malloc(sizeof(char*));
	rhsList[0]=(char*)malloc(23*sizeof(char));
	int i=0,h,h2,j;
	int m=244,n=186;
	h=hashMap_nt[hash(lhs,m)];
	nodeList temp=NULL,temp2=NULL;

	if(g[h]==NULL){
		g[h]=(Node)malloc(sizeof(node));
		g[h]->num=h;
		// strcpy(g[h]->name,lhs);
		g[h]->isTerminal='f';
		g[h]->head=NULL;
		g[h]->numOfRules=0;
		if((rhsList[0]=strtok(rhs," \n"))!=NULL){
			i++;
			g[h]->head=(nodeList*)malloc(sizeof(nodeList));
			g[h]->head[0]=(nodeList)malloc(sizeof(nodelist));
			temp=g[h]->head[0];
			g[h]->numOfRules=1;
			temp->n=(Node)malloc(sizeof(node));
			temp->next=NULL;
			
			if(rhsList[0][0]=='<'){
				h2=hash(rhsList[0],m);
				temp->n->isTerminal='f';
				if(hashMap_nt[h2]==-1){
					hashMap_nt[h2]=gc_nt;
					map_nt[gc_nt]=(char*)malloc(23*sizeof(char));
					strcpy(map_nt[gc_nt],rhsList[0]);
					gc_nt++;
				}
				temp->n->num=hashMap_nt[h2];
			}
			else{
				temp->n->isTerminal='t';
				h2=hash(rhsList[0],n);
				if(hashMap_t[h2]==-1){
					hashMap_t[h2]=gc_t;
					map_t[gc_t]=(char*)malloc(23*sizeof(char));
					strcpy(map_t[gc_t],rhsList[0]);
					gc_t++;
				}
				temp->n->num=hashMap_t[h2];
			}
			rhsList=realloc(rhsList,(i+1)*sizeof(char*));
			rhsList[i]=(char*)malloc(23*sizeof(char));
			while((rhsList[i]=strtok(NULL," \n"))!=NULL){
				i++;
				temp->next=(nodeList)malloc(sizeof(nodelist));
				temp=temp->next;
				temp->n=(Node)malloc(sizeof(node));
				temp->next=NULL;
				// temp->n->name=rhsList[i-1];
				if(rhsList[i-1][0]=='<'){
					temp->n->isTerminal='f';
					h2=hash(rhsList[i-1],m);
					if(hashMap_nt[h2]==-1){
						hashMap_nt[h2]=gc_nt;
						map_nt[gc_nt]=(char*)malloc(23*sizeof(char));
						strcpy(map_nt[gc_nt],rhsList[i-1]);
						gc_nt++;
					}
					temp->n->num=hashMap_nt[h2];
				}
				else{
					temp->n->isTerminal='t';
					h2=hash(rhsList[i-1],n);
					if(hashMap_t[h2]==-1){
						hashMap_t[h2]=gc_t;
						map_t[gc_t]=(char*)malloc(23*sizeof(char));
						strcpy(map_t[gc_t],rhsList[i-1]);
						gc_t++;
					}
					temp->n->num=hashMap_t[h2];
				}
				rhsList=realloc(rhsList,(i+1)*sizeof(char*));
				rhsList[i]=(char*)malloc(sizeof(char)*23);
			}
		}
	}
	else{
		g[h]->numOfRules++;
		g[h]->head=(nodeList*)realloc(g[h]->head,g[h]->numOfRules*sizeof(nodeList));
		g[h]->head[g[h]->numOfRules-1]=(nodeList)malloc(sizeof(nodelist));
		temp=g[h]->head[g[h]->numOfRules-1];
		if((rhsList[0]=strtok(rhs," \n"))!=NULL){
			i++;
			temp->n=(Node)malloc(sizeof(node));
			temp->next=NULL;
			// temp->n->name=rhsList[i-1];
			if(rhsList[0][0]=='<'){
				temp->n->isTerminal='f';
				h2=hash(rhsList[0],m);
				if(hashMap_nt[h2]==-1){
					hashMap_nt[h2]=gc_nt;
					map_nt[gc_nt]=(char*)malloc(23*sizeof(char));
					strcpy(map_nt[gc_nt],rhsList[0]);
					gc_nt++;
				}
				temp->n->num=hashMap_nt[h2];
			}
			else{
				temp->n->isTerminal='t';
				h2=hash(rhsList[0],n);
				if(hashMap_t[h2]==-1){
					hashMap_t[h2]=gc_t;
					map_t[gc_t]=(char*)malloc(23*sizeof(char));
					strcpy(map_t[gc_t],rhsList[0]);
					gc_t++;
				}
				temp->n->num=hashMap_t[h2];
			}
			rhsList=realloc(rhsList,(i+1)*sizeof(char*));
			rhsList[i]=(char*)malloc(23*sizeof(char));
			while((rhsList[i]=strtok(NULL," \n"))!=NULL){
				i++;
				temp->next=(nodeList)malloc(sizeof(nodelist));
				temp=temp->next;
				temp->n=(Node)malloc(sizeof(node));
				temp->next=NULL;
				// temp->n->name=rhsList[i-1];
				if(rhsList[i-1][0]=='<'){
					temp->n->isTerminal='f';
					h2=hash(rhsList[i-1],m);
					if(hashMap_nt[h2]==-1){
						hashMap_nt[h2]=gc_nt;
						map_nt[gc_nt]=(char*)malloc(23*sizeof(char));
						strcpy(map_nt[gc_nt],rhsList[i-1]);
						gc_nt++;
					}
					temp->n->num=hashMap_nt[h2];
				}
				else{
					temp->n->isTerminal='t';
					h2=hash(rhsList[i-1],n);
					if(hashMap_t[h2]==-1){
						hashMap_t[h2]=gc_t;
						map_t[gc_t]=(char*)malloc(23*sizeof(char));
						strcpy(map_t[gc_t],rhsList[i-1]);
						gc_t++;
					}
					temp->n->num=hashMap_t[h2];
				}
				rhsList=realloc(rhsList,(i+1)*sizeof(char*));
				rhsList[i]=(char*)malloc(sizeof(char)*23);

			}
		}
	}
	return g;
}

//Take a line in the grammar and fill the grammar table
Grammar fillGrammarTable(char* line,Grammar g){
	char **res,**rules;
	char *lhs,*rhs;
	res=lhsAndRhs(line);
	lhs=res[0];
	rhs=res[1];
	rules=(char**)malloc(sizeof(char*));
	int i=0,len=strlen(rhs)+1,m=244;
	rules[i]=(char*)malloc(sizeof(char)*len);
	int h=hash(lhs,m);
	if(hashMap_nt[h]==-1){
		hashMap_nt[h]=gc_nt;
		map_nt[gc_nt]=(char*)malloc(23*sizeof(char));
		strcpy(map_nt[gc_nt],lhs);
		gc_nt++;
	}
	if((rules[i]=strtok(rhs,"|"))!=NULL){
		i++;
		rules=realloc(rules,(i+1)*sizeof(char*));
		rules[i]=(char*)malloc(sizeof(char)*len);
		while((rules[i]=strtok(NULL,"|"))!=NULL){
			i++;
			rules=realloc(rules,(i+1)*sizeof(char*));
			rules[i]=(char*)malloc(sizeof(char)*len);
		}
	}
	int j;
	for(j=0;j<i;j++){
		g=fillRule(lhs,rules[j],g);
	}
	return g;
}

//Take a file pointer and populate the grammar.
Grammar readGrammar(){
	FILE* fp=fopen("grammar.txt","r");
	Grammar g;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int j,i,k,l;
	int m=244,n=186;
	gc_nt=0;
	gc_t=0;
	hashMap_nt=(int*)malloc(m*sizeof(int));
	hashMap_t=(int*)malloc(n*sizeof(int));
	map_nt=(char**)malloc(44*sizeof(char*));
	map_t=(char**)malloc(40*sizeof(char*));
	for(i=0;i<m;i++){
		if(i<n){
			if(i<39)
				map_t[i]=NULL;
			hashMap_t[i]=-1;
		}
		hashMap_nt[i]=-1;
		if(i<44)
			map_nt[i]=NULL;
	}
	map_t[39]=(char*)malloc(2);
	strcpy(map_t[39],"$");
	hashMap_t[hash("$",n)]=39;
	g=(Grammar)malloc(m*sizeof(Node));
	char* lhs,*rhs,*saveptr1,*str1,*token,*p;
	char** res,**rules,**rhs1;
	int count,temp_count=0;
	nodelist* temp;
	while ((read = getline(&line, &len, fp)) != -1) {
		g=fillGrammarTable(line,g);
	}
	fclose(fp);
	return g;
}

void printGrammar(Grammar g){
	int i,j,k=0;
	nodeList temp;
	for(i=0;i<44;i++){
		// if(g[i]==NULL) continue;
		for(j=0;j<g[i]->numOfRules;j++){
			temp=g[i]->head[j];
			printf("%s ===> ",map_nt[g[i]->num]);
			while(temp!=NULL){
				if(temp->n->isTerminal=='t'){
					printf("%s ",map_t[temp->n->num] );
				}
				else {
					printf("%s ",map_nt[temp->n->num] );
				}
				temp=temp->next;
			}
			k++;
			printf("\n");
		}
	}
	// printf("%d\n",k);
}

unsigned long int set(int n,unsigned long int t){
	int i=0;
	unsigned long int temp=1;
	temp=temp<<n;
	return t|temp;
}

unsigned long int Union(unsigned long int a,unsigned long int b){
	return a|b;
}

int in(int n,unsigned long int t){
	unsigned long int temp=1;
	temp=temp<<n;
	if((temp&t) != 0){
		return 1;
	}
	return 0;
}

unsigned long int Remove(int n, unsigned long int t){
	unsigned long int temp=1;
	temp=temp<<n;
	return t^temp;
}

ffNode FIRST(int nt,Grammar g,ffNode f){
	int m=244,n=186,i,j,k;
	int h=nt,h2,eps=hashMap_t[hash("eps",n)];
	nodeList temp=NULL;
	if(f[h]==0){
		for(i=0;i<g[h]->numOfRules;i++){
			temp=g[h]->head[i];
			h2=temp->n->num;
			if(temp->n->isTerminal=='t'){
				// h2=hashMap_t[hash(temp->n->name,n)];
				f[h]=set(h2,f[h]);
			}
			else{
				// h2=hashMap_nt[hash(temp->n->name,m)];
				if(f[h2]==0){
					f=FIRST(h2,g,f);
				}
				if(in(eps,f[h2])==1){
					f[h]=Union(f[h],Remove(eps,f[h2]));
					temp=temp->next;
					while(temp!=NULL && temp->n->isTerminal=='f' && in(eps,f[h2])){
						h2=temp->n->num;
						if(f[h2]==0) f=FIRST(h2,g,f);
						f[h]=Union(f[h],Remove(eps,f[h2]));
						temp=temp->next;					
					}
					if(temp!=NULL && temp->n->isTerminal=='f'){
						h2=temp->n->num;
						if(f[h2]==0) f=FIRST(h2,g,f);
						f[h]=Union(f[h],f[h2]);
					}
					else{
						f[h]=set(eps,f[h]);
					}
				}
				else{
					h2=temp->n->num;
					f[h]=Union(f[h],f[h2]);
				}
			}

		}
	}
	return f;
}

ffNode getFirstSet(Grammar g){
	int i=0,m=244,n=186;
	nodeList temp;
	ffNode f=(ffNode)calloc(44,sizeof(unsigned long int));
	for(i=0;i<44;i++){
		if(f[i]==0){
			f=FIRST(g[i]->num,g,f);
		}
	}
	return f;
}

void printFF(ffNode f){
	int i,h;
	unsigned long int temp;
	int j;
	int m=244,n=186;
	for(i=0;i<44;i++){
		printf("%s : {",map_nt[i]);
		temp=f[i];
		j=0;
		while(temp!=0){
			if(temp&1==1){
				printf("%s, ",map_t[j]);
			}	
			j++;
			temp=temp>>1;
		}
		printf("}\n");
	}
}

int noChanges(unsigned long int* now,unsigned long int* prev){
	int i,n;
	n=44;
	for(i=0;i<n;i++){
		if(now[i]!=prev[i])
			return 0;
	}
	return 1;
}

void copy(unsigned long int* now,unsigned long int* prev){
	int i,n;
	n=44;
	for(i=0;i<n;i++){
		now[i]=prev[i];
	}
}


ffNode getFollowSet(Grammar g,ffNode first){
	int i=0,m=244,n=186,k=0,j;
	ffNode f=(ffNode)calloc(44,sizeof(unsigned long int));
	ffNode prev=(ffNode)calloc(44,sizeof(unsigned long int));
	int h,h2,h3,eps=hashMap_t[hash("eps",n)],s=hashMap_t[hash("$",n)];
	nodeList temp=NULL,tempNext=NULL;
	while((noChanges(prev,f)==0)||(k==0)){
		copy(prev,f);
		f[0]=set(s,f[0]);
		for(j=0;j<44;j++){
			for(i=0;i<g[j]->numOfRules;i++){
				temp=g[j]->head[i];
				tempNext=temp->next;
				while(tempNext!=NULL){
					if(temp->n->isTerminal=='f'){
						h=temp->n->num;
						while(tempNext!=NULL){
							if(tempNext->n->isTerminal=='t'){
								h2=tempNext->n->num;
								f[h]=set(h2,f[h]);
								break;
							}
							else{
								h2=tempNext->n->num;
								if(in(eps,first[h2])==0){
									f[h]=Union(f[h],first[h2]);
									break;
								}
								else{
									f[h]=Union(f[h],Remove(eps,first[h2]));
								}	
							}
							tempNext=tempNext->next;
						}
						if(tempNext==NULL){
							f[h]=Union(f[h],f[j]);
						}
					}
					temp=temp->next;
					tempNext=temp->next;
				}
				if(temp->n->isTerminal=='f'){
					h=temp->n->num;
					f[h]=Union(f[h],f[j]);
				}
			}

		}
		k++;
		
	}
	// printf("%d\n",k );
	return f;
}

parseTable buildParseTable(Grammar g,ffNode first,ffNode follow){
	int m=244,n=186;
	int i,j,k,eps=hashMap_t[hash("eps",n)],s=hashMap_t[hash("$",n)],h,h2;
	unsigned long int tempLong=0;
	nodeList temp=NULL;
	parseTable p=(parseTable)malloc(44*sizeof(nodeList*));
	for(i=0;i<44;i++){
		p[i]=(nodeList*)calloc(40,sizeof(nodeList));
		for(j=0;j<g[i]->numOfRules;j++){
			temp=g[i]->head[j];
			// h=hash(temp->n->name,n);
			if(temp->n->isTerminal=='t'){
				h=temp->n->num;
				if(h==eps){
					tempLong=follow[i];
					if(in(s,tempLong)){
						p[i][39]=(nodeList)malloc(sizeof(nodelist));
						p[i][39]->n=(Node)malloc(sizeof(node));
						p[i][39]->next=NULL;
						// p[i][39]->n->name=(char*)malloc(2*sizeof(char));
						// strcpy(p[i][39]->n->name,"$");
						p[i][39]->n->num=s;
						p[i][39]->n->numOfRules=0;
						p[i][39]->n->head=NULL;
						p[i][39]->n->isTerminal='t';
					}
					k=0;
					while(k<39){
						if((tempLong&1)==1){
							p[i][k]=g[i]->head[j];
						}
						tempLong=tempLong>>1;
						k++;
					}
				}
				else{
					p[i][h]=temp;
				}
			}
			else{
				while(temp!=NULL){
					k=0;
					h2=temp->n->num;
					if(temp->n->isTerminal=='t'){
						p[i][h2]=g[i]->head[j];	
						break;
					}
					tempLong=first[h2];
					while(k<40){
						if((tempLong&1)==1){
							p[i][k]=temp;
						}
						tempLong=tempLong>>1;
						k++;
					}
					if(in(eps,first[h2])==0){
						break;
					}
					temp=temp->next;
				}
				if(temp==NULL){
					tempLong=follow[i];
					if(in(s,tempLong)){
						p[i][39]=(nodeList)malloc(sizeof(nodelist));
						p[i][39]->n=(Node)malloc(sizeof(node));
						p[i][39]->next=NULL;
						p[i][39]->n->num=s;
						p[i][39]->n->numOfRules=0;
						p[i][39]->n->head=NULL;
						p[i][39]->n->isTerminal='t';
					}
					k=0;
					while(k<40){
						if((tempLong&1)==1){
							p[i][k]=g[i]->head[j];
						}
						tempLong=tempLong>>1;
						k++;
					}
				}
			}

		}
	}
	return p;
}

void printParseTable(parseTable p){
	int i,j,m=244,n=186;
	nodeList temp;
	for(i=0;i<44;i++){
		printf("%s:{\n",map_nt[i]);
		for(j=0;j<40;j++){
			if(p[i][j]!=NULL){
				temp=p[i][j];
				printf("\t%s:",map_t[j]);
				while(temp!=NULL){
					if(temp->n->isTerminal=='t'){
						printf("%s ",map_t[temp->n->num] );
					}
					else{
						printf("%s ",map_nt[temp->n->num] );
					}
					temp=temp->next;
				}
				printf(",\n");
			}
		}
		printf("}\n");
	}
}

Stack pop(Stack s){
	if(s==NULL) return NULL;
	return s->next;
}

Node top(Stack s){
	return s->p->n;
}

void insert(nodeList n,parseTree* p,Stack* s){
	parseTree tempParse1=*p,tempParse2;
	int eps=hashMap_t[hash("eps",186)];
	nodeList tempList=n;
	Stack tempStack1,head=NULL;
	while(1){
		if(tempParse1->children!=NULL || tempParse1->n->isTerminal=='t' || tempParse1->n->isTerminal=='n'){
		
			if(tempParse1->n->isTerminal=='t' || tempParse1->n->isTerminal=='n'){
				if(tempParse1->next==NULL){
					while(tempParse1->par->next==NULL)
						tempParse1=tempParse1->par;
					tempParse1=tempParse1->par->next;
				}
				else{
					tempParse1=tempParse1->next;
				}
			}
			else{
				tempParse1=tempParse1->children;
			}
		}
		else{
			break;
		}
	}
	if(tempList->n->isTerminal=='n'){
		tempParse1->children=(parseTree)malloc(sizeof(parsetree));
		tempParse2=tempParse1;
		tempParse1=tempParse1->children;
		tempParse1->par=tempParse2;
		if(tempList->n!=NULL)
			tempParse1->n=tempList->n;
		tempParse1->tk=NULL;
		tempParse1->children=NULL;
		tempParse1->next=NULL;
	}
	else{
		tempParse1->children=(parseTree)malloc(sizeof(parsetree));
		tempParse2=tempParse1;
		tempParse1=tempParse1->children;
		tempParse1->par=tempParse2;
		if(tempList->n!=NULL)
			tempParse1->n=tempList->n;
		tempParse1->tk=NULL;
		tempParse1->children=NULL;
		tempParse1->next=NULL;
		tempStack1=(Stack)malloc(sizeof(stack));
		tempStack1->p=tempParse1;
		tempStack1->next=NULL;
		head=tempStack1;
		tempList=tempList->next;
		while(tempList!=NULL && tempList->n!=NULL){
			tempParse1->next=(parseTree)malloc(sizeof(parsetree));
			tempParse1=tempParse1->next;
			tempParse1->n=tempList->n;
			tempParse1->tk=NULL;
			tempParse1->children=NULL;
			tempParse1->par=tempParse2;
			tempParse1->next=NULL;
			tempStack1->next=(Stack)malloc(sizeof(stack));
			tempStack1=tempStack1->next;
			tempStack1->p=tempParse1;
			tempStack1->next=NULL;
			tempList=tempList->next;
		}
		tempStack1->next=*s;
		*s=head;
	}
}


void printTree(parseTree p,FILE* fp){
	parseTree temp=p;
	int eps=hashMap_t[hash("eps",186)];
	if(temp->children!=NULL){
		printTree(p->children,fp);
	}
	if(temp->n->isTerminal=='t'){
		if(eps==temp->n->num){
			// fprintf(fp,"eps  \t\t\t\t----   \t----\t\t\t\t----\t\t\t\t----  \t\t\t\t\t\t yes \t----\n");
			fprintf(fp,"eps  \t\t\t\t----   \t----\t\t\t\t");
			fprintf(fp, "----\t\t\t\t" );
			fprintf(fp, "%-30s",map_nt[temp->par->n->num] );
			fprintf(fp,"yes\t----\n");
		}
		else if(temp->tk==NULL){
			// fprintf(fp,"NullNode \t\t\t----   \t----\t\t\t\t----\t\t\t\t----  \t\t\t\t\t\t yes \t----\n");
			fprintf(fp,"NullNode \t\t\t----   \t----\t\t\t\t");
			fprintf(fp, "----\t\t\t\t" );
			fprintf(fp, "%-30s",map_nt[temp->par->n->num] );
			fprintf(fp,"yes\t----\n");
			return;
			//printf("jvnbmbmbq %s\n",map_t[temp->n->num]);
		}
		else if(strcmp(temp->tk->token_id,"NUM")==0){
			// fprintf(fp,"‐‐‐‐\t\t\t\t");
			fprintf(fp," %-19d",atoi(temp->tk->value));
			fprintf(fp,"  %-7d",temp->tk->line_no);
			fprintf(fp,"NUM \t\t\t\t");
			fprintf(fp," %-19d",atoi(temp->tk->value));
			fprintf(fp,"%-30s",map_nt[temp->par->n->num]);
			fprintf(fp,"yes\t----\n");
		}
		else if (strcmp(temp->tk->token_id,"RNUM")==0){
			// fprintf(fp,"‐‐‐‐\t\t\t\t");
			fprintf(fp," %-19.2f",atof(temp->tk->value));
			fprintf(fp,"  %-7d",temp->tk->line_no);
			fprintf(fp,"RNUM\t\t\t\t");
			fprintf(fp," %-19.2f",atof(temp->tk->value));
			fprintf(fp,"%-30s",map_nt[temp->par->n->num]);
			fprintf(fp,"yes\t----\n");
		}
		else{	
			fprintf(fp,"%-20s",temp->tk->value);
			fprintf(fp,"  %-7d",temp->tk->line_no);
			fprintf(fp,"%-19s",temp->tk->token_id);
			fprintf(fp, "----\t\t\t\t" );
			fprintf(fp, "%-30s",map_nt[temp->par->n->num] );
			fprintf(fp,"yes\t----\n");
		}
	}
	else if(temp->n->isTerminal=='n'){
		// printf("NullNode\n");
		fprintf(fp,"NullNode \t\t\t----   \t----\t\t\t\t----\t\t\t\t----  \t\t\t\t\t\t  no \t----\n");

		return;
	}
	else if(temp->par==NULL){
		fprintf(fp,"----\t\t\t\t----   \t----\t\t\t\t----\t\t\t\tROOT  \t\t\t\t\t\t  no \t%-30s\n",map_nt[temp->n->num]);
	}
	else{
		fprintf(fp,"----\t\t\t\t----   \t----\t\t\t\t----\t\t\t\t%-30sno \t%-30s\n",map_nt[temp->par->n->num],map_nt[temp->n->num]);
	}
	temp=temp->children;
	if(temp!=NULL){
		while(temp->next!=NULL){
			temp=temp->next;
			printTree(temp,fp);
		}
		// printTree(temp,fp);
	}

}

// void printTree(parseTree p,FILE* fp){
// 	parseTree temp=p;
// 	int eps=hashMap_t[hash("eps",186)];
// 	if(temp->children!=NULL){
// 		printTree(p->children,fp);
// 	}
// 	if(temp->n->isTerminal=='t'){
// 		if(temp->tk==NULL){
// 			// printf("jvnbmbmbq %s \n",map_t[temp->n->num]);
// 			return;
// 		}
// 		else if(eps!=temp->n->num && strcmp(temp->tk->token_id,"NUM")==0){
// 			printf("‐‐‐‐\t\t\t\t");
// 			printf("  %-7d",temp->tk->line_no);
// 			printf("NUM \t\t\t\t");
// 			printf(" %-19d",atoi(temp->tk->value));
// 			printf("%-30s",map_nt[temp->par->n->num]);
// 			printf("yes\t----\n");
// 		}
// 		else if ( eps!=temp->n->num && strcmp(temp->tk->token_id,"RNUM")==0){
// 			printf("‐‐‐‐\t\t\t\t");
// 			printf("  %-7d",temp->tk->line_no);
// 			printf("RNUM\t\t\t\t");
// 			printf(" %-19.2f",atof(temp->tk->value));
// 			printf("%-30s",map_nt[temp->par->n->num]);
// 			printf("yes\t----\n");
// 		}
// 		else if(eps!=temp->n->num ){	
// 			printf("%-20s",temp->tk->value);
// 			printf("  %-7d",temp->tk->line_no);
// 			printf("%-19s",temp->tk->token_id);
// 			printf( "----\t\t\t\t" );
// 			printf( "%-30s",map_nt[temp->par->n->num] );
// 			printf("yes\t----\n");
// 		}
// 	}
// 	else if(temp->n->isTerminal=='n'){
// 		printf("NullNode\n");
// 	}
// 	else if(temp->par==NULL){
// 		printf("----\t\t\t\t----   \t----\t\t\t\t----\t\t\t\tROOT  \t\t\t\t\t\t  no \t%-30s\n",map_nt[temp->n->num]);
// 	}
// 	else{
// 		printf("----\t\t\t\t----   \t----\t\t\t\t----\t\t\t\t%-30sno \t%-30s\n",map_nt[temp->par->n->num],map_nt[temp->n->num]);
// 	}
// 	temp=temp->children;
// 	if(temp!=NULL){
// 		while(temp->next!=NULL){
// 			temp=temp->next;
// 			printTree(temp,fp);
// 		}
// 	}

// }

void printParseTree(parseTree PT, char *outfile){
	FILE* fp;
	if(strcmp(outfile,"stdout")==0){
		fp = stdout;
	}
	else{
		fp=fopen(outfile,"w");
	}
	fprintf(fp, "-----------------------------------------------------------------------------------------------------------------\n" );
	fprintf(fp,"lexemeCurrentNode   lineno   token\t\t\tvalueIfNumber  \t\t\tparentNodeSymbol  \t\t\tisLeaf  NodeSymbol\n");
	fprintf(fp, "-----------------------------------------------------------------------------------------------------------------\n" );
	printTree(PT,fp);
}

unsigned long int* setKW(unsigned long int* synch){
	int* temp=(int*)malloc(12*sizeof(int));
	temp[0]=hashMap_t[hash("END",186)];
	temp[1]=hashMap_t[hash("INT",186)];
	temp[2]=hashMap_t[hash("REAL",186)];
	temp[3]=hashMap_t[hash("STRING",186)];
	temp[4]=hashMap_t[hash("MATRIX",186)];
	temp[5]=hashMap_t[hash("MAIN",186)];
	temp[6]=hashMap_t[hash("IF",186)];
	temp[7]=hashMap_t[hash("ELSE",186)];
	temp[8]=hashMap_t[hash("ENDIF",186)];
	temp[9]=hashMap_t[hash("READ",186)];
	temp[10]=hashMap_t[hash("PRINT",186)];
	temp[11]=hashMap_t[hash("FUNCTION",186)];
	int i,j;
	// for(j=0;j<12;j++){
	// 	printf("haha %d\n",temp[j] );
	// }
	for(i=0;i<44;i++){
		for(j=0;j<12;j++){

			// printf("%does %lu\n",temp[j],(synch[i]>>temp[j])%2);
			synch[i]=set(temp[j],synch[i]);
			// printf("%lu\n",(synch[i]>>temp[j])%2);
		}
	}
	return synch;
} 

// void Remove_prev(parseTree* p){
// 	parseTree temp,temp2;
// 	temp=*p;
// 	temp2=temp->children;
// 	if(temp2!=NULL){
// 		while(1){
// 			if(temp2->children!=NULL && temp2->n->isTerminal=='f'){
// 				temp=temp2;
// 				temp2=temp2->children;
// 			}
// 			else if(temp2->children==NULL && temp2->n->isTerminal=='f'){
// 				temp->children=NULL;
// 				return;
// 			}
// 			else{
// 				if(temp2->next==NULL){
// 					while(temp2->par->next==NULL){
// 						temp2=temp2->par;
// 						temp=temp->par;
// 					}
// 					temp2=temp2->next;

// 				}
// 				else{
// 					temp2=temp2->next;
// 				}
// 			}

// 		}
// 	}
// }

//Predictive Parsing Alogorithm
parseTree pred_parsing(tokenList tk,parseTable M,Grammar g,unsigned long int* synch){
	// synch=setKW(synch);
	int i,j,m=244,n=186,h1,h2,h3,d=hashMap_t[hash("$",n)],eps=hashMap_t[hash("eps",n)];
	Token a=getNextToken(tk);
	parseTree p,tempParse,tempParse2;
	p=(parseTree)malloc(sizeof(parsetree));
	Stack s,tempStack;
	nodeList temp;
	Node n1=(Node)malloc(sizeof(node));
	tempParse=(parseTree)malloc(sizeof(parsetree));
	n1->num=d;
	n1->numOfRules=0;
	n1->head=NULL;
	n1->isTerminal='t';
	tempParse->n=n1;
	tempParse->tk=NULL;
	tempParse->next=NULL;
	tempParse->children=NULL;
	s=(Stack)malloc(sizeof(stack));
	s->p=tempParse;
	s->next=NULL;
	h3=hashMap_t[hash("MAIN",n)];
	p->n=g[0];
	p->children=NULL;
	p->par=NULL;
	p->next=NULL;
	tempStack=(Stack)malloc(sizeof(stack));
	tempStack->p=p;
	tempStack->next=s;
	s=tempStack;
	nodeList nullNode;
	Node X;
	X=top(s);
	h1=X->num;
	while(h1!=d || X->isTerminal == 'f'){
		h3=hashMap_t[hash(a->token_id,n)];
		if(X->isTerminal=='t'){
			if(h1==h3){
				if(s->p->n->isTerminal=='t'){
					s->p->tk=a;
				}
				s=pop(s);
				a=getNextToken(tk);
			}
			else{
				if(h1==eps){
					s=pop(s);
				}
				else{
					fprintf(errorFile,"Line No. %d: Syntax Error : The token %s for lexeme %s does not match at line %d. The expected token here is %s. Terminal Inserted and Parsing Continued\n",a->line_no,a->token_id,a->value,a->line_no,map_t[h1]);
					error++;
					s=pop(s);
					// error();
					a=getNextToken(tk);
					// break;
				}
			}

		}
		else if(h1==-1){
			break;
		}
		else if(M[h1][h3]==NULL){
			fprintf(errorFile,"Line No. %d: Syntax Error :  Token received %s failed to meet the expected syntax. Checking for recovery from Synchronizing Set\n",a->line_no,a->token_id);
			error++;
			if(in(eps,synch[h1])==1){
				// printf("hgkblkkl\n");
				temp=M[h1][eps];
				if(temp!=NULL){ 
					s=pop(s);
					insert(temp,&p,&s);
				}
				else{
					while(in(h3,synch[h1])==0){
						a=getNextToken(tk);
						h3=hashMap_t[hash(a->token_id,n)];
						if(h3==d){
							break;
						}
					}
					s=pop(s);
					nullNode=(nodeList)malloc(sizeof(nodelist));
					nullNode->n=(Node)malloc(sizeof(node));
					nullNode->n->isTerminal='n';
					nullNode->n->num=-1;
					nullNode->next=NULL;
					nullNode->n->num=-1;
					nullNode->next=NULL;
					insert(nullNode,&p,&s);
					// a=getNextToken(tk);

					// Remove_prev(&p);
				}
			}
			else{
				// printf("test %s %s %d\n",a->value,map_t[h3],in(h3,synch[h1]));
				while(in(h3,synch[h1])==0){
					a=getNextToken(tk);
					h3=hashMap_t[hash(a->token_id,n)];
					if(h3==d){
						break;
					}
				}
				s=pop(s);
				nullNode=(nodeList)malloc(sizeof(nodelist));
				nullNode->n=(Node)malloc(sizeof(node));
				nullNode->n->isTerminal='n';
				nullNode->n->num=-1;
				nullNode->next=NULL;
				nullNode->n->num=-1;
				nullNode->next=NULL;
				insert(nullNode,&p,&s);
			}
		}
		else{
			temp=M[h1][h3];
			s=pop(s);
			insert(temp,&p,&s);
			
		}
		X=top(s);
		h1=X->num;
	}
	return p;
}

