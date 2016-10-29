/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/


#include "parserDef.h"


rule* createG(FILE *fp);// function to store rules in a data structure consisting of rule type structure.

int** newparseTable(); // function to create parseTable and initialize it with 0.

int** createParseTable(rule* grammar, int **parseTable);

trPtr  parseInputSourceCode(FILE *fptr, int **parseTable,rule* grammar);

void printParseTree(trPtr parseTree,FILE *fp);

int isTerminal(int i);

int hash(char *key); // function to hash terminals and non-terminals

ptr add(int key,int tkey,ptr p,ptr r); // function to create a node of E type and return a ptr

void fillFirst(); // function to compute the first set and store it in ltable. It uses helper function first()