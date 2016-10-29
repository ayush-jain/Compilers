#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h" 
#include "lexer.h"

int sizeMatrixTable=0;
char *idMatrix;
int size1;
int size2;
int choice=0;

void addMatrixTable(char *id,int size1,int size2){
	int i;
	infoPtr temp;
	temp=(infoPtr)malloc(sizeof(matrixInfo));
	temp->id=id;
	temp->size1=size1;
	temp->size2=size2;
	for(i=0;i<100;i++){
		if(matrixTable[i]!=NULL){
			if(strcmp(matrixTable[i]->id,id)==0){
				matrixTable[i]=temp;
				return;
			}
		}
		else
		{
			
			matrixTable[i]=temp;
			return;
		}

	}
	
return;	
}

int checkifLeaf(trPtr t){
	if(strcmp(t->isLeafNode,"Yes")==0)
		return 1;
	else
		return 0;
}

void printAst(trPtr t){
	if(t==NULL)
		return;
	ptrList cur=t->l;
	if(checkifLeaf(t)){	
		printf("%s\n",t->lexemeCurrentNode);
	}
	else if(!checkifLeaf(t))
		printf("%s\n",t->nodeSymbol);
	while(cur!=NULL){
		printAst(cur->child);
		cur=cur->next;
	}

}
ptrList add1(ptrList list,trPtr t){

	ptrList list1=list;
	ptrList temp=(ptrList)malloc(sizeof(struct list));
	temp->child=t;
	if(list==NULL)
		return temp;
	while(list1->next!=NULL){
		list1=list1->next;
	}
	list1->next=temp;
	return list;
}

ptrList dfs1(trPtr t,ptrList new,trPtr cons){
	ptrList new1=new;
	if(t->l==NULL)
		return new1;
	if(strcmp(t->nodeSymbol,"<declarationStmt>")==0||strcmp(t->nodeSymbol,"<functionDef>")==0||strcmp(t->nodeSymbol,"<ifStmt>")==0||strcmp(t->nodeSymbol,"<ioStmt>")==0||strcmp(t->nodeSymbol,"<funCallStmt>")==0||strcmp(t->nodeSymbol,"<assignmentStmt_type1>")==0||strcmp(t->nodeSymbol,"<assignmentStmt_type2>")==0){
		t->parentNodeSymbol=cons->nodeSymbol;
		t->parent=cons;
		new1=add1(new1,t);
		return new1; 	
	}
	ptrList temp=t->l;	
	while(temp!=NULL){
		new1=dfs1(temp->child,new1,cons);
		temp=temp->next;
	}
return new1;
}

ptrList dfs2(trPtr t,ptrList new){
	ptrList new1=new;
	if(t==NULL)
		return new1;
	//if(strcmp(t->lexemeCurrentNode,",")==0)
		//return;
	//if(strcmp(t->lexemeCurrentNode,";")==0)
		//return;
	if(choice==0){
	if(checkifLeaf(t) && ((strcmp(t->name,"COMMA")!=0) && (strcmp(t->name,"SEMICOLON")!=0) && (strcmp(t->name,"OP")!=0 )&& (strcmp(t->name,"CL")!=0))){
		new1=add1(new1,t);
		return new1; 
	}
	}
	if(choice==1){
	if(checkifLeaf(t) && (strcmp(t->name,"COMMA")!=0 )){
		new1=add1(new1,t);
		return new1; 
	}
	}
	
	ptrList cur=t->l;
	while(cur!=NULL){
		new1=dfs2(cur->child,new1);
		cur=cur->next;
	}
return new1;
}




trPtr actionTaken(trPtr ptr){
	ptrList new=NULL;
	ptrList cur=NULL;
	ptrList temp=NULL;
	//trPtr ptr1=ptr;
	if(strcmp(ptr->nodeSymbol,"<stmtsAndFunctionDefs>")==0){
		ptrList sample;
		new=dfs1(ptr,new,ptr);
		//sample=new;
		//while(sample!=NULL)
			//{printf("%s\n",sample->child->nodeSymbol);sample=sample->next;}
		ptr->l=new;
		return ptr;
	}
	
	if(strcmp(ptr->nodeSymbol,"<declarationStmt>")==0){
		new=dfs2(ptr,new);
		ptr->l=new;
		return ptr;
	}
	
	if(strcmp(ptr->nodeSymbol,"<functionDef>")==0){
		cur=ptr->l;
		if(cur==NULL)
			return ptr;
		while(cur->next!=NULL){
			if(strcmp(cur->child->nodeSymbol,"<stmtsAndFunctionDefs>")==0){
				cur->child->parent=ptr;
				
			}
			if(strcmp(cur->child->name,"FUNID")==0||strcmp(cur->child->name,"END")==0|| !checkifLeaf(cur->child))
			{	
				new=add1(new,cur->child);
				if(strcmp(cur->child->name,"FUNID")==0)
					{ ptr->name=cur->child->lexemeCurrentNode; ptr->lineno=cur->child->lineno;}	
			}
			cur=cur->next;
		}
		ptr->l=new;

		return ptr;
	}
	if(strcmp(ptr->nodeSymbol,"<parameter_list>")==0){
		new=dfs2(ptr,new);
		ptr->l=new;
		return ptr;
	}
	if(strcmp(ptr->nodeSymbol,"<assignmentStmt_type1>")==0){
		int lineno;
		char *str;
		cur=ptr->l;
		temp=cur->child->l;
		lineno=cur->next->child->lineno;
		str=cur->next->child->name;
		temp->next=cur->next->next;
		ptr->l=temp;
		cur=temp->next;
		temp=cur->child->l;
		ptr->l->next=temp;
		idMatrix=ptr->l->child->lexemeCurrentNode;
		if(strcmp(temp->child->nodeSymbol,"<sizeExpression>")==0){
			ptr->l->next=temp->child->l;
		}
		strcpy(ptr->isLeafNode,"Yes");
		strcpy(ptr->lexemeCurrentNode,"=");
		ptr->lineno=lineno;
		ptr->name=str;
		return ptr;
	}
	
	if(strcmp(ptr->nodeSymbol,"<arithmeticExpression>")==0){
		trPtr tree=NULL;
		ptrList prev=NULL;
		ptrList parent=NULL;
		ptrList prevSqo=NULL;
		ptrList sqo=NULL;
		ptrList sample;
		int count=0;
		int flag=0;
		choice=1;
		int ct=1;
		int pos=0;
		new=dfs2(ptr,new);
		choice=0;
		//if(new==NULL)
		//printf("Hello---------\n");
		sample=new;
		//printf("-----------%s\n",new->next->child->lexemeCurrentNode);
		while(sample!=NULL)
			{//printf("----%s\n",sample->child->name);
			if(strcmp(sample->child->name,"SQO")==0)
				flag=1;
			sample=sample->next;}
		cur=new->next;
		prev=new;
		//printf("hello----%s\n",cur->child->name);
		//if(cur==NULL)
		//{ 
		//return new->child;
		//}
		//printf("-------------ffff %s",new->child->name);
		sample=new->next;
		if(strcmp(new->child->name,"SQO")==0){
			printf("----------%s\n",idMatrix);
			
			while(sample!=NULL){
				if(strcmp(sample->child->lexemeCurrentNode,";")==0){
					size2=pos;
					pos=0;
					ct++;
					sample=sample->next;
				}else{
				pos++;
				sample=sample->next;
				}
			}
			addMatrixTable(idMatrix,size1,size2);
			ptr->l=new;
			return ptr;

		}else
		{
			ptr->l=new;
			return ptr;
		}
	}
		/*
		{
			if(flag==0){
				while(1){
					while(cur!=NULL && (strcmp(cur->child->name,"PLUS")!=0 || strcmp(cur->child->name,"MINUS")!=0 || strcmp(cur->child->name,"MUL")!=0 || strcmp(cur->child->name,"DIV")!=0))
					{
						prev=cur;
						cur=cur->next;

					}
					if(cur!=NULL){
						count++;
						if(count==1){
						printf("yummy");
						tree=cur->child;
						printf("yuppy\n");
						cur->child->l=NULL;
						cur->child->l=add1(cur->child->l,prev->child);
						parent=cur->child->l;
						}
					else{
						parent=add1(parent,cur->child);
						cur->child->l=NULL;
						cur->child->l=add1(cur->child->l,prev->child);
						parent=cur->child->l;	
						}
					}else{
						parent=add1(parent,prev->child);
						return tree;
					}
				prev=cur;
				cur=cur->next;	

				}
			}	
			return ptr;
		}
	}
	*/
		/*
		{
		//printf("fffff");	
		while(1){
			while(cur!=NULL && (strcmp(cur->child->name,"PLUS")!=0 || strcmp(cur->child->name,"MINUS")!=0 || strcmp(cur->child->name,"MUL")!=0 || strcmp(cur->child->name,"DIV")!=0)){
				if(strcmp(cur->child->name,"SQO")==0)
					{
						prevSqo=prev;
						sqo=cur;
					}

				prev=cur;
				cur=cur->next;
			}
			printf("%s-----YAHOOO\n",cur->child->name);
			if(cur!=NULL && prev!=NULL){
				if(strcmp(prev->child->name,"SQC")==0){
					count++;
				if(count==1){
					tree=cur->child;
					cur->child->l=NULL;
					cur->child->l=add1(cur->child->l,prevSqo->child);
					sqo=sqo->next;
					while(strcmp(sqo->child->name,"SQC")!=0){
						prevSqo->child->l=add1(prevSqo->child->l,sqo->child);
						sqo=sqo->next;
					}
					parent=cur->child->l;
				}
				else{
					parent=add1(parent,cur->child);
					cur->child->l=NULL;
					cur->child->l=add1(cur->child->l,prev->child);
					parent=cur->child->l;
					}	
				}else{
				count++;
				if(count==1){
					printf("yummy");
					tree=cur->child;
					printf("yuppy\n");
					cur->child->l=NULL;
					cur->child->l=add1(cur->child->l,prev->child);
					parent=cur->child->l;
				}
				else{
					parent=add1(parent,cur->child);
					cur->child->l=NULL;
					cur->child->l=add1(cur->child->l,prev->child);
					parent=cur->child->l;	
					}
				}
			}

			else{
					parent=add1(parent,prev->child);	
					
					if(tree==NULL)
						return parent->child;
					return tree;
					break;
			}
			prev=cur;
			cur=cur->next;	
					
		}
	}

	return tree;
	}
	*/
	if(strcmp(ptr->nodeSymbol,"<assignmentStmt_type2>")==0){
		int lineno;
		char *str;
		cur=ptr->l;
		ptrList temp1;
		temp1=dfs2(cur->child,new);
		ptr->l=temp1;
		lineno=cur->next->child->lineno;
		str=cur->next->child->name;
		while(temp1->next!=NULL)
			{
				temp1=temp1->next;
				printf("YAHOO----%s\n",temp1->child->lexemeCurrentNode);
			}	

		temp1->next=cur->next->next->child->l;
		
		
		if(strcmp(temp1->next->child->nodeSymbol,"<sizeExpression>")==0){
			temp1->next=temp1->next->child->l;
		}
		strcpy(ptr->isLeafNode,"Yes");
		strcpy(ptr->lexemeCurrentNode,"=");
		ptr->lineno=lineno;
		ptr->name=str;
		printf("hellllllllo\n");
		return ptr;	

	}
	if(strcmp(ptr->nodeSymbol,"<funCallStmt>")==0){
		new=dfs2(ptr,new);
		ptr->l=new;
		return ptr;
	}
	if(strcmp(ptr->nodeSymbol,"<ifStmt>")==0){
		cur=ptr->l;
		ptrList small;
		ptrList tem;
		while(cur!=NULL){
			if(strcmp(cur->child->nodeSymbol,"<stmt>")==0){
				new=add1(new,cur->child->l->child);
			}
			if(strcmp(cur->child->nodeSymbol,"<otherStmts>")==0 && cur->child->l!=NULL){
				small=dfs2(cur->child,small);
				tem=new;
				while(tem->next!=NULL)
					tem=tem->next;
				tem->next=small;
			}
			if(!checkifLeaf(cur->child) &&(strcmp(cur->child->nodeSymbol,"<booleanExpression>")==0 || strcmp(cur->child->nodeSymbol,"<RemainingIf>")==0))
				new=add1(new,cur->child);
			if(strcmp(cur->child->name,"IF")==0)	
				new=add1(new,cur->child);
			cur=cur->next;
		}
	ptr->l=new;	
	return ptr;
	}
	if(strcmp(ptr->nodeSymbol,"<RemainingIf>")==0){
		cur=ptr->l;
		ptrList tem1;
		ptrList small1;
		while(cur!=NULL){
			if(checkifLeaf(cur->child) && strcmp(cur->child->name,"SEMICOLON")!=0)
				new=add1(new,cur->child);
			if(strcmp(cur->child->nodeSymbol,"<stmt>")==0){
				new=add1(new,cur->child->l->child);
			}
			if(strcmp(cur->child->nodeSymbol,"<otherStmts>")==0 && cur->child->l!=NULL){
				small1=dfs2(cur->child,small1);
				tem1=new;
				while(tem1->next!=NULL)
					tem1=tem1->next;
				tem1->next=small1;
			}
		cur=cur->next;		
		}
	ptr->l=new;
	return ptr;	
	}
	if(strcmp(ptr->nodeSymbol,"<booleanExpression>")==0){
		new=dfs2(ptr,new);
		ptr->l=new;
		return ptr;
	}
	if(strcmp(ptr->nodeSymbol,"<ioStmt>")==0){
		cur=ptr->l;
		while(cur!=NULL){
			if(strcmp(cur->child->name,"READ")==0 || strcmp(cur->child->name,"PRINT")==0 || strcmp(cur->child->name,"ID")==0)
				new=add1(new,cur->child);
			cur=cur->next;
		}
	ptr->l=new;
	return ptr;
	}

return ptr;
}

trPtr traverse(trPtr t){
	//printf("--------------hello");
	if(strcmp(t->isLeafNode,"Yes")==0 ||t->l==NULL)
		return t;
	//printf("-----------------hello");
	t=actionTaken(t);
	ptrList cur=t->l;
	while(cur!=NULL){
		//printf("%s------HELLOO----%s\n",cur->child->nodeSymbol,cur->child->lexemeCurrentNode);
		cur->child=traverse(cur->child);
		
		cur=cur->next;
		
	}
	//printf("---hello");
	return t;	
}

trPtr buildParseTree(trPtr pT){
	int i=0;
	ptrList new=NULL;
	ptrList cur= pT->l;
	while(cur!=NULL){
		/*if(checkifLeaf(cur->child) && (strcmp(cur->child->name,"MAIN")!=0 || strcmp(cur->child->name,"END")!=0))
		{
			free(cur->child);
		}
		*/
		if(!checkifLeaf(cur->child) || strcmp(cur->child->name,"MAIN")==0 || strcmp(cur->child->name,"END")==0)
				{
				//printf("Hello %s \n",cur->child->nodeSymbol);	
				if(!checkifLeaf(cur->child))
					{
						cur->child=traverse(cur->child);
						new=add1(new,cur->child);
					}
				else{
				
				//printf("Hello\n");
					new=add1(new,cur->child);
				}
				}
		
	cur=cur->next;
	}	
	pT->l=new;
	return pT;
	/*
	if(temp->child==NULL)
	{
		pT->l=temp->next;
		free(temp);
		temp=pT->l->next;
	}
	
	cur=temp;
	while(cur!=NULL){
		if(cur->child==NULL)
		{
			temp=cur;
			cur=temp->next;
			free(temp);					
		}
		else{
			cur=cur->next;
			
		}
	}
	*/
}
/*
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

	Tree=parseInputSourceCode(fptr,pt,grammar);
	printParseTree(Tree,out);
	
	Tree=buildParseTree(Tree);
	if(Tree==NULL)
		printf("----------Hello-----------\n");
	printAst(Tree);
return 1;
}
*/