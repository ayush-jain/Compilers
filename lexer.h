/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/



#include "lexerDef.h"
 

void getStream(FILE *fp, buffer B, bufferSize k);

char* getToken(int final);

char getChar(FILE *fp);

int isDigit(char c);

int isUpperAlpha(char c);

int isLowerAlpha(char c);

int isDigitOrAlpha(char c);

int isError(char c,FILE *fp);

void retract();// move one position backward while reading the input source code

int getFinal(FILE *fp);// This function gives the final destination state no.

tokenInfo  getNextToken(FILE *fp); // gives the token along with details like lineno,lexeme etc.