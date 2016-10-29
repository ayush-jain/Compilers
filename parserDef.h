/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/

/*


ltable is a dataStructure holding information about first and follow set for each non terminal. 
It is used while computing first set

rtable is a dataStructure holding information about position of a non-terminal on righthandside in a rule.

 trNode is a node for parseTree.

stack is also used for parsing



*/


struct row;
typedef struct row ROW;
typedef ROW *ptrRow;

struct list;
typedef struct list *ptrList;
struct tNode;
typedef struct tNode trNode;
typedef trNode *trPtr;
struct list{

	trPtr child;
	ptrList next;

};

struct elem ;
typedef struct elem *ptr;

typedef struct elem{
	int val;
	ptr next;
	ptr prev;
} E; 


typedef struct{
	char isEmpty;
	char* lhs;
	ptr first;
	ptr follow;
	ptr rhs[10];
	ptr rrhs[10];
	int count;
} nonTerminal,*nTptr;


typedef struct {

	int left;
	ptr right;
	ptr rright;
}rule;
typedef struct{

	ptr arg[10];
	int arglhs[10];
	int count;
}rhsTable;

struct tNode{

	char *lexemeCurrentNode;
	int lineno;
	char *name;
	int valueIfnumber;
	char *parentNodeSymbol;
	char isLeafNode[3];
	char *nodeSymbol;
	ptrList l;
	trPtr parent;
	ptrRow sptr;
};


struct node;
typedef struct node NODE;
typedef NODE *ndPtr;

struct node{

	int id;
	ndPtr next;
	trPtr p;

};
typedef struct{

	ndPtr head;
	int size;
}st;
typedef st *stack;


int check[100];
static nonTerminal ltable[100];
static rhsTable rtable[100];
static char *terminal[100];
//----------------------------------------------------------------------------------




struct row{
	char *idname;
	char *scope;
	char *type;
	int offset;
	int lineno;
	trPtr p;
	int isEmpty;
};

struct ue;
typedef struct ue uElem;
typedef uElem *uElemptr;
struct ue{
	char *type;
	char *id;
	uElemptr next;
};



struct tb;
typedef struct tb table;
typedef table *tbPtr;
struct tb{
	char *idname;
	int stno;
	int endno;
	char *scope;
	uElemptr parameterlist; 
	uElemptr returnlist;
	ROW t[100];
	trPtr p;
};

tbPtr symtb[100];
int offset;
typedef struct mI{
	char *id;
	int size1;
	int size2;
}matrixInfo;
typedef matrixInfo *infoPtr;
static infoPtr matrixTable[100];

trPtr traverse(trPtr t);
trPtr buildParseTree(trPtr pT);
void printAst(trPtr t);

