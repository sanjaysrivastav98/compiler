#include "lexer.h"
#include "parserDef.h"
#include "ast.h"

int isSpecial(parseTree p){
    parseTree tempParse = p;
    int n=186; 
    int *temp = (int*)malloc(sizeof(int)*9);
    temp[0]=hashMap_t[hash("INT",n)];
    temp[1]=hashMap_t[hash("REAL",n)];
    temp[2]=hashMap_t[hash("STRING",n)];
    temp[3]=hashMap_t[hash("MATRIX",n)];
    temp[4]=hashMap_t[hash("ID",n)];
    temp[5]=hashMap_t[hash("FUNID",n)];
    temp[6]=hashMap_t[hash("RNUM",n)];
    temp[7]=hashMap_t[hash("NUM",n)];
    temp[8]=hashMap_t[hash("STR",n)];
    int i=0;
    for(i=0;i<9;i++){
        if(tempParse->n->num==temp[i])
            return 1;
    }
    return 0;
}

int isSpecialNT(parseTree p){
    parseTree tempParse = p;
    int m = 244,i=0;
    int *temp =(int*)malloc(sizeof(int)*10);
    temp[0] = hashMap_nt[hash("<mainFunction>",m)];
    temp[1] = hashMap_nt[hash("<stmtsAndFunctionDefs>",m)];
    temp[2] = hashMap_nt[hash("<parameter_list>",m)];
    temp[3] = hashMap_nt[hash("<var_list>",m)];
    temp[4] = hashMap_nt[hash("<var_list1>",m)];
    temp[5] = hashMap_nt[hash("<otherStmts>",m)];
    temp[6] = hashMap_nt[hash("<row>",m)];
    temp[7] = hashMap_nt[hash("<firstRow>",m)];
    temp[8] = hashMap_nt[hash("<conditionalStmt>",m)];
    temp[9] = hashMap_nt[hash("<functionDef>",m)];
    for(i=0;i<9;i++){
        if(tempParse->n->num==temp[i]){
            return 1;
        }
    }
    return 0;
}   

int isSpecialT1(parseTree p){
    parseTree tempParse = p;
    int n = 186,i=0,h = hashMap_t[hash(p->tk->token_id,n)];
    int *temp = (int*)malloc(sizeof(int)*3);
    temp[0] = hashMap_t[hash("SIZE",n)];
    temp[1] = hashMap_t[hash("READ",n)];
    temp[2] = hashMap_t[hash("PRINT",n)];
    for(i=0;i<3;i++){
        if(h == temp[i]){
            return 1;
        }
    }
    return 0;
}

int isSpecialT2(parseTree p){
    parseTree tempParse = p;
    int n = 186,i=0,h = hashMap_t[hash(p->tk->token_id,n)];
    int *temp = (int*)malloc(sizeof(int)*5);
    temp[0]=hashMap_t[hash("ID",n)];
    temp[1]=hashMap_t[hash("FUNID",n)];
    temp[2]=hashMap_t[hash("RNUM",n)];
    temp[3]=hashMap_t[hash("NUM",n)];
    temp[4]=hashMap_t[hash("STR",n)];
    for(i=0;i<3;i++){
        if(h == temp[i]){
            return 1;
        }
    }
    return 0;
}

int isarithORbool(parseTree p){
    int m = 244,i=0;
    int *temp =(int*)malloc(sizeof(int)*2);
    temp[0]=hashMap_nt[hash("<arithmeticExpression>",m)];
    temp[1]=hashMap_nt[hash("<booleanExpression>",m)];
    for(i=0;i<2;i++){
        if(p->n->num == temp[i]){
            return i;
        }
    }
    return -1;
}

int* numOfNTChil(parseTree p){
    int *temp=(int*)malloc(sizeof(int)*2);
    temp[0]=0;
    temp[1]=0;
    parseTree tempParse =p->children;
    while(tempParse!=NULL){
        if(tempParse->n->isTerminal=='f'){
            temp[0]+=1;
        }
        else if(tempParse->n->isTerminal=='t' && tempParse->tk==NULL){
            temp[1]=-1;
            return temp;
        }
        else if (tempParse->n->isTerminal=='t' && isSpecial(tempParse)){
            temp[1]+=1;
        }
        tempParse=tempParse->next;
    }
    return temp;
}

astNode newNode(parseTree p){
    parseTree tempParse=p->children;
    astNode tempParseAns = (astNode)malloc(sizeof(astnode));
    char* str = map_nt[p->n->num]; 
    tempParseAns->name = (char*)malloc(sizeof(char)*(-1+strlen(str)));
    int i=0,j=0;
    for(i=0;i<strlen(str);i++){
        if(isalpha(str[i])){
            tempParseAns->name[j]=toupper(str[i]);j++;
        }
    }
    tempParseAns->p=NULL;
    tempParseAns->children=NULL;
    tempParseAns->next=NULL;
    tempParseAns->par = NULL;
    astNode tempParsechil;
    int flag=0;
    while(tempParse!=NULL){
        if(tempParse->n->isTerminal=='f'){
            if(flag==0){
                tempParseAns->children = buildAstTree(tempParse);
                if(tempParseAns->children!=NULL){
                    flag=1;
                    tempParsechil=tempParseAns->children;
                }
            }
            else{
                while(tempParsechil->next!=NULL)
                    tempParsechil=tempParsechil->next;
                tempParsechil->next=buildAstTree(tempParse);
                if(tempParsechil->next!=NULL)
                    tempParsechil=tempParsechil->next;
            }
        }
        else if(tempParse->n->isTerminal=='t'  && isSpecial(tempParse)){
            if(flag==0){
                flag=1;
                tempParseAns->children = (astNode)malloc(sizeof(astnode));
                if(tempParsechil->children!=NULL)
                    tempParsechil=tempParseAns->children;
                tempParsechil->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
                strcpy(tempParsechil->name,tempParse->tk->token_id);
                tempParsechil->p = tempParse;
                tempParsechil->next=NULL;
                tempParsechil->children=NULL;
                tempParsechil->par=NULL;
            }
            else{
                while(tempParsechil->next!=NULL)
                    tempParsechil=tempParsechil->next;
                tempParsechil->next = (astNode)malloc(sizeof(astnode));
                if(tempParsechil->next!=NULL)
                    tempParsechil=tempParsechil->next;
                tempParsechil->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
                strcpy(tempParsechil->name,tempParse->tk->token_id);
                tempParsechil->p = tempParse;
                tempParsechil->next=NULL;
                tempParsechil->children=NULL;
                tempParsechil->par=NULL;
            }
        }
        tempParse=tempParse->next;
    }
    return tempParseAns;
}

astNode newLeaf(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns = (astNode)malloc(sizeof(astnode));
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
    strcpy(tempParseAns->name,tempParse->tk->token_id);
    while(tempParse->next!=NULL)
        tempParse=tempParse->next;
    tempParseAns->p = tempParse;
    return tempParseAns;
}

astNode newNode_Leaf(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns = (astNode)malloc(sizeof(astnode));
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
    strcpy(tempParseAns->name,tempParse->tk->token_id);
    while(tempParse->next!=NULL){
        if(isSpecial(tempParse))
            break;
        tempParse=tempParse->next;
    }
    tempParseAns->children=(astNode)malloc(sizeof(astnode));
    tempParseAns->children->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
    strcpy(tempParseAns->children->name,tempParse->tk->token_id);
    tempParseAns->children->p = tempParse;
    return tempParseAns;
}

astNode newLeafMat(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns = (astNode)malloc(sizeof(astnode));
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->name = (char*)malloc(sizeof(char)*7);
    strcpy(tempParseAns->name,"MATRIX");
    tempParseAns->children = (astNode)malloc(sizeof(astnode));
    tempParseAns->children->next=NULL;
    tempParseAns->children->par=NULL;
    tempParseAns->children->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->next->tk->token_id)));
    strcpy(tempParseAns->children->name,tempParse->next->tk->token_id);
    tempParseAns->children->p = tempParse->next;
    tempParseAns->children->next = (astNode)malloc(sizeof(astnode));
    tempParseAns->children->next->next=NULL;
    tempParseAns->children->next->par=NULL;
    tempParseAns->children->next->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->next->next->next->tk->token_id)));
    strcpy(tempParseAns->children->next->name,tempParse->next->next->next->tk->token_id);
    tempParseAns->children->next->p = tempParse->next->next->next;
    return tempParseAns;
}

astNode newLeafDualSp(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns = (astNode)malloc(sizeof(astnode));
    tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
    strcpy(tempParseAns->name,tempParse->tk->token_id);
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->children = NULL;
    tempParseAns->p = tempParse;
    tempParseAns->next = buildAstTree(tempParse->next);
    return tempParseAns;
}

astNode newNodeDualSp(parseTree p){
    parseTree tempParse = p->children;
    if(tempParse->next->n->isTerminal=='f' && tempParse->next->children->n->isTerminal=='t' && tempParse->next->children->n->num==4){
        astNode tempParseAns = (astNode)malloc(sizeof(astnode));
        tempParseAns->next=NULL;
        tempParseAns->par=NULL;
        tempParseAns->children = NULL;
        tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
        strcpy(tempParseAns->name,tempParse->tk->token_id);
        tempParseAns->p = tempParse;
        return tempParseAns;

    }
    else if(tempParse->next->n->isTerminal=='f'){
        astNode tempParseAns = (astNode)malloc(sizeof(astnode));
        char* str = map_nt[p->n->num]; 
        tempParseAns->name = (char*)malloc(sizeof(char)*(-1+strlen(str)));
        int i=0,j=0;
        for(i=0;i<strlen(str);i++){
            if(isalpha(str[i])){
                tempParseAns->name[j]=toupper(str[i]);j++;
            }
        }
        tempParseAns->next=NULL;
        tempParseAns->par=NULL;
        tempParseAns->children = (astNode)malloc(sizeof(astnode));
        astNode tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        tempParseAns->children=NULL;
        tempParseAns->par=NULL;
        tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
        strcpy(tempParseAns->name,tempParse->tk->token_id);
        tempParseAns->p = tempParse;
        tempParseAns->next = buildAstTree(tempParse->next);
        return tempParseAns1;
    }
    else{
        astNode tempParseAns = (astNode)malloc(sizeof(astnode));
        char* str = map_nt[p->n->num]; 
        tempParseAns->name = (char*)malloc(sizeof(char)*(-1+strlen(str)));
        int i=0,j=0;
        for(i=0;i<strlen(str);i++){
            if(isalpha(str[i])){
                tempParseAns->name[j]=toupper(str[i]);j++;
            }
        }
        tempParseAns->next=NULL;
        tempParseAns->par=NULL;
        tempParseAns->children = (astNode)malloc(sizeof(astnode));
        astNode tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        tempParseAns->children=NULL;
        tempParseAns->par=NULL;
        tempParseAns->name = (char*)malloc(sizeof(char)*(1+strlen(tempParse->tk->token_id)));
        strcpy(tempParseAns->name,tempParse->tk->token_id);
        tempParseAns->p = tempParse;
        if(tempParse->next->next!=NULL)
            tempParseAns->next = buildAstTree(tempParse->next->next);
        return tempParseAns1;
    }   
}

astNode newNodeBool(parseTree p){
    parseTree tempParse = p->children;
    int i=0,m=244,n=186,flag=0;
    int h1 = hashMap_nt[hash("<logicalOp>",m)];
    int h2 = hashMap_nt[hash("<relationalOp>",m)];
    astNode tempParseAns=NULL,tempParseAns1=NULL;
    tempParseAns = (astNode)malloc(sizeof(astnode));
    if(tempParse->tk!=NULL && strcmp(tempParse->tk->token_id,"NOT")==0){
        tempParseAns->name =(char*)malloc(sizeof(char)*4);
        strcpy(tempParseAns->name,"NOT");
        tempParseAns->next=NULL;
        tempParseAns->par=NULL;
        tempParseAns->p=NULL;
        tempParseAns->children = buildAstTree(tempParse->next);
        return tempParseAns;
    }
    while(tempParse!=NULL){
        if(tempParse->n->num == h1 && strcmp(tempParse->children->tk->token_id,"AND")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*4);
            strcpy(tempParseAns->name,"AND");
            flag=1;
        }
        else if(tempParse->n->num == h1 && strcmp(tempParse->children->tk->token_id,"OR")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"OR");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"LT")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"LT");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"LE")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"LE");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"EQ")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"EQ");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"GT")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"GT");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"GE")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"GE");
            flag=1;
        }
        else if(tempParse->n->num == h2 && strcmp(tempParse->children->tk->token_id,"NE")==0){
            tempParseAns->name =(char*)malloc(sizeof(char)*3);
            strcpy(tempParseAns->name,"NE");
            flag=1;
        }
        if(flag==1){
            tempParseAns->next=NULL;
            tempParseAns->par=NULL;
            tempParseAns->p=NULL;
            tempParse=p->children;
            while(tempParse!=NULL){
                if(tempParse->n->isTerminal=='f'){
                    break;
                }
                tempParse=tempParse->next;
            }
            tempParseAns->children = buildAstTree(tempParse);
            tempParseAns1=tempParseAns;
            tempParseAns=tempParseAns->children;
            while(tempParseAns->next!=NULL){
                tempParseAns=tempParseAns->next;
            }
            tempParseAns->next=buildAstTree(tempParse->next->next);
            return tempParseAns1;
        }
        tempParse=tempParse->next;
    }
}

astNode newNode_param(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns=(astNode)malloc(sizeof(astnode));
    tempParseAns->name = (char*)malloc(sizeof(char)*(9));
    strcpy(tempParseAns->name,"TYPENODE");
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->children=buildAstTree(tempParse);
    astNode tempParseAns1=tempParseAns;
    tempParseAns=tempParseAns->children;
    while(tempParseAns->next!=NULL){
        tempParseAns=tempParseAns->next;
    }
    tempParseAns->next=(astNode)malloc(sizeof(astnode));
    tempParseAns->next->name =(char*)malloc(sizeof(char)*3);
    strcpy(tempParseAns->next->name,"ID");
    tempParseAns->next->p=tempParse->next;
    tempParseAns1->next=buildAstTree(tempParse->next->next);
    return tempParseAns1;
}

astNode newNode_row(parseTree p){
    parseTree tempParse = p->children;
    astNode tempParseAns=(astNode)malloc(sizeof(astnode));
    tempParseAns->name = (char*)malloc(sizeof(char)*(4));
    strcpy(tempParseAns->name,"ROW");
    tempParseAns->next=NULL;
    tempParseAns->par=NULL;
    tempParseAns->children=buildAstTree(tempParse);
    tempParseAns->next=buildAstTree(tempParse->next);
    return tempParseAns;
}

astNode newNodeFactor(parseTree p){
    if(p->children->next==NULL){
        return buildAstTree(p->children);
    }
    else{
        return buildAstTree(p->children->next);
    }
}

astNode newNodeTerm(parseTree p){
    if(p->children->next->children->n->isTerminal == 't' && p->children->next->children->n->num==4){
        return newNodeFactor(p->children);
    }
    parseTree tempParse =p->children;
    astNode tempParseAns,tempParseAns1;
    if(strcmp(tempParse->next->children->children->tk->token_id,"MUL")==0){
        tempParseAns=(astNode)malloc(sizeof(astnode));
        tempParseAns->name=(char*)malloc(sizeof(char)*4);
        strcpy(tempParseAns->name,"MUL");
        tempParseAns->p=NULL;
        tempParseAns->children=newNodeFactor(tempParse);
        tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        while(tempParseAns->next!=NULL){
            tempParseAns=tempParseAns->next;
        }
        tempParseAns->next=newNodeTerm(tempParse->next->children->next);
        return tempParseAns1;
    }
    else{
        tempParseAns=(astNode)malloc(sizeof(astnode));
        tempParseAns->name=(char*)malloc(sizeof(char)*4);
        tempParseAns->p=NULL;
        strcpy(tempParseAns->name,"DIV");
        tempParseAns->children=newNodeFactor(tempParse);
        tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        while(tempParseAns->next!=NULL){
            tempParseAns=tempParseAns->next;
        }
        tempParseAns->next=newNodeTerm(tempParse->next->children->next);
        return tempParseAns1;
    }
} 

astNode newNodeArith(parseTree p){
    if(p->children->next->children->n->isTerminal == 't' && p->children->next->children->n->num==4){
        return newNodeTerm(p->children);
    }
    parseTree tempParse =p->children;
    astNode tempParseAns,tempParseAns1;
    if(strcmp(tempParse->next->children->children->tk->token_id,"PLUS")==0){
        tempParseAns=(astNode)malloc(sizeof(astnode));
        tempParseAns->name=(char*)malloc(sizeof(char)*5);
        tempParseAns->p=NULL;
        strcpy(tempParseAns->name,"PLUS");
        tempParseAns->children=newNodeTerm(tempParse);
        tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        while(tempParseAns->next!=NULL){
            tempParseAns=tempParseAns->next;
        }
        tempParseAns->next=buildAstTree(tempParse->next->children->next);
        return tempParseAns1;
    }
    else{
        tempParseAns=(astNode)malloc(sizeof(astnode));
        tempParseAns->name=(char*)malloc(sizeof(char)*6);
        strcpy(tempParseAns->name,"MINUS");
        tempParseAns->children=newNodeTerm(tempParse);
        tempParseAns->p=NULL;
        tempParseAns1=tempParseAns;
        tempParseAns=tempParseAns->children;
        while(tempParseAns->next!=NULL){
            tempParseAns=tempParseAns->next;
        }
        tempParseAns->next=buildAstTree(tempParse->next->children->next);
        return tempParseAns1;
    }
}

astNode buildAstTree(parseTree p){
    
    int m=244,n=186;
    parseTree tempParse = p;
    astNode tempParseAns1=NULL,tempParseAns=NULL;
    int *numChil = numOfNTChil(tempParse);
    if(numChil[0]==0 && numChil[1]==0){
        return NULL;
    }
    else if(numChil[1]==-1){
        return NULL;
    }
    else if(numChil[0]==1 && numChil[1]==0){
        tempParse =p->children;
        while(tempParse!=NULL){
            if(tempParse->n->isTerminal=='f'){
                break;
            }
            tempParse=tempParse->next;
        } 
        return buildAstTree(tempParse);
    }
    else if( numChil[1]==0){
        if(isarithORbool(tempParse)==1){
            return newNodeBool(tempParse);
        }
        else if(isarithORbool(tempParse)==0){
            return newNodeArith(tempParse);
        }
        else if(hashMap_nt[hash("<row>",m)]==tempParse->n->num){
            return newNode_row(tempParse);
        }
        else if(!isSpecialNT(tempParse)){
            return newNode(tempParse);
        }
        else{
            tempParse =p->children;
            while(tempParse!=NULL){
                if(tempParse->n->isTerminal=='f'){
                    if(tempParseAns==NULL){
                        tempParseAns=buildAstTree(tempParse);
                        tempParseAns1=tempParseAns;
                    }
                    else{
                        while(tempParseAns->next!=NULL)
                            tempParseAns=tempParseAns->next;
                        tempParseAns->next=buildAstTree(tempParse);
                        if(tempParseAns->next!=NULL)
                            tempParseAns=tempParseAns->next;
                    }
                }
                tempParse=tempParse->next;
            }
            return tempParseAns1;
        }
    }
    else if(numChil[1]==2 && numChil[0]==0){
        return newLeafMat(tempParse);
    }
    else if(numChil[1]>0 && numChil[0]==0){
        if(isSpecialT1(tempParse->children)){
            return newNode_Leaf(tempParse);
        }
        else{
            return newLeaf(tempParse);
        }
    }
    else if(numChil[0]==1 && numChil[1]==1){
        // printf("%s\n",map_nt[p->n->num]);
        if(isSpecialNT(tempParse)){
            return newLeafDualSp(tempParse);
        }
        else{
            return newNodeDualSp(tempParse);
        }
    }
    else if(numChil[0]==2 && numChil[1]==1){
        return newNode_param(tempParse);
    }
    else{
        return newNode(tempParse);
    }
}

void printAstTree1(astNode ast){
    astNode tempParse = ast->children;
    while(tempParse!=NULL){
        if(tempParse->p!=NULL){
            printf("%-30s %-30s %-30s\n",tempParse->p->tk->value,tempParse->name,ast->name);
        }
        else{
            printf("%-30s %-30s %-30s\n","----",tempParse->name,ast->name);
        }
        printAstTree1(tempParse);
        tempParse=tempParse->next;
    }
}

void printAstTree(astNode ast){
    printf("------------------------------------------------------------------------------------\n");
    printf("%-30s %-30s %-30s\n","TOKEN","NAME","PARENT");
    printf("------------------------------------------------------------------------------------\n");
    printAstTree1(ast);
}

int cal_sizeA(astNode tree){
    astNode temp=tree->children;
    int size=1;
    while(temp!=NULL){
        size+=cal_sizeA(temp);
        temp=temp->next;
    }
    return size;
} 

int cal_sizeP(parseTree tree){
    if(tree==NULL){
        return 0;
    }
    parseTree temp=tree->children;
    int size=1;
    while(temp!=NULL){
        size+=cal_sizeP(temp);
        temp=temp->next;
    }
    return size;
} 