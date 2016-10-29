/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/

/* Global parameters used for tokenizing*/

static char temp[1000] = "";
static int curLine= 1;
static char curStr[22] = "";
static int len=0;
static char curTok[22] = "";
static int curState=0;
static int curPos=0;
static int count=0;
static FILE *fptr;

typedef int bufferSize;
typedef char* buffer;

/* Datastructure tk for holding token information*/

typedef struct {
		char *name;
		char *lexeme;
		int line;
		int tokenNo;
		int length;			

}tk;

typedef tk *tokenInfo;


