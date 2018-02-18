#include "lexer.h"

tokenList* addtoTkList(token* tk,tokenList* tkList){
	tokenNode *t=(tokenNode*)malloc(sizeof(tokenNode));
	t->tk=tk;
	t->next=NULL;
	tokenNode* temp=tkList->head;
	if (temp==NULL){
		temp=t;
		tkList->head=temp;
	}
	else{
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=t;
	}
	return tkList;
}

token* getNextToken(tokenList* tkList){
	tokenNode *t=(tokenNode*)malloc(sizeof(tokenNode));
	t=tkList->head;
	if(t==NULL){
		return NULL;
	}
	tkList->head=tkList->head->next;
	return t->tk;
}

FILE* fillBuffer(FILE* fp,char* buffer){
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

int checkKeyWord(char* b,char* f,char* valuebuffer){
	char* temp=extractWord(b,f,valuebuffer);
	if( (strcmp(temp,"end")==0)||(strcmp(temp,"int")==0)||(strcmp(temp,"real")==0)||(strcmp(temp,"string")==0)||(strcmp(temp,"matrix")==0)||(strcmp(temp,"_main")==0)||(strcmp(temp,"if")==0)||(strcmp(temp,"else")==0)||(strcmp(temp,"endif")==0)||(strcmp(temp,"read")==0)||(strcmp(temp,"print")==0)||(strcmp(temp,"function")==0)){
		return 1;
	}
	return 0;
}

char* retract(char* forward){
	return forward-1;
}

token* fillStruct(char* b,char* f,char* valuebuffer,char* s,int line_no){
	token *tk;
	tk=(token*)malloc(sizeof(token));
	tk->line_no=line_no;
	char* temp;
	if(strcmp(s,"KW")==0){
		temp=extractWord(b,f,valuebuffer);
		int k=strlen(temp);
		while(*temp){
			*temp = toupper((unsigned char) *temp);
			temp++;
		}
		strcpy(tk->token_id,temp-k);
		return tk;
	}
	strcpy(tk->token_id,s);
	if (strcmp(tk->token_id,"RNUM")==0 || strcmp(tk->token_id,"NUM")==0 || strcmp(tk->token_id,"ID")==0 || strcmp(tk->token_id,"FUN_ID")==0 || strcmp(tk->token_id,"STR")==0){
		tk->value=(char*)malloc(30*sizeof(char));
		tk->value=extractWord(b,f,valuebuffer);
	}
	return tk;
}

char* renewBuffer(char* b){
	free(b);
	b=(char*)malloc(30*sizeof(char));
	return b;
}

void printToken(token* tk){
	if (strcmp(tk->token_id,"RNUM")==0 || strcmp(tk->token_id,"NUM")==0 || strcmp(tk->token_id,"ID")==0 || strcmp(tk->token_id,"FUN_ID")==0 || strcmp(tk->token_id,"STR")==0){
		printf("TOKEN-->%s\t%s\t%d\n",tk->token_id,tk->value,tk->line_no);
	
	}
	else{
		printf("TOKEN-->%s\t%d\n",tk->token_id,tk->line_no);
	}
}
void print(tokenList t){
	tokenNode* temp=t.head;
	while(temp!=NULL){
		printToken(temp->tk);
		temp=temp->next;
	}

}

// void removeComments(char *testcaseFile, char *cleanFile)

tokenList* tokenize(FILE* fp,tokenList *tkList){
	char* buffer=(char*)malloc(30*sizeof(char));
	char* valuebuffer=(char*)malloc(30*sizeof(char));
	int line_no=1,state=1;
	fp=fillBuffer(fp,buffer);
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
				fp=fillBuffer(fp,buffer);	
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
				fp=fillBuffer(fp,buffer);	
				begin = &buffer[0];
			}
			forward = begin;
			continue;
		}
		// printf("Entered,%c,%d %d\n",*forward,state,i);
		switch(state){
			case 1:
				valuebuffer[0]='$';
				if (*forward=='$') return tkList;
				if (*forward=='\n'){
					line_no++;
					forward++;
					begin=forward;
					state=1;
					break;
				}
				if  (*forward=='\t' || *forward==' '){
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
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
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 10:
				if ((*forward >='a' && *forward <='z') || (*forward >='A' && *forward <='Z') || (*forward >='0' && *forward <='9')){
					state=10;
					forward++;
					break;
				}
				else{
					state=11;
					forward++;
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
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ID",line_no),tkList);
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 17:
				if((*forward >='0' && *forward <='9')){
					state=18;
					i--;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
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
				if((*forward >='a' && *forward <='z')){
					state=21;
					forward++;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 21:
				if ((*forward >='a' && *forward <='z')){
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 22:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"STR",line_no),tkList);
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 35:
				if (*forward=='n'){
					state=36;
					forward++;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 36:
				if(*forward=='d'){
					state=37;
					forward++;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 37:
				if(*forward=='.'){
					state=38;
					i--;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 40:
				if(*forward=='.'){
					state=41;
					i--;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
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
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 43:
				if(*forward=='t'){
					state=44;
					forward++;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
			case 44:
				if(*forward=='.'){
					state=45;
					i--;
					break;
				}
				else{
					printf("Lexical Error in line %d\n",line_no);state=1;break;;
				}
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


// int main(){
// 	FILE* fp;
// 	fp=fopen("test1.txt","r");
// 	char* buffer=(char*)malloc(30*sizeof(char));
// 	tokenList *tkList=(tokenList*)malloc(sizeof(tokenList));
// 	tkList=tokenize(fp,tkList);
// 	token* t=(token*)malloc(sizeof(token));
// 	while((t=getNextToken(tkList))!=NULL){
// 		printToken(t);
// 		free(t);
// 		t=(token*)malloc(sizeof(token));	
// 	}
// 	return 0;
// }