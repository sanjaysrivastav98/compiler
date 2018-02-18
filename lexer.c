#include "lexer.h"

char* begin,*forward;
tokenList tkList;
char* buffer;

tokenList addtoTkList(token* tk){
	tokenNode *t=(tokenNode*)malloc(sizeof(tokenNode));
	t->tk=tk;
	t->next=NULL;
	tokenNode* temp=tkList.head;
	if (temp==NULL){
		temp=t;
		tkList.head=temp;
	}
	else{
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=t;
	}
	return tkList;
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


void retract(){
	forward--;
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


char* tokenize(FILE* fp){
	char* buffer=(char*)malloc(30*sizeof(char));
	char* valuebuffer=(char*)malloc(30*sizeof(char));
	int line_no=1,state=1;
	fp=fillBuffer(fp,buffer);
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
		printf("Entered,%c,%d %d\n",*forward,state,i);
		switch(state){
			case 1:
				valuebuffer[0]='$';
				if (*forward=='$') return "Completed";
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
				retract();
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ASSIGNOP",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 4:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"EQ",line_no));
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
					return "Lexical Error";
				}
				break;
			case 6:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NE",line_no));
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
					return "Lexical Error";
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
				retract();
				i--;
				if (checkKeyWord(begin,forward,valuebuffer)==1){
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MAIN",line_no));
					state=1;
					forward++;
					begin=forward;
					break;
				}
				else{
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"FUNID",line_no));
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
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ID",line_no));
				forward++;
				begin=forward;
				break;
			case 14:
				retract();
				i--;
				if (checkKeyWord(begin,forward,valuebuffer)==1){
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"KW",line_no));
				}
				else{
					tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"ID",line_no));
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
					return "Lexical Error";
				}
			case 17:
				if((*forward >='0' && *forward <='9')){
					state=18;
					i--;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 18:
				state=1;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"RNUM",line_no));
				forward++;
				begin=forward;
				break;
			case 19:
				retract();
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NUM",line_no));
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
					return "Lexical Error";
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
					return "Lexical Error";
				}
			case 22:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"STR",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 23:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SQO",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 24:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SQC",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 25:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"OP",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 26:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"CL",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 27:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SEMICOLON",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 28:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"COMMA",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 29:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"PLUS",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 30:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MINUS",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 31:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"MUL",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 32:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"DIV",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 33:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"SIZE",line_no));
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
					return "Lexical Error";
				}
			case 35:
				if (*forward=='n'){
					state=36;
					forward++;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 36:
				if(*forward=='d'){
					state=37;
					forward++;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 37:
				if(*forward=='.'){
					state=38;
					i--;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 38:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"AND",line_no));
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
					return "Lexical Error";
				}
			case 40:
				if(*forward=='.'){
					state=41;
					i--;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 41:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"OR",line_no));
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
					return "Lexical Error";
				}
			case 43:
				if(*forward=='t'){
					state=44;
					forward++;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 44:
				if(*forward=='.'){
					state=45;
					i--;
					break;
				}
				else{
					return "Lexical Error";
				}
			case 45:
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"NOT",line_no));
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
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"LE",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 48:
				retract();
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"LT",line_no));
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
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"GE",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
			case 51:
				retract();
				i--;
				tkList=addtoTkList(fillStruct(begin,forward,valuebuffer,"GT",line_no));
				forward++;
				state=1;
				begin=forward;
				break;
		}

	}
}

int main(){
	FILE* fp;
	fp=fopen("test1.txt","r");
	buffer=(char*)malloc(30*sizeof(char));
	char* s;
	s=tokenize(fp);
	if (s=="Lexical Error"){
		return 0;
	}
	printf("%s\n",s);
	print(tkList);
	return 0;
}