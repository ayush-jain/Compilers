#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h" 
#include "lexer.h"

#define SIZE_STRING 2
#define SIZE_INT 4
#define SIZE_REAL 4

int size=0;
int fillSymTb(char *key,int index,trPtr t, char *scope,char *type,int offset){

int h=0;
int hnew=0;
int i;

const int len=strlen(key)+1;
for (i=0; i<len;i+=1)
{
	h=h*i+key[i];
	h=h%997;
}
//if(strcmp(key,"<RemainingStmts"))
	//printf("%d %s\n", h%99, key);
hnew=h%99;
//printf("%d %s\n", hnew, key);
	

	if(symtb[index]->t[hnew].isEmpty=='y') {
		symtb[index]->t[hnew].isEmpty='n';
		symtb[index]->t[hnew].idname=(char *)malloc((strlen(key)+1)*sizeof(char));
		symtb[index]->t[hnew].scope=(char *)malloc((strlen(key)+1)*sizeof(char));
		symtb[index]->t[hnew].type=(char *)malloc((strlen(key)+1)*sizeof(char));
		strcpy(symtb[index]->t[hnew].idname,key);
		strcpy(symtb[index]->t[hnew].scope,scope);
		strcpy(symtb[index]->t[hnew].type,type);
		symtb[index]->t[hnew].offset=offset;
		symtb[index]->t[hnew].lineno=t->lineno;
		symtb[index]->t[hnew].p=t;
		t->sptr=&symtb[index]->t[hnew];
		return hnew;
	}
	else
	{
		while(symtb[index]->t[hnew].isEmpty=='n')
		{	
			//printf("%d %s\n", hnew, key);
			if (strcmp(symtb[index]->t[hnew].idname,key) == 0) 
			{	
				printf("ERROR----MULTIPLE DECLARATIONS OF %s\n",key);
				return hnew;
			}
			else {
				if(hnew==98) 
					hnew=0;
				else 
					hnew++;
			}
			//printf("DOIT");
		}
		symtb[index]->t[hnew].isEmpty='n';
		symtb[index]->t[hnew].idname=(char *)malloc((strlen(key)+1)*sizeof(char));
		symtb[index]->t[hnew].scope=(char *)malloc((strlen(key)+1)*sizeof(char));
		symtb[index]->t[hnew].type=(char *)malloc((strlen(key)+1)*sizeof(char));
		strcpy(symtb[index]->t[hnew].idname,key);
		strcpy(symtb[index]->t[hnew].scope,scope);
		strcpy(symtb[index]->t[hnew].type,type);
		symtb[index]->t[hnew].offset=offset;
		symtb[index]->t[hnew].lineno=t->lineno;
		symtb[index]->t[hnew].p=t;
		t->sptr=&symtb[index]->t[hnew];
	}
	//printf("%d %s\n", hnew, key);
	return hnew;

}

int checkIfExists(char *key,int index){

int h=0;
int hnew=0;
int i;

const int len=strlen(key)+1;
for (i=0; i<len;i+=1)
{
	h=h*i+key[i];
	h=h%997;
}
//if(strcmp(key,"<RemainingStmts"))
	//printf("%d %s\n", h%99, key);
hnew=h%99;
//printf("%d %s\n", hnew, key);
	

	if(symtb[index]->t[hnew].isEmpty=='y') {
		
		return 0;
	}
	else
	{
		while(symtb[index]->t[hnew].isEmpty=='n')
		{	
			//printf("%d %s\n", hnew, key);
			if (strcmp(symtb[index]->t[hnew].idname,key) == 0) 
			{	
				return 1;
			}
			else {
				if(hnew==98) 
					hnew=0;
				else 
					hnew++;
			}
			//printf("DOIT");
		}
		
	}
	//printf("%d %s\n", hnew, key);
	return 0;

}


int findIndex(char *key){
	int i;
	for(i=0;i<100;i++){

		if(symtb[i]!=NULL){
			if(strcmp(symtb[i]->idname,key)==0)
				return i;
		}
		else{
			return -1;
		}
	}
	return -1;
}


int addFunc(char *key,int stno,int endno,char *scope,uElemptr parameter,uElemptr returnlist,trPtr t){
	
	if(findIndex(key)==-1){
		symtb[size]=(tbPtr)malloc(sizeof(table));
		strcpy(symtb[size]->idname,key);
		symtb[size]->stno=stno;
		symtb[size]->endno=endno;
		symtb[size]->scope=scope;
		symtb[size]->parameterlist=parameter;
		symtb[size]->returnlist=returnlist;
		symtb[size]->p=t;
		size++;
		printf("----------YUPPY---Heloo\n");
	}
	return size;
}

uElemptr addpr(uElemptr list,char *type, char *id){

	uElemptr cur=list;
	while(cur->next!=NULL)
		cur=cur->next;
	cur->next=(uElemptr)malloc(sizeof(uElem));
	cur->next->type=(char *)malloc((strlen(type)+1)*sizeof(char));
	cur->next->id=(char *)malloc((strlen(id)+1)*sizeof(char));
	strcpy(cur->next->type,type);
	strcpy(cur->next->id,id);
	return list;
}

int checkSize(char *name){
	int i=0;
	int result=0;
	for(i=0;i<100;i++){
		if(matrixTable[i]!=NULL){
			if(strcmp(matrixTable[i]->id,name)==0){
				result= matrixTable[i]->size1*matrixTable[i]->size1;
			}
		}else{
			return result;
		}

	}
	
return result;
}

int checknested(char *id,char *scope){
	int i;
	int index;
	char *scope1=scope;
	index=findIndex(scope1);
	i=checkIfExists(id,index);
	if(i==1)
		return 1;
	scope1=symtb[index]->scope;
	index=findIndex(scope1);
	while(i==0 && strcmp(scope1,"null")!=0){
		i=checkIfExists(id,index);
		if(i==1)
			return 1;
		index=findIndex(scope1);
		scope1=symtb[index]->scope;
	}
	if(i==1)
		return 1;
	else
		return 0;	
}

void populateSym(trPtr t,char *scope){
	if(t==NULL)
		return;
	trPtr cur=t;
	char *scope1=scope;
	ptrList c;
	c=t->l;
	offset=0;
	int hnew=0;
	int sizeMatrix=0;
	printf("-------------Heloo\n");
	if(strcmp(cur->nodeSymbol,"<declarationStmt>")==0){
		char* type=c->child->name;
		int i=findIndex(scope);
		
		while(c!=NULL){
			if(strcmp(c->child->name,"ID")==0){
				hnew=fillSymTb(c->child->lexemeCurrentNode,i,c->child,scope1,type,offset);
				//t->sptr=&symtb[index]->t[hnew];
				if(strcmp(type,"STRING")==0)
					offset+= SIZE_STRING;
				if(strcmp(type,"INT")==0)
					offset+=SIZE_INT;
				if(strcmp(type,"REAL")==0)
					offset+=SIZE_REAL;
				if(strcmp(type,"MATRIX")==0){
					sizeMatrix=checkSize(c->child->lexemeCurrentNode);
					offset+=(sizeMatrix*SIZE_INT);
				}

			}
		c=c->next;
		}
	return;
	}
	if(strcmp(cur->nodeSymbol,"<mainFunction>")==0){
		uElemptr pl=NULL;
		uElemptr rl=NULL;
		offset=0;
		scope1=(char *)malloc(10*sizeof(char));
		char *name=(char *)malloc(10*sizeof(char));
		strcpy(scope1,"null");
		strcpy(name,"_main");
		printf("---%s----%s--%d--%d----Heloo\n",name,scope1,c->child->lineno,c->next->next->child->lineno);
		addFunc(name,c->child->lineno,c->next->next->child->lineno,scope1,pl,rl,cur);

	}
	if(strcmp(cur->nodeSymbol,"<functionDef>")==0){
		uElemptr pl=NULL;
		uElemptr rl=NULL;
		offset=0;
		scope1=cur->name;
		while(c->next!=NULL)
			{	
				if(strcmp(c->child->name,"FUNID")==0)
					break;
				pl=addpr(pl,c->child->name,c->next->child->lexemeCurrentNode);
				c=c->next->next;
			}
		c=c->next;
		while(c->next!=NULL)
			{	
				
				rl=addpr(rl,c->child->name,c->next->child->lexemeCurrentNode);
				c=c->next->next;
			}		
		addFunc(cur->name,cur->lineno,c->child->lineno,scope1,pl,rl,cur);
	}
	if(strcmp(cur->name,"ID")==0){
		if(checknested(cur->lexemeCurrentNode,scope1))
			return ;
		else{
			printf("Error------No Declaration of %s\n",cur->lexemeCurrentNode);
			return;
		}
	}
	c=t->l;	
	while(c!=NULL){
		populateSym(c->child,scope1);
		c=c->next;
	}
	return;	
}

int main(){
	int i;
	rule *grammar;
	FILE *fp;
	FILE *fptr;
	FILE *out;
	fptr=fopen("testcase3.txt","r");
	out=fopen("output.txt","w");
	fp=fopen("grammar.txt","r");
	trPtr Tree;
	int **pt=newparseTable();
	grammar=createG(fp);
	pt=createParseTable(grammar,pt);
	char main[10];
	strcpy(main,"_main");
	Tree=parseInputSourceCode(fptr,pt,grammar);
	printParseTree(Tree,out);
	
	Tree=buildParseTree(Tree);
	if(Tree==NULL)
		printf("----------Hello-----------\n");
	printAst(Tree);
	populateSym(Tree,main);
return 1;
}