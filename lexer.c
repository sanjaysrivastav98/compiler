//K S Sanjay Srivastav 
//2015A7PS0102P
#include "lexerDef.h"

tokenList addtoTkList(Token tk,tokenList tkList){
	tokenNode t=(tokenNode)malloc(sizeof(tokennode));
	t->tk=tk;
	t->next=NULL;
	tokenNode temp=tkList->tail;
	if (temp==NULL){
		temp=t;
		tkList->head=temp;
		tkList->tail=temp;
	}
	else{
		temp->next=t;
		tkList->tail=t;
	}
	return tkList;
}

Token getNextToken(tokenList tkList){
	tokenNode t;
	t=tkList->head;
	if(t==NULL){
		return NULL;
	}
	tkList->head=tkList->head->next;
	return t->tk;
}

FILE* getStream(FILE* fp,char* buffer){
	int i=0,j=0;
	char c;
	i=fread(buffer,1,30,fp);
	if (i!=30){
		buffer[i]='$';
	}
	return fp;
}

char* extractWord(char* b,char* f,char* valuebuffer){
	char* temp;
	temp=(char*)malloc(60*sizeof(char));
	int i=0;
	while(valuebuffer[i]!='$'){
		temp[i]=valuebuffer[i];
		i++;
	}
	if (i>0){
		i--;
	}
	while(b<=f){
		temp[i]=*b;
		b++;
		i++;
	}
	temp[i]='\0';
	return temp;
}

int hash(char *str,int m)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (int)(hash%m);
}

void fillKeyHash(){
	char* word[12];
	int i=0,h;
	int m=37;
	keyWord temp=NULL;
	word[0]=(char*)malloc(4*sizeof(char));
	strcpy(word[0],"end");
	word[1]=(char*)malloc(4*sizeof(char));
	strcpy(word[1],"int");
	word[2]=(char*)malloc(5*sizeof(char));
	strcpy(word[2],"real");
	word[3]=(char*)malloc(6*sizeof(char));
	strcpy(word[3],"string");
	word[4]=(char*)malloc(7*sizeof(char));
	strcpy(word[4],"matrix");
	word[5]=(char*)malloc(6*sizeof(char));
	strcpy(word[5],"_main");
	word[6]=(char*)malloc(3*sizeof(char));
	strcpy(word[6],"if");
	word[7]=(char*)malloc(5*sizeof(char));
	strcpy(word[7],"else");
	word[8]=(char*)malloc(6*sizeof(char));
	strcpy(word[8],"endif");
	word[9]=(char*)malloc(5*sizeof(char));
	strcpy(word[9],"read");
	word[10]=(char*)malloc(6*sizeof(char));
	strcpy(word[10],"print");
	word[11]=(char*)malloc(9*sizeof(char));
	strcpy(word[11],"function");
	for(i=0;i<12;i++){
		h=hash(word[i],m);
		temp=(keyWord)malloc(sizeof(keyword));
		temp->name=word[i];
		temp->next=NULL;
		if(keyHash[h]==NULL){
			keyHash[h]=temp;
		}
		else{
			temp->next=keyHash[h];
			keyHash[h]=temp;
		}
	}
}

int checkKeyWord(char* b,char* f,char* valuebuffer){
	char* temp=extractWord(b,f,valuebuffer);
	int m=37;
	keyWord temp2=NULL;
	temp2=keyHash[hash(temp,m)];
	while(temp2!=NULL){
		if(strcmp(temp2->name,temp)==0){
			free(temp);
			return 1;
		}
		temp2=temp2->next;
	}
	free(temp);
	return 0;
}

char* retract(char* forward){
	return forward-1;
}

Token fillStruct(char* b,char* f,char* valuebuffer,char* s,int line_no){
	Token tk;
	
	char* temp=extractWord(b,f,valuebuffer);
	
	if((strcmp(s,"ID")==0) ||(strcmp(s,"STR")==0) ) {
		if(strlen(temp)>20)
			return NULL;
	}
	tk=(Token)malloc(sizeof(token));
	tk->line_no=line_no;
	int i=0,k;
	if(strcmp(s,"KW")==0){
		tk->value=(char*)malloc(30*sizeof(char));
		strcpy(tk->value,temp);
		k=strlen(temp);
		while(i<k){
			temp[i] = toupper(temp[i]);
			i++;
		}
		strcpy(tk->token_id,temp);
		free(temp);
		return tk;
	}

	else{
		strcpy(tk->token_id,s);
		tk->value=(char*)malloc(30*sizeof(char));
		tk->value=temp;
		
	}
	return tk;
}

char* renewBuffer(char* b){
	free(b);
	b=(char*)malloc(30*sizeof(char));
	return b;
}

void printToken(Token tk){
	// if (strcmp(tk->token_id,"RNUM")==0 || strcmp(tk->token_id,"NUM")==0 || strcmp(tk->token_id,"ID")==0 || strcmp(tk->token_id,"FUN_ID")==0 || strcmp(tk->token_id,"STR")==0){
	
	printf("%-20s%-20s%-20d\n",tk->token_id,tk->value,tk->line_no);
	
	// }
	// else{
	// 	printf("%s:\t-\t%d\n",tk->token_id,tk->line_no);
	// }
}

tokenList copyTokenList(tokenList t){
	tokenList temp=(tokenList)malloc(sizeof(tokenList));
	tokenNode temp1=NULL,temp2=t->head,temp3;
	while(temp2!=NULL){
		if(temp->head==NULL){
			temp3=(tokenNode)malloc(sizeof(tokennode));
			temp3->tk=temp2->tk;
			temp3->next=NULL;
			temp->head=temp3;
		}
		else{
			temp3->next=(tokenNode)malloc(sizeof(tokennode));
			temp3=temp3->next;
			temp3->tk=temp2->tk;
			temp3->next=NULL;
		}
		temp2=temp2->next;
	}
	return temp;

}

void print(tokenList t){
	tokenNode temp=t->head;
	printf("-----------------------------------------------------------------\n");
	printf("%-20s%-20s%-20s\n","Token ID","Token Value","Line Number");
	printf("-----------------------------------------------------------------\n");
	while(temp!=NULL && strcmp(temp->tk->token_id,"$")!=0){
		printToken(temp->tk);
		temp=temp->next;
	}

}

void removeComments(char* filename){
	FILE* fp=fopen(filename,"r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int j,i=0,k,l;
	while ((read = getline(&line, &len, fp)) != -1) {
		i=0;
		while(i<len){
			if(line[i]!=' ' && line[i]!='\t') break;
			i++;
		}
		if(line[i]=='#') continue;
		else{
			printf("%s",line);
		}
	}
	fclose(fp);
}

tokenList tokenize(FILE* fp,tokenList tkList){
	char* buffer=(char*)malloc(30*sizeof(char));
	char* valuebuffer=(char*)malloc(30*sizeof(char));
	int line_no=1,state=1;
	Token temp_token;
	fp=getStream(fp,buffer);
	char* begin,*forward;
	begin = &buffer[0];
	forward = begin;
	int i=0,j=0;
	while(1){
		i++;
		if (i==31){
			i=0;
			if (state==1){
				buffer=renewBuffer(buffer);
				fp=getStream(fp,buffer);	
				begin = &buffer[0];
				valuebuffer[0]='$';
			}
			else{
				j=0;
				while(begin<=&buffer[30]){
					valuebuffer[j]=*begin;
					begin++;
					j++;
				}
				valuebuffer[j]='$';
				buffer=renewBuffer(buffer);
				fp=getStream(fp,buffer);	
				begin = &buffer[0];
			}
			forward = begin;
			continue;
		}
		// printf("Entered,%c,%d %d\n",*forward,state,i);
		switch(state){
			case 1:
				valuebuffer[0]='$';
				// printf("fdsfsdgdgdfg---------------%s\n",forward);					
				if (*forward=='$'){
					// printf("fdsfsdgdgdfg---------------\n");
					temp_token=(Token)malloc(sizeof(token));
					temp_token->line_no=line_no;
					strcpy(temp_token->token_id,"$");
					temp_token->value=(char*)malloc(30*sizeof(char));
					strcpy(temp_token->value,"$");
					tkList=addtoTkList(temp_token,tkList);
					return tkList;
				}
				if (*forward=='\n'){
					line_no++;
					forward++;
					begin=forward;
					state=1;
					break;
				}
				if  (*forward=='\t' || *forward==' ' || *forward == '\r'){
					state=1;
					forward++;
					begin=forward;
					break;
				}
				if (*forward=='='){
					state=2;
					forward++;
					break;
				}
				if (*forward=='#'){
					state=7;
					forward++;
					break;
				}
				if (*forward == '_'){
					state=9;
					forward++;
					break;
				}
				if ((*forward >='a' && *forward <='z') || (*forward >='A' && *forward <='Z')){
					state=12;
					forward++;
					break;
				}
				if(*forward >='0' && *forward <='9'){
					state=15;
					forward++;
					break;
				}
				if (*forward=='"'){
					state=20;
					forward++;
					break;
				}
				if(*forward=='['){
					state=23;i--;
					break;
				}
				if(*forward==']'){
					state=24;i--;
					break;
				}
				if(*forward=='('){
					state=25;i--;
					break;
				}
				if(*forward==')'){
					state=26;i--;
					break;
				}
				if(*forward==';'){
					state=27;i--;
					break;
				}
				if(*forward==','){
					state=28;i--;
					break;
				}
				if(*forward=='+'){
					state=29;i--;
					break;
				}
				if(*forward=='-'){
					state=30;i--;
					break;
				}
				if(*forward=='*'){
					state=31;i--;
					break;
				}
				if(*forward=='/'){
					state=32;i--;
					break;
				}
				if(*forward=='@'){
					state=33;i--;
					break;
				}
				if(*forward=='.'){
					state=34;forward++;
					break;
				}
				if(*forward=='<'){
					state=46;forward++;
					break;
				}
				if(*forward=='>'){
					forward++;
					state=49;
					break;
				}
			case 2:
				if(*forward=='='){
					state=4;
					i--;
					break;
				}
				else if(*forward=='/'){
					state=5;
					forward++;
					break;
				}
				else{
					
					state=3;
					i--;
					break;				
				}
			case 3:
				forward=retract(forward);
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ASSIGNOP",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 4:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"EQ",line_no),tkList);
				state=1;
				forward++; 
				begin=forward;
				break;
			case 5:
				if (*forward=='='){
					state=6;
					i--;
					break;
				}
				else{
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern. Expected '=' but given %c\n",line_no,*forward);state=1;begin=forward;break;
				}
				break;
			case 6:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NE",line_no),tkList);
				state=1;
				forward++;
				begin=forward;
				break;
			case 7:
				if(*forward=='\n'){
					state=8;
					line_no++;
					i--;
					break;
				}
				else{
					state=7;
					forward++;
					break;
				}
			case 8:
				state=1;forward++;begin=forward;
				break;
			case 9:
				if ((*forward >='a' && *forward <='z') || (*forward >='A' && *forward <='Z')){
					state=10;
					forward++;
					
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern. Expected alphabet but given %c\n",line_no,*forward);state=1;begin=forward;break;
				}
				break;
			case 10:
				if ((*forward >='a' && *forward <='z') || (*forward >='A' && *forward <='Z') || (*forward >='0' && *forward <='9')){
					state=10;
					forward++;
					break;
				}
				else{
					state=11;
					i--;
					// forward++;
					break;
				}
			case 11:
				forward=retract(forward);
				i--;
				if (checkKeyWord(begin,forward,valuebuffer)==1){
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MAIN",line_no),tkList);
					state=1;
					forward++;
					begin=forward;
					break;
				}
				else{
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"FUNID",line_no),tkList);
					state=1;
					forward++;
					begin=forward;
					break;
				}
			case 12:
				if ((*forward >='a' && *forward <='z') || (*forward >='A' && *forward <='Z')){
					state=12;
					forward++;
					break;
				}
				else if((*forward >='0' && *forward <='9')){
					state=13;
					i--;
					break;
				}
				else{
					state=14;
					i--;
					break;
				}
				break;
			case 13:
				state=1;

				temp_token=fillStruct(begin,forward,valuebuffer,"ID",line_no);
				if(temp_token==NULL){
					error++;
					printf("Line No. %d:Lexical Error : Identifier is longer than the prescribed length\n",line_no);
				}
				else{
					tkList=addtoTkList(temp_token,tkList);
				}
				forward++;
				begin=forward;
				break;
			case 14:
				forward=retract(forward);
				i--;
				if (checkKeyWord(begin,forward,valuebuffer)==1){
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"KW",line_no),tkList);
				}
				else{
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ID",line_no),tkList);
				}
				state=1;
				forward++;
				begin=forward;
				break;
			case 15:
				if((*forward >='0' && *forward <='9')){
					state=15;
					forward++;
					break;
				}
				else if(*forward=='.'){
					state=16;
					forward++;
					break;
				}
				else{
					state=19;
					i--;
					break;
				}
			case 16:
				if((*forward >='0' && *forward <='9')){
					state=17;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}
				break;
			case 17:
				if((*forward >='0' && *forward <='9')){
					state=18;
					i--;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unkown Pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}
				break;
			case 18:
				state=1;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"RNUM",line_no),tkList);
				forward++;
				begin=forward;
				break;
			case 19:
				forward=retract(forward);
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NUM",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 20:
				if((*forward >='a' && *forward <='z') || (*forward==' ')){
					state=21;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 21:
				if ((*forward >='a' && *forward <='z') || (*forward==' ')){
					state=21;
					forward++;
					break;
				}
				else if(*forward=='"'){
					state=22;
					i--;
					break;
				}
				else{
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 22:
				temp_token=fillStruct(begin,forward,valuebuffer,"STR",line_no);
				if(temp_token==NULL){
					error++;
					printf("Line No. %d:Lexical Error : Identifier is longer than the prescribed length\n",line_no);
				}
				else{
					tkList=addtoTkList(temp_token,tkList);
				}
				forward++;
				state=1;
				begin=forward;
				break;
			case 23:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SQO",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 24:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SQC",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 25:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"OP",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 26:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"CL",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 27:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SEMICOLON",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 28:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"COMMA",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 29:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"PLUS",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 30:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MINUS",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 31:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MUL",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 32:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"DIV",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 33:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SIZE",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 34:
				if (*forward=='a'){
					state=35;
					forward++;
					break;
				}
				else if(*forward=='o'){
					state=39;
					forward++;
					break;
				}
				else if(*forward=='n'){
					state=42;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown Pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}
			case 35:
				if (*forward=='n'){
					state=36;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}
			case 36:
				if(*forward=='d'){
					state=37;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 37:
				if(*forward=='.'){
					state=38;
					i--;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 38:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"AND",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 39:
				if(*forward=='r'){
					state=40;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 40:
				if(*forward=='.'){
					state=41;
					i--;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 41:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"OR",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 42:
				if(*forward=='o'){
					state=43;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 43:
				if(*forward=='t'){
					state=44;
					forward++;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 44:
				if(*forward=='.'){
					state=45;
					i--;
					break;
				}
				else{
					i--;
					error++;
					printf("Line No. %d:Lexical Error : Unknown pattern '%s'\n",line_no,extractWord(begin,forward,valuebuffer));state=1;begin=forward;break;
				}break;
			case 45:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NOT",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 46:
				if(*forward=='='){
					state=47;
					i--;
				}
				else{
					state=48;
					i--;
				}
				break;
			case 47:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"LE",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 48:
				forward=retract(forward);
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"LT",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 49:
				if(*forward=='='){
					state=50;
					i--;
				}
				else{
					state=51;
					i--;
				}
				break;
			case 50:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"GE",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
			case 51:
				forward=retract(forward);
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"GT",line_no),tkList);
				forward++;
				state=1;
				begin=forward;
				break;
		}

	}
	return tkList;
}

