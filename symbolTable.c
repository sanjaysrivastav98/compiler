#include "lexer.h"
#include "parserDef.h"
#include "symbolTable.h"
#include <stdlib.h>

int ht_size=91;
int last_offset=0;
matSize getOffset(astNode s,matSize m){
    astNode temp=s,tempChil;
    int a=0,row,prev;
    while(temp!=NULL){
        tempChil=temp->children;
        row=0;
        while(tempChil!=NULL){
            row+=2;
            tempChil=tempChil->next;
        }
        if(a!=0 && row!=prev){
            return NULL;
        }
        m->x = row/2;
        prev=row;
        a+=row;
        temp=temp->next;
    }
    if(m->x!=0){
        m->y = a/(m->x*2);
    }
    return m;
}

symbolTable insertToHT(symbolTable st,astNode root,int* offset){
    symbolTable tempSt=st;
    int a= *offset;
    int h,c=0;
    char* type= (char*)malloc(sizeof(char)*7);
    strcpy(type,root->children->name);
    astNode temp=root->children->next;
    astNode par=root->next;
    if(temp==NULL){
        *offset=-1;
        st->last_offset=-1;
        return NULL;
    }
    if(strcmp(type,"INT")==0 || strcmp(type,"REAL")==0){
        while(temp!=NULL){
            h=hash(temp->p->tk->value,st->ht->size);
            if(st->ht->s[h]==NULL){
                st->ht->s[h]=(stNode)malloc(sizeof(stnode));
                st->ht->s[h]->var_name=temp->p->tk->value;
                st->ht->s[h]->type=type;
                st->ht->s[h]->offset=a;
                st->ht->s[h]->next=NULL;
                temp->st=st;
                if(strcmp(type,"INT")==0){
                    a+=2;
                }
                else{
                    a+=4;
                }
                *offset=a;
            }
            else{
                stNode tempNode=st->ht->s[h];
                while(tempNode->next!=NULL){
                    if(strcmp(temp->p->tk->value,tempNode->var_name)==0){
                        fprintf(errorFile,"Multiple Declarations of the variable %s at line %d \n",temp->p->tk->value,temp->p->tk->line_no);
                        break;
                        // return st;
                        // *offset=-1;
                        // return NULL;
                    }
                    tempNode=tempNode->next;
                }
                if(strcmp(temp->p->tk->value,tempNode->var_name)==0){
                    // *offset=-1;
                    // return NULL;
                    fprintf(errorFile,"Multiple Declarations of the variable %s at line %d.\n",temp->p->tk->value,temp->p->tk->line_no);
                    break;
                    // return st;
                }
                tempNode->next=(stNode)malloc(sizeof(stnode));
                tempNode=tempNode->next;
                tempNode->var_name=temp->p->tk->value;
                temp->st=st;
                tempNode->type=type;
                tempNode->offset=a;
                tempNode->next=NULL;
                if(strcmp(type,"INT")==0){
                    a+=2;
                }
                else {
                    a+=4;
                }
                *offset=a;
            }
            temp=temp->next;
        }
        st->last_offset=*offset;
        return st;
    }
    while(temp!=NULL){
        astNode tempPar=par;
        while(tempPar!=NULL){
            if((strcmp(tempPar->name,"ASSIGNMENTSTMT")==0) && (strcmp(tempPar->children->p->tk->value,temp->p->tk->value)==0) ){
                if(strcmp(tempPar->children->next->name,"FUNCTIONCALL")==0){
                    // *offset=-1;
                    fprintf(errorFile,"STRING or MATRIX %s initialized with a function Call at line %d - Not supported\n",temp->p->tk->value,tempPar->children->p->tk->line_no);
                    break;
                    // return  st;
                }
                else if(strcmp(tempPar->children->next->name,"PLUS")==0 || strcmp(tempPar->children->next->name,"MINUS")==0 || strcmp(tempPar->children->next->name,"MUL")==0 || strcmp(tempPar->children->next->name,"DIV")==0){
                    fprintf(errorFile,"Variable %s used at line number %d before assigned\n",temp->p->tk->value,tempPar->children->p->tk->line_no);
                    tempPar=tempPar->next;
                    continue;
                }
                else{
                    h=hash(temp->p->tk->value,st->ht->size);
                    if(st->ht->s[h]==NULL){
                        
                        if(strcmp(type,"MATRIX")==0){
                            st->ht->s[h]=(stNode)malloc(sizeof(stnode));
                            st->ht->s[h]->var_name=temp->p->tk->value;
                            st->ht->s[h]->mat = (matSize)calloc(1,sizeof(matsize));
                            st->ht->s[h]->mat=getOffset(tempPar->children->next,st->ht->s[h]->mat);
                            if(NULL==st->ht->s[h]->mat){
                                fprintf(errorFile,"Inconsistent Matrix declaration for variable %s at line %d\n",temp->p->tk->value,tempPar->children->p->tk->line_no);
                                break;
                            }
                            st->ht->s[h]->type=type;
                            st->ht->s[h]->offset=a;
                            st->ht->s[h]->next=NULL;
                            a+=(2*st->ht->s[h]->mat->x*st->ht->s[h]->mat->y);
                        }
                        else{
                            st->ht->s[h]=(stNode)malloc(sizeof(stnode));
                            st->ht->s[h]->var_name=temp->p->tk->value;
                            st->ht->s[h]->type=type;
                            st->ht->s[h]->offset=a;
                            st->ht->s[h]->next=NULL;
                            a+=strlen(tempPar->children->next->p->tk->value)-2;
                        }
                        temp->st=st;
                        *offset=a;
                        break;
                    }
                    else{
                        stNode tempNode=st->ht->s[h];
                        while(tempNode->next!=NULL){
                            if(strcmp(tempPar->children->next->p->tk->value,tempNode->var_name)==0){
                                fprintf(errorFile,"Multiple Declarations of the variable %s at line %d\n",temp->p->tk->value,temp->p->tk->line_no);
                                break;
                            }
                            tempNode=tempNode->next;
                        }
                        if(strcmp(tempPar->children->next->p->tk->value,tempNode->var_name)==0){
                            fprintf(errorFile,"Multiple Declarations of the variable %s at line %d \n",temp->p->tk->value,temp->p->tk->line_no);
                            break;
                        }
                        
                        if(strcmp(type,"MATRIX")==0){
                            tempNode->next=(stNode)malloc(sizeof(stnode));
                            tempNode=tempNode->next;
                            tempNode->var_name=temp->p->tk->value;
                            tempNode->type=type;
                            tempNode->mat = (matSize)calloc(1,sizeof(matsize));
                            tempNode->mat=getOffset(tempPar->children->next,tempNode->mat);
                            if(tempNode->mat == NULL){
                                fprintf(errorFile,"Inconsistent Matrix declaration for variable %s at line %d\n",temp->p->tk->value,temp->p->tk->line_no);
                                break;
                            }
                            tempNode->offset=(2*tempNode->mat->x*tempNode->mat->y);
                            tempNode->next=NULL;
                            a+=c;
                        }
                        else{
                            tempNode->next=(stNode)malloc(sizeof(stnode));
                            tempNode=tempNode->next;
                            tempNode->var_name=temp->p->tk->value;
                            tempNode->type=type;
                            tempNode->offset=a;
                            a+=strlen(tempPar->children->next->p->tk->value);
                            tempNode->next=NULL;
                        }
                        temp->st=st;
                        *offset=a;
                        break;
                    }
                }
                break;
            }
            tempPar=tempPar->next;
        }
        if(tempPar==NULL){
            fprintf(errorFile,"Uninitialized variable %s at line %d\n",temp->p->tk->value,temp->p->tk->line_no);
        }
        temp=temp->next;
    }
    st->last_offset=*offset;
    return st;
}

int checkinHash(symbolTable st,char* name){
    int h=hash(name,st->ht->size);
    stNode temp=st->ht->s[h];
    while(temp!=NULL){
        if(strcmp(temp->var_name,name)==0){
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

symbolTable buildST(astNode root){
    // last_offset=0;
    int begin_offset=0,flag=0;
    astNode temp=root,temp2;
    astNode par=root;
    symbolTable st=NULL,stChil=NULL;
    symbolTable stAns=NULL;
    
    st = (symbolTable)malloc(sizeof(symboltable));
    st->par=NULL;
    st->next=NULL;
    st->children=NULL;
    st->ht = (st_hashTable)malloc(sizeof(st_hashtable));
    stAns=st;
    if(strcmp(temp->name,"MAIN")==0){
        st->ht->scope=(char*)malloc(sizeof(char)*6);
        strcpy(st->ht->scope,"_main");
    }
    else{
        temp=temp->children;
        while(temp!=NULL){
            if(strcmp(temp->name,"FUNID")==0){
                st->ht->scope=temp->p->tk->value;
                break;
            }
            temp=temp->next;
        }
    }
    if(temp==NULL){
        fprintf(errorFile,"Name of the function is not defined at line %d\n",root->children->children->p->tk->line_no);
        return NULL;
    }
    temp=root;
    st->ht->size= ht_size;
    st->ht->s=(stNode*)calloc(st->ht->size,sizeof(stNode));
    par=temp;
    temp=temp->children;
    while(temp!=NULL){
        if(strcmp(temp->name,"FUNCTIONDEF")==0){
            if(st->children!=NULL){
                stChil=st->children;
                temp2=temp->children;
                while(temp2!=NULL){
                    if(strcmp(temp2->name,"FUNID")==0){
                        break;
                    }
                    temp2=temp2->next;
                }
                while(stChil->next!=NULL){
                    if(temp2!=NULL && strcmp(stChil->ht->scope,temp2->p->tk->value)==0){
                        fprintf(errorFile,"Multiple Declarations of function %s at line %d\n",temp2->p->tk->value,temp2->p->tk->line_no);
                        break;
                    }
                    stChil=stChil->next;
                }
                if(temp2!=NULL && strcmp(stChil->ht->scope,temp2->p->tk->value)==0){
                    fprintf(errorFile,"Multiple Declarations of function %s at line %d\n",temp2->p->tk->value,temp2->p->tk->line_no);
                }
                else if(stChil->next==NULL){
                    stChil->next=buildST(temp);
                    stChil->next->par=stChil->par;
                }
            }
            else{
                st->children=buildST(temp);
                st->children->par=st;
            }
        }
        else if(strcmp(temp->name,"ASSIGNMENTSTMT")==0){
            if(checkinHash(st,temp->children->p->tk->value)==0){
                fprintf(errorFile,"Undeclared Variable %s at line %d\n",temp->children->p->tk->value,temp->children->p->tk->line_no);
            }
        }
        else if(strcmp(temp->name,"DECLARATIONSTMT")==0){
            st=insertToHT(st,temp,&begin_offset);
        }
        temp=temp->next;
    }
    return stAns;
}

int inHt(char* var_name,symbolTable st){
    st_hashTable ht = st->ht;
    int i=0;
    stNode temp;
    for(i=0;i<ht->size;i++){
        if(ht->s[i]){
            temp=ht->s[i];
            while(temp!=NULL){
                if(strcmp(temp->var_name,var_name)==0){
                    return 1;
                }
                temp=temp->next;
            }
        }
    }
    return 0;
}

char* staticParent(symbolTable st,char* varname){
    symbolTable temp=st;
    while(temp!=NULL){
        if(inHt(varname,temp)){
            return temp->ht->scope;
        }
        temp=temp->par;
    }
    return NULL;
}

int compare(const void* s1,const void* s2){
    return ((stNode*)s1)[0]->offset - ((stNode*)s2)[0]->offset;
}

int level =1;
void printHash(symbolTable st){
    st_hashTable ht = st->ht;
    int i=0;
    stNode temp;
    stNode* res=NULL;
    int s=0;
    for(i=0;i<ht->size;i++){
        if(ht->s[i]){
            if(res){
                res=(stNode*)realloc(res,(s+1)*sizeof(stNode));s++;
            }
            else{
                res=(stNode*)malloc(sizeof(stNode));
                s=1;
            }
            temp=ht->s[i];
            while(temp!=NULL){
                res[s-1]=temp;
                if(temp->next!=NULL){
                    res=(stNode*)realloc(res,(s+1)*sizeof(stNode));s++;
                }
                temp=temp->next;
            }
        }
    }
    qsort(res,s,sizeof(stNode),compare);
    for(i=0;i<s;i++){
        if(strcmp(res[i]->type,"MATRIX")==0){
            if(i!=s-1){
                if(st->par==NULL){
                    printf("%-20s %-20s %-13d %-20s %-8s [%d , %d]     %-10d %-10d\n",res[i]->var_name,ht->scope,level,"NULL",res[i]->type,res[i]->mat->x,res[i]->mat->y,res[i+1]->offset-res[i]->offset,res[i]->offset);
                }
                else{
                    printf("%-20s %-20s %-13d %-20s %-8s [%d , %d]     %-10d %-10d\n",res[i]->var_name,ht->scope,level,st->par->ht->scope,res[i]->type,res[i]->mat->x,res[i]->mat->y,res[i+1]->offset-res[i]->offset,res[i]->offset);                
                }
            }
            else{ 
                if(st->par){
                    printf("%-20s %-20s %-13d %-20s %-8s [%d , %d]     %-10d %-10d\n",res[i]->var_name,ht->scope,level,st->par->ht->scope,res[i]->type,res[i]->mat->x,res[i]->mat->y,st->last_offset-res[i]->offset,res[i]->offset);            
                } 
                else{
                    printf("%-20s %-20s %-13d %-20s %-8s [%d , %d]     %-10d %-10d\n",res[i]->var_name,ht->scope,level,"NULL",res[i]->type,res[i]->mat->x,res[i]->mat->y,st->last_offset-res[i]->offset,res[i]->offset);            
                }
            }
        }
        else{
            if(i!=s-1){
                if(st->par){
                printf("%-20s %-20s %-13d %-20s %-20s %-10d %-10d\n",res[i]->var_name,ht->scope,level,st->par->ht->scope,res[i]->type,res[i+1]->offset-res[i]->offset,res[i]->offset);
                }
                else{
                printf("%-20s %-20s %-13d %-20s %-20s %-10d %-10d\n",res[i]->var_name,ht->scope,level,"NULL",res[i]->type,res[i+1]->offset-res[i]->offset,res[i]->offset);
                }
            }
            else{
                if(st->par)
                {
                printf("%-20s %-20s %-13d %-20s %-20s %-10d %-10d\n",res[i]->var_name,ht->scope,level,st->par->ht->scope,res[i]->type,st->last_offset-res[i]->offset,res[i]->offset);                
                }
                else{
                printf("%-20s %-20s %-13d %-20s %-20s %-10d %-10d\n",res[i]->var_name,ht->scope,level,"NULL",res[i]->type,st->last_offset-res[i]->offset,res[i]->offset);                
                }
            }
        }
    }
}

void printST1(symbolTable st){
    symbolTable temp=st;
    while(temp!=NULL){
        printHash(temp);
        level++;
        printST1(temp->children);
        level--;
        temp=temp->next;
    }
}
void printST(symbolTable st){
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-10s %-20s %-20s %-10s %-10s\n","Identifier Name","SCOPE","NestingLevel","Static Parent","TYPE","WIDTH","OFFSET");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");    
    printST1(st);
}


astNode typeChecker(astNode ast,symbolTable root){

}