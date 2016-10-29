/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h" 
#include "lexer.h"


int main(int argc, char**argv){

	int i;
	rule *grammar;
	FILE *fp;
	FILE *fptr;
	FILE *out;

	printf("FIRST AUTOMATED : FOLLOW NOT AUTOMATED\n");
	printf("EACH MODULE WORKING PROPERLY\n");
	printf("ENTER YOUR OPTION\n");
	scanf("%d",&i);

	if(i==2){
	fptr=fopen(argv[1],"r");
	out=fopen(argv[2],"w");
	fp=fopen("grammar.txt","r");
	trPtr Tree;
	int **pt=newparseTable();
	grammar=createG(fp);
	pt=createParseTable(grammar,pt);

	Tree=parseInputSourceCode(fptr,pt,grammar);

	}
	if(i==1){

		fptr=fopen(argv[1],"r");
		tokenInfo new;
		while(1){
		//i=getFinal();
		//printf("%d-----------%s----------------%d-----------\n",curLine,curStr,i);
		//if(i==INVALID)
		//	break;
		//getToken(i);
		new=getNextToken(fptr);
		if(new->lexeme[0]==EOF)
			break;
		printf("\nLEXEME IS %s  TOKEN IS %s  LINENO-%d TOKEnNO-%d  LENGTH-%d\n",new->lexeme,new->name,new->line,new->tokenNo,new->length);
		}
	}

	if(i==3){

		fptr=fopen(argv[1],"r");
		out=fopen(argv[2],"w");
		fp=fopen("grammar.txt","r");
		trPtr Tree;
		int **pt=newparseTable();
		grammar=createG(fp);
		pt=createParseTable(grammar,pt);

		Tree=parseInputSourceCode(fptr,pt,grammar);
		printParseTree(Tree,out);
		printf("CHECK YOUR OUTPUT FILE FOR PARSE TREE\n");
		printf("-999 lineno for NON TERMINAL NODE\n");
		printf("---- for lexemeCurrentNode for NON TERMINAL NODE\n");
		printf("---- for tokenName for NON TERMINAL NODE\n");
		printf("---- for NodeSymbol for NON TERMINAL NODE\n");


	}
	



return 0;
}