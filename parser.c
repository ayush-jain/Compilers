/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "lexer.h"
#include "parser.h"

int isTerminal(int i){
	if(i>=101)
		return 1;
	else
		return 0;
}


int hash(char *key)
{
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
	
if(key[0]=='<'){
	if(ltable[hnew].isEmpty=='y') {
		ltable[hnew].isEmpty='n';
		ltable[hnew].lhs=(char *)malloc((strlen(key)+1)*sizeof(char));
		strcpy(ltable[hnew].lhs,key);
		return hnew;
	}
	else
	{
		while(ltable[hnew].isEmpty=='n')
		{	
			//printf("%d %s\n", hnew, key);
			if (strcmp(ltable[hnew].lhs,key) == 0) {return hnew;}
			else {
				if(hnew==98) 
					hnew=0;
				else 
					hnew++;
			}
			//printf("DOIT");
		}
		ltable[hnew].isEmpty='n';
		ltable[hnew].lhs=(char *)malloc((strlen(key)+1)*sizeof(char));
		strcpy(ltable[hnew].lhs,key);
	}
	//printf("%d %s\n", hnew, key);
	return hnew;
}
else{
	if(terminal[hnew]==NULL)
		{terminal[hnew]=(char *)malloc((strlen(key)+1)*sizeof(char)); strcpy(terminal[hnew],key);}
	else{
		
		while(terminal[hnew]!=NULL){
			if (strcmp(terminal[hnew],key) == 0) {break;}
			else{ 
				if(hnew==98)
					hnew=0;	
				else
					hnew++;		
				}
			}
		terminal[hnew]=(char *)malloc((strlen(key)+1)*sizeof(char));
		strcpy(terminal[hnew],key);
	}
	return hnew+103;
}
}
/*
int main(){

	int p1,p2,p3;
	p1=hash("<matrix>");
	p2=hash("<otherStmts>");
	p3=hash("<RemainingIf>");
	printf("%d %d %d\n",p1,p2,p3);
}
*/



ptr add(int key,int tkey,ptr p,ptr r){

	ptr e1=(ptr)malloc(sizeof(E));
	if(p==NULL){
		p=e1;
		e1->val=tkey;
		ltable[key].rrhs[ltable[key].count]=e1;
		return p;
	}else{

	//while(cur->next!=NULL)
		//cur=cur->next;
	e1->val=tkey;
	e1->next=p;
	p=e1;
	e1->next->prev=e1;
	return p;
	}	
return p;
}

rule* createG(FILE *fp){
	int i,j=0;
	rule *r=(rule *)malloc(100*sizeof(rule));
	for(i=0;i<100;i++){
		ltable[i].isEmpty='y';
		ltable[i].count=0;
		rtable[i].count=0;

	}
	char temp[400];
	char *tok;
	int key,tkey;
	i=1;
	int *last;
	while(fgets(temp,sizeof(temp),fp)!=NULL){
		//printf("%s\n",temp);
		if(temp==NULL)
			break;
		tok=strtok(temp," -\n");
		key=hash(tok);
		//printf("LHS-%s--%d\n",tok,key);
		r[i].left=key;
		//ltable[key].isEmpty='n';
			while(tok!=NULL){
				//printf("???HELLLO\n");
				tok=strtok (NULL," -\n");
				//printf("???HELLLO\n");
					if(tok==NULL)
						break;
				//printf("\n%s---HELLO\n",tok);	
				
				if(strcmp(tok,"EPSILON")==0)
					tkey=101;
				else
					tkey=hash(tok);
					
				
				//printf("KEYYYYYYYYYYYY ---%d\n",tkey);
				//if(tkey==67 || key==67)
				//printf("RHS------%s---%d----\n",tok,tkey);
				
				ltable[key].rhs[ltable[key].count]=add(key,tkey,ltable[key].rhs[ltable[key].count],ltable[key].rrhs[ltable[key].count]);
				
				if(!isTerminal(tkey)){
					rtable[tkey].arg[rtable[tkey].count]=ltable[key].rrhs[ltable[key].count];
				//printf("-----------------???HELLLO\n");
					rtable[tkey].arglhs[rtable[tkey].count]=key;
					rtable[tkey].count++;

					}
			}
			
		r[i].right=ltable[key].rhs[ltable[key].count];	
		r[i++].rright=ltable[key].rrhs[ltable[key].count];
		ltable[key].count++;	

	}

return r;
}

//void auto_first(){


//}







ptr addfill(int key,int tkey,ptr p){

	ptr e1=(ptr)malloc(sizeof(E));
	if(p==NULL){
		p=e1;
		e1->val=tkey;
		return p;
	}else{

	//while(cur->next!=NULL)
		//cur=cur->next;
	e1->val=tkey;
	e1->next=p;
	p=e1;
	e1->next->prev=e1;
	return p;
	}	
return p;
}
int containsEpsilon(ptr p){

	while(p!=NULL){
		
			if(p->val==101)
				return 1;	
			
			else
				p=p->next;

	}
return 0;	
}


ptr first(int i){
	
	ptr temp;
	ptr cur;
	if(ltable[i].first!=NULL)
	{
		return ltable[i].first;
	}
	else{
	
	int j;
	for(j=0;j<ltable[i].count;j++){
		cur=ltable[i].rrhs[j];
		//printf("HELLO %s    %d----\n",ltable[i].lhs,cur->val);
		if(isTerminal(cur->val)==0){
		temp=first(cur->val);
		cur=cur->prev;
		while(containsEpsilon(temp)&&cur!=NULL)
			{ 
				while(temp!=NULL){
				ltable[i].first=addfill(i,temp->val,ltable[i].first); 
				temp=temp->next;
				}
				temp=first(cur->val);cur=cur->prev;
				
		}
		while(temp!=NULL)
			{ ltable[i].first=addfill(i,temp->val,ltable[i].first); temp=temp->next;
			}
		}
		else{
			//if(cur->val!=101)
				//printf("%s terminal %s\n",ltable[i].lhs,terminal[(cur->val)-103]);
			ltable[i].first=addfill(i,cur->val,ltable[i].first);
		}

	
		}
	}
return ltable[i].first;
}
/*
ptr auto_follow(int i){
	int j=0;
	if(check[i]==1)
		return;
	check[i]=1;
	ptr temp;
	ptr cur;
	//if(ltable[i].follow!=NULL){
	//	return ltable[i].follow;
	//}
	{

		for(j=0;j<rtable[i].count;j++){
			cur=rtable[i].arg[j]->prev;
			if(cur!=NULL){
				if(isTerminal(cur->val)==0){

					temp=first(cur->val);
					cur=cur->prev;
					while(containsEpsilon(temp)&&cur!=NULL)
					{ 
					while(temp!=NULL){
						ltable[i].follow=addfill(i,temp->val,ltable[i].follow); 
						temp=temp->next;
					}
					temp=first(cur->val);cur=cur->prev;
					}
					if((!containsEpsilon(temp))){
						while(temp!=NULL){
							ltable[i].follow=addfill(i,temp->val,ltable[i].follow);
							temp=temp->next;
						}	
					}
					else if(!containsEpsilon(temp)&& cur==NULL){
						while(temp!=NULL){
							ltable[i].follow=addfill(i,temp->val,ltable[i].follow);
							temp=temp->next;
						}
						temp=follow(rtable[i].arglhs[count]);
						while(temp!=NULL){
							ltable[i].follow=addfill(i,temp->val,ltable[i].follow);
							temp=temp->next;
						}	
					}

				}
				else{
					ltable[i].follow=addfill(i,cur->val,ltable[i].follow);
					
				}

			}
			else{

				temp=follow(rtable[i].arglhs[count]);
				while(temp!=NULL){
					ltable[i].follow=addfill(i,temp->val,ltable[i].follow);
					temp=temp->next;
				}
			}
		}


	}
return ltable[i].follow;
}
*/

void fillFirst(){
	int i;
	for(i=0;i<100;i++){
		if(ltable[i].isEmpty=='n')
			{
			ltable[i].first=first(i);	
			}
	}
	
return;
}

/*
void fillFollow(){
	int i;
	ltable[38].follow=addfill(38,102,ltable[38].follow);
	for(i=0;i<100;i++){
		if(ltable[i].isEmpty=='n'){
			ltable[i].follow=follow(i);
		}
	}
return ;
}
*/






void fillfollow(){

	ltable[38].follow=addfill(38,102,ltable[38].follow);

    ltable[29].follow=addfill(29,193,ltable[29].follow);

    ltable[65].follow=addfill(65,193,ltable[65].follow);

    ltable[2].follow=addfill(2,165,ltable[2].follow);
    ltable[2].follow=addfill(2,130,ltable[2].follow);
    ltable[2].follow=addfill(2,180,ltable[2].follow);
    ltable[2].follow=addfill(2,181,ltable[2].follow);
    ltable[2].follow=addfill(2,129,ltable[2].follow);
    ltable[2].follow=addfill(2,197,ltable[2].follow);
    ltable[2].follow=addfill(2,186,ltable[2].follow);
    ltable[2].follow=addfill(2,187,ltable[2].follow);
    ltable[2].follow=addfill(2,159,ltable[2].follow);
    ltable[2].follow=addfill(2,191,ltable[2].follow);
    ltable[2].follow=addfill(2,127,ltable[2].follow);
    ltable[2].follow=addfill(2,193,ltable[2].follow);

    ltable[49].follow=addfill(49,165,ltable[49].follow);
    ltable[49].follow=addfill(49,130,ltable[49].follow);
    ltable[49].follow=addfill(49,180,ltable[49].follow);
    ltable[49].follow=addfill(49,181,ltable[49].follow);
    ltable[49].follow=addfill(49,129,ltable[49].follow);
    ltable[49].follow=addfill(49,197,ltable[49].follow);
    ltable[49].follow=addfill(49,186,ltable[49].follow);
    ltable[49].follow=addfill(49,187,ltable[49].follow);
    ltable[49].follow=addfill(49,159,ltable[49].follow);
    ltable[49].follow=addfill(49,191,ltable[49].follow);
    ltable[49].follow=addfill(49,108,ltable[49].follow);
    ltable[49].follow=addfill(49,174,ltable[49].follow);
    ltable[49].follow=addfill(49,127,ltable[49].follow);
    ltable[49].follow=addfill(49,193,ltable[49].follow);

    ltable[81].follow=addfill(81,165,ltable[81].follow);
    ltable[81].follow=addfill(81,130,ltable[81].follow);
    ltable[81].follow=addfill(81,180,ltable[81].follow);
    ltable[81].follow=addfill(81,181,ltable[81].follow);
    ltable[81].follow=addfill(81,129,ltable[81].follow);
    ltable[81].follow=addfill(81,197,ltable[81].follow);
    ltable[81].follow=addfill(81,186,ltable[81].follow);
    ltable[81].follow=addfill(81,187,ltable[81].follow);
    ltable[81].follow=addfill(81,159,ltable[81].follow);
    ltable[81].follow=addfill(81,191,ltable[81].follow);
    ltable[81].follow=addfill(81,127,ltable[81].follow);
    ltable[81].follow=addfill(81,193,ltable[81].follow);

    ltable[42].follow=addfill(42,192,ltable[42].follow);

    ltable[89].follow=addfill(89,187,ltable[89].follow);

    ltable[55].follow=addfill(55,192,ltable[55].follow);

    ltable[11].follow=addfill(11,165,ltable[11].follow);
    ltable[11].follow=addfill(11,130,ltable[11].follow);
    ltable[11].follow=addfill(11,180,ltable[11].follow);
    ltable[11].follow=addfill(11,181,ltable[11].follow);
    ltable[11].follow=addfill(11,129,ltable[11].follow);
    ltable[11].follow=addfill(11,197,ltable[11].follow);
    ltable[11].follow=addfill(11,186,ltable[11].follow);
    ltable[11].follow=addfill(11,187,ltable[11].follow);
    ltable[11].follow=addfill(11,159,ltable[11].follow);
    ltable[11].follow=addfill(11,191,ltable[11].follow);
    ltable[11].follow=addfill(11,108,ltable[11].follow);
    ltable[11].follow=addfill(11,174,ltable[11].follow);
    ltable[11].follow=addfill(11,127,ltable[11].follow);
    ltable[11].follow=addfill(11,193,ltable[11].follow);

    ltable[63].follow=addfill(63,192,ltable[63].follow);
    ltable[63].follow=addfill(63,113,ltable[63].follow);

    ltable[24].follow=addfill(24,192,ltable[24].follow);
    ltable[24].follow=addfill(24,113,ltable[24].follow);

    ltable[0].follow=addfill(0,165,ltable[0].follow);
    ltable[0].follow=addfill(0,130,ltable[0].follow);
    ltable[0].follow=addfill(0,180,ltable[0].follow);
    ltable[0].follow=addfill(0,181,ltable[0].follow);
    ltable[0].follow=addfill(0,129,ltable[0].follow);
    ltable[0].follow=addfill(0,197,ltable[0].follow);
    ltable[0].follow=addfill(0,186,ltable[0].follow);
    ltable[0].follow=addfill(0,187,ltable[0].follow);
    ltable[0].follow=addfill(0,159,ltable[0].follow);
    ltable[0].follow=addfill(0,191,ltable[0].follow);
    ltable[0].follow=addfill(0,108,ltable[0].follow);
    ltable[0].follow=addfill(0,174,ltable[0].follow);
    ltable[0].follow=addfill(0,127,ltable[0].follow);
    ltable[0].follow=addfill(0,193,ltable[0].follow);

    ltable[59].follow=addfill(59,165,ltable[59].follow);
    ltable[59].follow=addfill(59,130,ltable[59].follow);
    ltable[59].follow=addfill(59,180,ltable[59].follow);
    ltable[59].follow=addfill(59,181,ltable[59].follow);
    ltable[59].follow=addfill(59,129,ltable[59].follow);
    ltable[59].follow=addfill(59,197,ltable[59].follow);
    ltable[59].follow=addfill(59,186,ltable[59].follow);
    ltable[59].follow=addfill(59,187,ltable[59].follow);
    ltable[59].follow=addfill(59,159,ltable[59].follow);
    ltable[59].follow=addfill(59,191,ltable[59].follow);
    ltable[59].follow=addfill(59,108,ltable[59].follow);
    ltable[59].follow=addfill(59,174,ltable[59].follow);
    ltable[59].follow=addfill(59,127,ltable[59].follow);
    ltable[59].follow=addfill(59,193,ltable[59].follow);
    
    ltable[80].follow=addfill(80,179,ltable[80].follow);

    ltable[1].follow=addfill(1,179,ltable[1].follow);

    ltable[13].follow=addfill(13,113,ltable[13].follow);

    ltable[37].follow=addfill(37,113,ltable[37].follow);

    ltable[20].follow=addfill(20,113,ltable[20].follow);

    ltable[84].follow=addfill(84,165,ltable[84].follow);
    ltable[84].follow=addfill(84,130,ltable[84].follow);
    ltable[84].follow=addfill(84,180,ltable[84].follow);
    ltable[84].follow=addfill(84,181,ltable[84].follow);
    ltable[84].follow=addfill(84,129,ltable[84].follow);
    ltable[84].follow=addfill(84,197,ltable[84].follow);
    ltable[84].follow=addfill(84,186,ltable[84].follow);
    ltable[84].follow=addfill(84,187,ltable[84].follow);
    ltable[84].follow=addfill(84,159,ltable[84].follow);
    ltable[84].follow=addfill(84,191,ltable[84].follow);
    ltable[84].follow=addfill(84,108,ltable[84].follow);
    ltable[84].follow=addfill(84,174,ltable[84].follow);
    ltable[84].follow=addfill(84,127,ltable[84].follow);
    ltable[84].follow=addfill(84,193,ltable[84].follow);

    ltable[67].follow=addfill(67,165,ltable[67].follow);
    ltable[67].follow=addfill(67,130,ltable[67].follow);
    ltable[67].follow=addfill(67,180,ltable[67].follow);
    ltable[67].follow=addfill(67,181,ltable[67].follow);
    ltable[67].follow=addfill(67,129,ltable[67].follow);
    ltable[67].follow=addfill(67,197,ltable[67].follow);
    ltable[67].follow=addfill(67,186,ltable[67].follow);
    ltable[67].follow=addfill(67,187,ltable[67].follow);
    ltable[67].follow=addfill(67,159,ltable[67].follow);
    ltable[67].follow=addfill(67,191,ltable[67].follow);
    ltable[67].follow=addfill(67,108,ltable[67].follow);
    ltable[67].follow=addfill(67,174,ltable[67].follow);
    ltable[67].follow=addfill(67,127,ltable[67].follow);
    ltable[67].follow=addfill(67,193,ltable[67].follow);

    ltable[77].follow=addfill(77,108,ltable[77].follow);
    ltable[77].follow=addfill(77,174,ltable[77].follow);

    ltable[70].follow=addfill(70,165,ltable[70].follow);
    ltable[70].follow=addfill(70,130,ltable[70].follow);
    ltable[70].follow=addfill(70,180,ltable[70].follow);
    ltable[70].follow=addfill(70,181,ltable[70].follow);
    ltable[70].follow=addfill(70,129,ltable[70].follow);
    ltable[70].follow=addfill(70,197,ltable[70].follow);
    ltable[70].follow=addfill(70,186,ltable[70].follow);
    ltable[70].follow=addfill(70,187,ltable[70].follow);
    ltable[70].follow=addfill(70,159,ltable[70].follow);
    ltable[70].follow=addfill(70,191,ltable[70].follow);
    ltable[70].follow=addfill(70,108,ltable[70].follow);
    ltable[70].follow=addfill(70,174,ltable[70].follow);
    ltable[70].follow=addfill(70,127,ltable[70].follow);
    ltable[70].follow=addfill(70,193,ltable[70].follow);

    ltable[23].follow=addfill(23,113,ltable[23].follow);
    ltable[23].follow=addfill(23,165,ltable[23].follow);
    ltable[23].follow=addfill(23,130,ltable[23].follow);
    ltable[23].follow=addfill(23,180,ltable[23].follow);
    ltable[23].follow=addfill(23,181,ltable[23].follow);
    ltable[23].follow=addfill(23,129,ltable[23].follow);
    ltable[23].follow=addfill(23,197,ltable[23].follow);
    ltable[23].follow=addfill(23,186,ltable[23].follow);
    ltable[23].follow=addfill(23,187,ltable[23].follow);
    ltable[23].follow=addfill(23,159,ltable[23].follow);
    ltable[23].follow=addfill(23,191,ltable[23].follow);
    ltable[23].follow=addfill(23,108,ltable[23].follow);
    ltable[23].follow=addfill(23,174,ltable[23].follow);
    ltable[23].follow=addfill(23,127,ltable[23].follow);
    ltable[23].follow=addfill(23,193,ltable[70].follow);

    ltable[66].follow=addfill(66,194,ltable[66].follow);

    ltable[14].follow=addfill(14,194,ltable[14].follow);

    ltable[25].follow=addfill(25,194,ltable[25].follow);
    ltable[25].follow=addfill(25,113,ltable[25].follow);

    ltable[85].follow=addfill(85,194,ltable[85].follow);
    ltable[85].follow=addfill(85,113,ltable[85].follow);

    ltable[40].follow=addfill(40,115,ltable[40].follow);
    ltable[40].follow=addfill(40,178,ltable[40].follow);
    ltable[40].follow=addfill(40,194,ltable[40].follow);
    ltable[40].follow=addfill(40,113,ltable[40].follow);

    ltable[41].follow=addfill(41,115,ltable[41].follow);
    ltable[41].follow=addfill(41,178,ltable[41].follow);
    ltable[41].follow=addfill(41,194,ltable[41].follow);
    ltable[41].follow=addfill(41,113,ltable[41].follow);

    ltable[62].follow=addfill(62,109,ltable[62].follow);
    ltable[62].follow=addfill(62,111,ltable[62].follow);
    ltable[62].follow=addfill(62,115,ltable[62].follow);
    ltable[62].follow=addfill(62,178,ltable[62].follow);
    ltable[62].follow=addfill(62,194,ltable[62].follow);
    ltable[62].follow=addfill(62,113,ltable[62].follow);

    ltable[12].follow=addfill(12,124,ltable[12].follow);
    ltable[12].follow=addfill(12,187,ltable[12].follow);
    ltable[12].follow=addfill(12,118,ltable[12].follow);
    ltable[12].follow=addfill(12,188,ltable[12].follow);
    ltable[12].follow=addfill(12,156,ltable[12].follow);
    ltable[12].follow=addfill(12,129,ltable[12].follow);

    ltable[15].follow=addfill(15,124,ltable[15].follow);
    ltable[15].follow=addfill(15,187,ltable[15].follow);
    ltable[15].follow=addfill(15,118,ltable[15].follow);
    ltable[15].follow=addfill(15,188,ltable[15].follow);
    ltable[15].follow=addfill(15,156,ltable[15].follow);
    ltable[15].follow=addfill(15,129,ltable[15].follow);

   ltable[60].follow=addfill(60,194,ltable[60].follow);

   ltable[75].follow=addfill(75,126,ltable[75].follow);
   ltable[75].follow=addfill(75,195,ltable[75].follow);
   ltable[75].follow=addfill(75,106,ltable[75].follow);
   ltable[75].follow=addfill(75,116,ltable[75].follow);
   ltable[75].follow=addfill(75,185,ltable[75].follow);
   ltable[75].follow=addfill(75,199,ltable[75].follow);
   ltable[75].follow=addfill(75,194,ltable[75].follow);

   ltable[68].follow=addfill(68,182,ltable[68].follow);
   ltable[68].follow=addfill(68,109,ltable[68].follow);
   ltable[68].follow=addfill(68,111,ltable[68].follow);
   ltable[68].follow=addfill(68,115,ltable[68].follow);
   ltable[68].follow=addfill(68,178,ltable[68].follow);
   ltable[68].follow=addfill(68,194,ltable[68].follow);
   ltable[68].follow=addfill(68,113,ltable[68].follow);

   ltable[78].follow=addfill(78,182,ltable[78].follow);
   ltable[78].follow=addfill(78,109,ltable[78].follow);
   ltable[78].follow=addfill(78,111,ltable[78].follow);
   ltable[78].follow=addfill(78,115,ltable[78].follow);
   ltable[78].follow=addfill(78,178,ltable[78].follow);
   ltable[78].follow=addfill(78,194,ltable[78].follow);
   ltable[78].follow=addfill(78,113,ltable[78].follow);

   ltable[16].follow=addfill(16,192,ltable[16].follow);

   ltable[26].follow=addfill(26,113,ltable[26].follow);
   ltable[26].follow=addfill(26,192,ltable[26].follow);

   ltable[50].follow=addfill(50,113,ltable[50].follow);
   ltable[50].follow=addfill(50,192,ltable[50].follow);

   ltable[82].follow=addfill(82,182,ltable[82].follow);
   ltable[82].follow=addfill(82,109,ltable[82].follow);
   ltable[82].follow=addfill(82,111,ltable[82].follow);
   ltable[82].follow=addfill(82,115,ltable[82].follow);
   ltable[82].follow=addfill(82,178,ltable[82].follow);
   ltable[82].follow=addfill(82,194,ltable[82].follow);
   ltable[82].follow=addfill(82,113,ltable[68].follow);

   ltable[69].follow=addfill(69,124,ltable[69].follow);

   ltable[71].follow=addfill(71,187,ltable[71].follow);
   ltable[71].follow=addfill(71,118,ltable[71].follow);
   ltable[71].follow=addfill(71,188,ltable[71].follow);

return;	
}
/*
int main(){
	int i=0;
	FILE *f=fopen("grammar.txt","r");
	rule *grammar=createG(f);
	fillFirst();
	fillfollow();
	//printf("hello");
	ptr cur;
	for(i=1;i<100;i++){
		cur=ltable[grammar[i].left].follow;
		if(cur==NULL)
			continue;
		printf("\nLHS--%s--%d----\n",ltable[grammar[i].left].lhs,grammar[i].left);
		while(cur!=NULL){
			printf("FOLLOW---%s---%d---\n",terminal[(cur->val)-103],cur->val);
			cur=cur->next;
		}
		//printf("??? %s\n",terminal[165-103]);
		
	}


return 0;
}
*/
void fillfirst(){

	ltable[38].first=addfill(38,117,ltable[38].first);

	ltable[65].first=addfill(65,101,ltable[65].first);
	ltable[65].first=addfill(65,165,ltable[65].first);
	ltable[65].first=addfill(65,130,ltable[65].first);
	ltable[65].first=addfill(65,180,ltable[65].first);
	ltable[65].first=addfill(65,181,ltable[65].first);
	ltable[65].first=addfill(65,129,ltable[65].first);
	ltable[65].first=addfill(65,197,ltable[65].first);
	ltable[65].first=addfill(65,186,ltable[65].first);
	ltable[65].first=addfill(65,187,ltable[65].first);
	ltable[65].first=addfill(65,159,ltable[65].first);
	ltable[65].first=addfill(65,191,ltable[65].first);
	ltable[65].first=addfill(65,127,ltable[65].first);
	
	ltable[81].first=addfill(81,127,ltable[81].first);

	ltable[89].first=addfill(89,165,ltable[89].first);
	ltable[89].first=addfill(89,130,ltable[89].first);
	ltable[89].first=addfill(89,180,ltable[89].first);
	ltable[89].first=addfill(89,181,ltable[89].first);	

	ltable[55].first=addfill(55,182,ltable[55].first);
	ltable[55].first=addfill(55,101,ltable[55].first);

	ltable[63].first=addfill(63,187,ltable[63].first);

	ltable[24].first=addfill(24,182,ltable[24].first);
	ltable[24].first=addfill(24,101,ltable[24].first);

	ltable[80].first=addfill(80,187,ltable[80].first);

    ltable[1].first=addfill(1,129,ltable[1].first);	

    ltable[20].first=addfill(20,119,ltable[20].first);

    ltable[84].first=addfill(84,191,ltable[84].first);

    ltable[67].first=addfill(67,174,ltable[67].first);
    ltable[67].first=addfill(67,108,ltable[67].first);

    ltable[77].first=addfill(77,101,ltable[77].first);
    ltable[77].first=addfill(77,165,ltable[77].first);
    ltable[77].first=addfill(77,130,ltable[77].first);
    ltable[77].first=addfill(77,180,ltable[77].first);
    ltable[77].first=addfill(77,181,ltable[77].first);
    ltable[77].first=addfill(77,129,ltable[77].first);
    ltable[77].first=addfill(77,197,ltable[77].first);
    ltable[77].first=addfill(77,186,ltable[77].first);
    ltable[77].first=addfill(77,187,ltable[77].first);
    ltable[77].first=addfill(77,159,ltable[77].first);
    ltable[77].first=addfill(77,191,ltable[77].first);

    ltable[70].first=addfill(70,197,ltable[70].first);
    ltable[70].first=addfill(70,186,ltable[70].first);

    ltable[23].first=addfill(23,159,ltable[23].first);

    ltable[66].first=addfill(66,101,ltable[66].first);
    ltable[66].first=addfill(66,187,ltable[66].first);
    ltable[66].first=addfill(66,118,ltable[66].first);
    ltable[66].first=addfill(66,188,ltable[66].first);
    ltable[66].first=addfill(66,156,ltable[66].first);
    ltable[66].first=addfill(66,129,ltable[66].first);

    ltable[14].first=addfill(14,182,ltable[14].first);
    ltable[14].first=addfill(14,101,ltable[14].first);

    ltable[85].first=addfill(85,101,ltable[85].first);
    ltable[85].first=addfill(85,115,ltable[85].first);
    ltable[85].first=addfill(85,178,ltable[85].first);

    ltable[41].first=addfill(41,101,ltable[23].first);
    ltable[41].first=addfill(41,109,ltable[23].first);
    ltable[41].first=addfill(41,111,ltable[23].first);
    
    ltable[62].first=addfill(62,124,ltable[62].first);
    ltable[62].first=addfill(62,187,ltable[62].first);
    ltable[62].first=addfill(62,118,ltable[62].first);
    ltable[62].first=addfill(62,188,ltable[62].first);
    ltable[62].first=addfill(62,156,ltable[62].first);
    ltable[62].first=addfill(62,129,ltable[62].first);

    ltable[12].first=addfill(12,115,ltable[12].first);
    ltable[12].first=addfill(12,178,ltable[12].first);

    ltable[15].first=addfill(15,109,ltable[15].first);
    ltable[15].first=addfill(15,111,ltable[15].first);

    ltable[60].first=addfill(60,124,ltable[60].first);
    ltable[60].first=addfill(60,201,ltable[60].first);
    ltable[60].first=addfill(60,187,ltable[60].first);
    ltable[60].first=addfill(60,118,ltable[60].first);
    ltable[60].first=addfill(60,188,ltable[60].first);

    ltable[75].first=addfill(75,187,ltable[75].first);
    ltable[75].first=addfill(75,118,ltable[75].first);
    ltable[75].first=addfill(75,188,ltable[75].first);

    ltable[68].first=addfill(68,187,ltable[68].first);
    ltable[68].first=addfill(68,118,ltable[68].first);
    ltable[68].first=addfill(68,188,ltable[68].first);
    ltable[68].first=addfill(68,156,ltable[68].first);
    ltable[68].first=addfill(68,129,ltable[68].first);

    ltable[78].first=addfill(78,129,ltable[78].first);

    ltable[16].first=addfill(16,113,ltable[16].first);
    ltable[16].first=addfill(16,101,ltable[16].first);

    ltable[26].first=addfill(26,118,ltable[26].first);

    ltable[50].first=addfill(50,182,ltable[50].first);
    ltable[50].first=addfill(50,101,ltable[50].first);

    ltable[82].first=addfill(82,129,ltable[82].first);
    ltable[82].first=addfill(82,101,ltable[82].first);

    ltable[69].first=addfill(69,168,ltable[69].first);
    ltable[69].first=addfill(69,128,ltable[69].first);

    ltable[71].first=addfill(71,126,ltable[71].first);
    ltable[71].first=addfill(71,195,ltable[71].first);
    ltable[71].first=addfill(71,106,ltable[71].first);
    ltable[71].first=addfill(71,116,ltable[71].first);
    ltable[71].first=addfill(71,185,ltable[71].first);
    ltable[71].first=addfill(71,199,ltable[71].first);

    ltable[42].first=addfill(42,165,ltable[42].first);
    ltable[42].first=addfill(42,130,ltable[42].first);
    ltable[42].first=addfill(42,180,ltable[42].first);
    ltable[42].first=addfill(42,181,ltable[42].first);

    ltable[11].first=addfill(11,165,ltable[11].first);
    ltable[11].first=addfill(11,130,ltable[11].first);
    ltable[11].first=addfill(11,180,ltable[11].first);
    ltable[11].first=addfill(11,181,ltable[11].first);

    ltable[0].first=addfill(0,187,ltable[0].first);

    ltable[59].first=addfill(59,129,ltable[59].first);

    ltable[37].first=addfill(37,119,ltable[37].first);
    ltable[37].first=addfill(37,159,ltable[37].first);

    ltable[49].first=addfill(49,165,ltable[49].first);
    ltable[49].first=addfill(49,130,ltable[49].first);
    ltable[49].first=addfill(49,180,ltable[49].first);
    ltable[49].first=addfill(49,181,ltable[49].first);
    ltable[49].first=addfill(49,129,ltable[49].first);
    ltable[49].first=addfill(49,197,ltable[49].first);
    ltable[49].first=addfill(49,186,ltable[49].first);
    ltable[49].first=addfill(49,187,ltable[49].first);
    ltable[49].first=addfill(49,159,ltable[49].first);
    ltable[49].first=addfill(49,191,ltable[49].first);

    ltable[40].first=addfill(40,124,ltable[40].first);
    ltable[40].first=addfill(40,187,ltable[40].first);
    ltable[40].first=addfill(40,118,ltable[40].first);
    ltable[40].first=addfill(40,188,ltable[40].first);
    ltable[40].first=addfill(40,156,ltable[40].first);
    ltable[40].first=addfill(40,129,ltable[40].first);

    ltable[25].first=addfill(25,124,ltable[25].first);
    ltable[25].first=addfill(25,187,ltable[25].first);
    ltable[25].first=addfill(25,118,ltable[25].first);
    ltable[25].first=addfill(25,188,ltable[25].first);
    ltable[25].first=addfill(25,156,ltable[25].first);
    ltable[25].first=addfill(25,129,ltable[25].first);

    ltable[2].first=addfill(2,165,ltable[2].first);
    ltable[2].first=addfill(2,130,ltable[2].first);
    ltable[2].first=addfill(2,180,ltable[2].first);
    ltable[2].first=addfill(2,181,ltable[2].first);
    ltable[2].first=addfill(2,129,ltable[2].first);
    ltable[2].first=addfill(2,197,ltable[2].first);
    ltable[2].first=addfill(2,186,ltable[2].first);
    ltable[2].first=addfill(2,187,ltable[2].first);
    ltable[2].first=addfill(2,159,ltable[2].first);
    ltable[2].first=addfill(2,191,ltable[2].first);
    ltable[2].first=addfill(2,127,ltable[2].first);
    
    ltable[13].first=addfill(13,124,ltable[13].first);
    ltable[13].first=addfill(13,187,ltable[13].first);
    ltable[13].first=addfill(13,118,ltable[13].first);
    ltable[13].first=addfill(13,188,ltable[13].first);
    ltable[13].first=addfill(13,156,ltable[13].first);
    ltable[13].first=addfill(13,129,ltable[13].first);
    ltable[13].first=addfill(13,159,ltable[13].first);
    ltable[13].first=addfill(13,119,ltable[13].first);

    ltable[29].first=addfill(29,165,ltable[29].first);
    ltable[29].first=addfill(29,130,ltable[29].first);
    ltable[29].first=addfill(29,180,ltable[29].first);
    ltable[29].first=addfill(29,181,ltable[29].first);
    ltable[29].first=addfill(29,129,ltable[29].first);
    ltable[29].first=addfill(29,197,ltable[29].first);
    ltable[29].first=addfill(29,186,ltable[29].first);
    ltable[29].first=addfill(29,187,ltable[29].first);
    ltable[29].first=addfill(29,159,ltable[29].first);
    ltable[29].first=addfill(29,191,ltable[29].first);
    ltable[29].first=addfill(29,127,ltable[29].first);

return;	
}


int** newparseTable(){

	int **parseTable=(int **)malloc(100*sizeof(int *));

	int i =0;
	for(i=0;i<100;i++){
		parseTable[i]=(int *)calloc(102,sizeof(int));
		fillfirst();
		fillfollow();		

	}
	return parseTable;
}

int** createParseTable(rule* grammar, int **parseTable){

	int i=1;
	ptr cur,cur1;
	int flag=0;
	while(grammar[i].right!=NULL){
		if(grammar[i].right->val==101){

			cur=ltable[grammar[i].left].follow;
			while(cur!=NULL){
				if(cur->val==102)
					parseTable[grammar[i].left][102]=i;
				else
					parseTable[grammar[i].left][(cur->val)-103]=i;
				cur=cur->next;
			}
	}else{
			cur=grammar[i].rright;
			//printf("%d-----RHS\n",cur->val);
			if(isTerminal(cur->val))
				parseTable[grammar[i].left][(cur->val)-103]=i;
			else{
			while(cur!=NULL){

			cur1=ltable[cur->val].first;
			while(cur1!=NULL){
				if(cur1->val==101)
					{ cur1=cur1->next;flag=1; continue;}								
				parseTable[grammar[i].left][(cur1->val)-103]=i;
				//printf("%d\n",i);
				cur1=cur1->next;
			}
			if(flag==1)
				cur=cur->prev;
			else
				break;	
			}
		}
	}

	i++;	
	}
return parseTable;
}
/*
int main(){
	rule *grammar;
	FILE *fp=NULL;
	FILE *fptr=NULL;
	fp=fopen("grammar.txt","r");
	trPtr Tree;
	int **pt=newparseTable();
	grammar=createG(fp);
	int i,j=0;
	pt=createParseTable(grammar,pt);
	for(i=0;i<100;i++){
		for(j=0;j<102;j++){
			if(pt[i][j]!=0)
			printf("%s %s %d\n",ltable[i].lhs,terminal[j],pt[i][j]);
		}
		
	}	
	

return 0;
}
*/

stack createStack(){

	stack s;
	s=(stack)malloc(sizeof(st));
	s->head=NULL;
	s->size=0;
	return s;
}

stack push(stack s,int num,trPtr pi){

	ndPtr ptr;
	ptr=(ndPtr)malloc(sizeof(NODE));
	ptr->id=num;
	ptr->next=s->head;
	s->size++;
	s->head=ptr;
	ptr->p=pi;
	return s;
}

stack pop(stack s){

	ndPtr temp;
	temp=s->head;
	s->head=temp->next;
	free(temp);
	s->size--;
	return s;


}

trPtr addtrNode(trPtr t,int val,tokenInfo tok){

	trPtr temp;
	ptrList cur;
	temp=(trPtr)malloc(sizeof(trNode));
	if(isTerminal(val)){

		if(val==101){
			temp->lexemeCurrentNode=(char *)malloc(10*sizeof(char));
			strcpy(temp->lexemeCurrentNode,"EPSILON");
			temp->lineno = -999;
			temp->name=(char *)malloc(5*sizeof(char));
			strcpy(temp->name,"----");
			temp->valueIfnumber=-999;
			strcpy(temp->isLeafNode,"No");
			temp->parentNodeSymbol=(char *)malloc((strlen(t->nodeSymbol)+1)*sizeof(char));
			strcpy(temp->parentNodeSymbol,t->nodeSymbol);
			temp->nodeSymbol=(char *)malloc(5*sizeof(char));
			strcpy(temp->nodeSymbol,"----");
			//if(t!=NULL){
			//	cur=t->l;
			//	while(cur!=NULL)
			//	cur=cur->next;
			//	cur=(ptrList)malloc(sizeof(struct list));
			//	cur->next=NULL;
			//	cur->child=temp;
			//}
		}
		else{
			temp->name=(char*)malloc((strlen(tok->name)+1)*sizeof(char));
			temp->nodeSymbol=(char *)malloc(5*sizeof(char));
			temp->lexemeCurrentNode=(char *)malloc((strlen(tok->lexeme)+1)*sizeof(char));
			temp->parentNodeSymbol=(char *)malloc((strlen(t->nodeSymbol)+1)*sizeof(char));
			if(strcmp(tok->name,"NUM")==0)
				temp->valueIfnumber=atoi(tok->lexeme);
			else
				if(strcmp(tok->name,"RNUM")==0)
					temp->valueIfnumber=atof(tok->lexeme);
			strcpy(temp->nodeSymbol,"----");
			strcpy(temp->lexemeCurrentNode,tok->lexeme);
			strcpy(temp->name,tok->name);
			temp->lineno=tok->line;
			strcpy(temp->parentNodeSymbol,t->nodeSymbol);
			strcpy(temp->isLeafNode,"Yes");
			//if(t!=NULL){
			//	cur=t->l;
			//	while(cur!=NULL)
			//	cur=cur->next;
			//	cur=(ptrList)malloc(sizeof(struct list));
			//	cur->next=NULL;
			//	cur->child=temp;
			//}
		}

	}else{
		
		temp->nodeSymbol=ltable[val].lhs;
		temp->lexemeCurrentNode=(char *)malloc(5*sizeof(char));
		//printf("Hello\n");
		strcpy(temp->lexemeCurrentNode,"----");
		temp->lineno = -999;	
		temp->name=(char *)malloc(5*sizeof(char));
		strcpy(temp->name,"----");
		temp->valueIfnumber=-999;
		strcpy(temp->isLeafNode,"No");
		//printf("Hello\n");
		
		if(t==NULL){
			temp->parentNodeSymbol=(char *)malloc(5*sizeof(char));
			strcpy(temp->parentNodeSymbol,"ROOT");
		}
		else{
			temp->parentNodeSymbol=(char *)malloc((strlen(t->nodeSymbol)+1)*sizeof(char));	
			strcpy(temp->parentNodeSymbol,t->nodeSymbol);
		}
		//if(t!=NULL){
		//cur=t->l;
		//while(cur!=NULL)
		//	cur=cur->next;
		//cur=(ptrList)malloc(sizeof(struct list));
		//cur->next=NULL;
		//cur->child=temp;
		//}

	}
return temp;
}

trPtr  parseInputSourceCode(FILE *fptr, int **parseTable,rule* grammar){
		trPtr tree=NULL;
		trPtr prev=tree;
		trPtr cur;
		ptr p;
		stack s;
		ptrList cur1;
		int rnum;
		s=createStack();
		s=push(s,102,tree);
		s=push(s,grammar[1].left,tree);
		tokenInfo ti;
		ti=getNextToken(fptr);
		//printf("%s---%d---%d\n",ti->name,s->head->id,s->head->next->id);
		//tree=addtrNode(tree,55,ti);
		//tree=addtrNode(tree,102,ti);
		//printf("%d---%d\n",s->head->id,s->size);
		while(1){
			//if(isTerminal(s->head->id))
				//t=getNextToken(fptr);
			if(ti->lexeme[0]==EOF){
				if(s->head->id==102)
					{printf(" Compiled Successfully: Input source code is syntactically correct!!\n");return tree;}
			}
			if(isTerminal(s->head->id)){
				//if(s->size==1) 
					//return tree;
				if(strcmp(terminal[(s->head->id)-103],ti->name)==0)
					{ 	
						//printf("???????????\n");
						cur=addtrNode(s->head->p,s->head->id,ti);
						//printf("*************------");
					//if(cur!=NULL)
					//printf("%s----------%s\n",cur->lexemeCurrentNode,s->head->p->nodeSymbol);
					
						//if(s->head->p->l!=NULL)
							//printf("%s PARENT ---	CHILD %s \n",s->head->p->nodeSymbol,s->head->p->l->child->name);
						cur1=s->head->p->l;
						if(cur1==NULL)
						{
							cur1=(ptrList)malloc(sizeof(struct list));
							//cur1->next=NULL;
							cur1->child=cur;
							s->head->p->l=cur1;
							//printf("HELLLO--%s\n",cur1->child->name);
							
						}
						else{
							//printf("Hiiii");
						while(cur1->next!=NULL)
							{cur1=cur1->next;}
						cur1->next=(ptrList)malloc(sizeof(struct list));
						cur1->next->child=cur;
						cur1->next->next=NULL;
						}
					
					s=pop(s);	
					//printf("%s---\n",terminal[(s->head->id)-103]);
					//printf("PARENT---%s\n",s->head->p->nodeSymbol);
					//printf("token%s-    -%s\n",ti->name,cur1->child->name);
					ti=getNextToken(fptr);
					//printf("%s---%d\n",ti->name,s->head->id);
					}
				else{
			//printf("************* %d\n",s->head->id);
			printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s\n",ti->name,ti->lexeme,ti->line,terminal[(s->head->id)-103]);
			return tree;
			}
		}else{

				rnum=parseTable[s->head->id][hash(ti->name)-103];
				//printf("hello\n");
				//printf("-%d----%s------%d-----\n",rnum,ti->name,hash(ti->name));
				if(rnum==0)
				{//printf("END????%d---\n",s->head->id);
				printf("\n\nSYNTAX \nError: No RULE FOUND IN PARSE TABLE-----%s----%s TOKEN---RULE No.-%d----\n",ltable[s->head->id].lhs,(ti->name),rnum); return tree;}	
				cur=addtrNode(s->head->p,s->head->id,ti);
				if(s->head->p!=NULL){
				cur1=s->head->p->l;
				if(cur1==NULL)
						{
							cur1=(ptrList)malloc(sizeof(struct list));
							cur1->child=cur;
							cur1->next=NULL;
							s->head->p->l=cur1;
						}
				else{
						while(cur1->next!=NULL)
							{cur1=cur1->next;}
						cur1->next=(ptrList)malloc(sizeof(struct list));
						cur1->next->child=cur;
						cur1->next->next=NULL;
						}
				}
				if(s->head->p==NULL)
					{tree=cur;}
						//printf("START-%s\n",cur->nodeSymbol);}
				//if(cur!=NULL)
					//printf("%s-----%d-------%d---%d\n",cur->nodeSymbol,rnum,s->head->id,hash(ti->name)-103);
				s=pop(s);
				p=grammar[rnum].right;
				if(p->val!=101){
					while(p!=NULL){
						s=push(s,p->val,cur);
						//printf("RHS????%d---\n",s->head->id);
						p=p->next;
					}
				}else{
					addtrNode(cur,101,ti);
				}
				

			}
			

		}
return tree;
}


void printParseTree(trPtr parseTree,FILE *fp){

	if(parseTree==NULL ||fp==NULL)
		{ printf("empty tree\n");return;}
	fprintf(fp, "\n%s 		%d 			%s 			%d 			%s  		%s  		%s\n",parseTree->lexemeCurrentNode,parseTree->lineno,parseTree->name,parseTree->valueIfnumber,parseTree->parentNodeSymbol,parseTree->isLeafNode,parseTree->nodeSymbol );
	ptrList cur=parseTree->l;
	while(cur!=NULL){
		printParseTree(cur->child,fp);
		cur=cur->next;
	}	
return ;
}

/*
int main(){
	rule *grammar;
	FILE *fp=NULL;
	FILE *fptr=fopen("input.txt","r");
	FILE *out=fopen("output.txt","w");
	fp=fopen("grammar.txt","r");
	trPtr Tree;
	int **pt=newparseTable();
	grammar=createG(fp);
	pt=createParseTable(grammar,pt);
	int i,j=0;
	//for(i=0;i<100;i++)
		//for(j=0;j<102;j++)
			//{ if(pt[i][j]!=0) printf("%d %d %d\n",i,j,pt[i][j]);}
	Tree=parseInputSourceCode(fptr,pt,grammar);
	//if(Tree==NULL)
		//printf("Hello");
		//printf("%s",Tree->parentNodeSymbol);
	//printf("%s",ltable[6].lhs);
	printParseTree(Tree,out);
return 0;
}


*/


