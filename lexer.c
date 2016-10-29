/*BATCH NO 14
AYUSH JAIN  2011A7PS066P
ARADHYA SAXENA 2011C6PS599P
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define INVALID -999
#define END -1
void getStream(FILE *fp, buffer B, bufferSize k){
	//memset(B,'\0',sizeof(B));
	int last=0;
	int i=0;
	//if(feof(fp)){
		//B[i++]='?';
	//	return ;
	//}
	char c=' ';
	if(fp==NULL)
	{
		printf("Error : File not Found");
		exit(0);	
	}

	while(i<k-1){

			c=fgetc(fp);
			if(c=='#'){
				while(1){
					c=fgetc(fp);
					if(c=='\n')
						{ B[i++]=c; c=fgetc(fp); break;}
				}
			}
			B[i++]=c;
			if(feof(fp)){
				//last=1;
				break;
			}	
	}
	//if(last && i<k-1)
		//B[i++]='?';
	B[i++]='\0';

return ;
}


char* getToken(int final){
	char *val=(char *)malloc(22*sizeof(char));
	switch(final){
		case 197:
			strcpy(val,"ID");
			break;
		case 200:
			strcpy(val,"SIZE");
			break;
		case 201:
			strcpy(val,"SQO");
			break;
		case 202:
			strcpy(val,"SQC");
			break;
		case 203:
			strcpy(val,"OP");
			break;
		case 204:
			strcpy(val,"CL");
			break;
		case 205:
			strcpy(val,"SEMICOLON");
			break;
		case 206:
			strcpy(val,"COMMA");
			break;
		case 207:
			strcpy(val,"PLUS");
			break;
		case 208:
			strcpy(val,"MINUS");
			break;
		case 209:
			strcpy(val,"MUL");
			break;
		case 210:
			strcpy(val,"DIV");
			break;
		case 215:
			strcpy(val,"FUNCTION");
			break;
		case 216:
			strcpy(val,"END");
			break;
		case 217:
			strcpy(val,"MATRIX");
			break;
		case 218:
			strcpy(val,"STRING");
			break;
		case 219:
			strcpy(val,"REAL");
			break;
		case 220:
			strcpy(val,"READ");
			break;
		case 221:
			strcpy(val,"ENDIF");
			break;
		case 222:
			strcpy(val,"ELSE");
			break;
		case 223:
			strcpy(val,"INT");
			break;
		case 224:
			strcpy(val,"IF");
			break;
		case 225:
			strcpy(val,"PRINT");
			break;
		case 226:
			strcpy(val,"STR");
			break;
		case 227:
			strcpy(val,"NUM");
			break;
		case 228:
			strcpy(val,"RNUM");
			break;
		case 229:
			strcpy(val,"FUNID");
			break;
		case 230:
			strcpy(val,"MAIN");
			break;
		case 231:
			strcpy(val,"NE");
			break;
		case 232:
			strcpy(val,"EQ");
			break;
		case 233:
			strcpy(val,"ASSIGNOP");
			break;
		case 234:
			strcpy(val,"LE");
			break;
		case 235:
			strcpy(val,"LT");
			break;
		case 236:
			strcpy(val,"GE");
			break;
		case 237:
			strcpy(val,"GT");
			break;
		case 238:
			strcpy(val,"AND");
			break;
		case 239:
			strcpy(val,"OR");
			break;
		case 240:
			strcpy(val,"NOT");
			break;
		case -999:
			strcpy(val,"ERROR");
			break;	
		default:
			break;											
																																																 

	}


return val;
}


char getChar(FILE *fp){
	char c;
	if(strcmp(temp,"")==0){
		//fptr=fopen("input.txt","r");
		getStream(fp,temp,1000);
		curPos=0;
	}
	if(curPos==1000){
		getStream(fp,temp,1000);
		curPos=0;
	}
	c=temp[curPos++];
	return c;
}


/*


int main(){


	fptr=fopen("input.txt","r");
	buffer buf;
	bufferSize size=50;
	
	buf=(char *)malloc(size *sizeof(char));	
	getStream(fptr,buf,size);
	while(strlen(buf)==49){
	printf("%s",buf);
	free(buf);
	buf=(char *)malloc(size *sizeof(char));	
	getStream(fptr,buf,size);}
	//printf("\nHello\n");
	//printf("---%s----%c%d\n",buf,strlen(buf));
	return 0;
		
}
*/

int isDigit(char c){

	if(c>='0' && c<='9')
		return 1;
	else
		return 0;

}


int isUpperAlpha(char c){
	if(c>='A' && c<='Z')
		return 1;
	else
		return 0;

}

int isLowerAlpha(char c){
	if(c>='a' && c<='z')
		return 1;
	else
		return 0;

}

int isDigitOrAlpha(char c){

	if((c>='a' && c<='z') || (c>='A' && c<='Z')|| (c>='0'&& c<='9'))
		return 1;
	else
		return 0;
}

int isError(char c,FILE *fp){
	int i=0;
	tokenInfo t;
	if(c=='%'){
		printf("----------------------ERROR_3: UNKNOWN PATTERN :CORRECT PATTERN SHOULD BE %s\n",curStr);
		c=getChar(fp);
		printf("TOKENS AFTER 1st ERROR DETECTED\n");
		while(i!=END && c!=EOF){
			i=getFinal(fp);
			tokenInfo t;
			if(i==INVALID)
				break;
		char *temp=getToken(i);	
		t=(tokenInfo)malloc(sizeof(tk));
		char *lex =(char *)malloc((len+1)*sizeof(char));
		char *n = (char *)malloc((strlen(temp)+1)*sizeof(char));
		strcpy(lex,curStr);
		strcpy(n,temp);
		t->lexeme=lex;
		t->name =n;
		t->length=strlen(curStr);
		t->line=curLine;
		t->tokenNo=++count;
		if(i!=END && c!=EOF)
		printf("--%s--%s---%d---%d----%d\n",t->lexeme,t->name,t->line,t->tokenNo,t->length);
		free(t);	
		}
		return 1;
	}


	if(len>=21){
		printf("----------------------ERROR_1:LENGTH OF IDENTIFIER  %s > 20------------------------------------\n",curStr);
		c=getChar(fp);
		curState=0;
		memset(curStr,'\0',sizeof(curStr));
		len=0;
		//while(i!=END)
				//i=getFinal(fp);
		return 1;
	}

	if((isDigitOrAlpha(c))|| c==EOF||c==','|| c==';'||c=='_' || c ==' '|| c=='\n' || c=='*'||c=='/'|| c=='+'|| c=='-' || c=='@'||c=='['||c==']'||c=='('|| c==')'||c=='.'|| c=='"'||c=='#'|| c=='='||c=='>'||c=='<'||c=='=' || c=='\t'){
		return 0;
	}
	else{
		if(c==EOF)
			return 0;
		//printf("hello--%c--- \n",c);
		printf("ERROR_2:INVALID SYMBOL----%s--------\n",curStr);
		c=getChar(fp);
		//c=getChar(fp);
		//while(i!=END)
		//	{//printf("%c--",c);
		//	i=getFinal(fp);}
		return 1;
	}
	
return 0;

}

void retract(){
	curPos--;
	if(!isDigit(curStr[len-1]))
	len--;
	curStr[len]='\0';
}


int getFinal(FILE *fp){
	int c=' ';
	curState=0;
	memset(curStr,'\0',sizeof(curStr));
	len=0;
	while(1){

		switch(curState){

		case 0:
			c=getChar(fp);
			//printf("A==%c==A",c);
			if(c==' '){
				curState=0;
				break;
			}
			if(c=='\t'){
				curState=0;
				break;
			}
			if(c=='\n'){
				curLine++;
				curState=0;
				break;
			}
			if(c==EOF){
				curStr[len++]=c;
				return END;
			}

			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;

			if(isLowerAlpha(c) && c!='m' && c!='s' && c!='r' && c!='e' && c!='p' && c!='i' && c!='f'){
				curState=1;
				break;	
			}

			if(c=='f'){
				curState=125;
				break;
			}
			if(c=='r'){
				curState=27;
				break;
			}	
			if(c=='s'){
				curState=87;
				break;	
			}
			if(c=='m'){
				curState=82;
				break;
			}
			if(c=='e'){
				curState=4;
				break;
			}
			if(c=='i'){
				curState=16;
				break;
			}	
			if(c=='p'){
				curState=28;
				break;
			}
			if(c=='_'){
				curState=95;
				break;
			}
			if(c=='"'){
				curState=108;
				break;
			}
			if(isDigit(c)){
				curState=104;
				break;	
			}
			if(c=='['){
				return 201;
			}	
				
			if(c==']'){
				return 202;
			}
			if(c=='('){
				return 203;
			}
			if(c==')'){
				return 204;
			}
			if(c==';'){
				return 205;
			}
			if(c==','){
				return 206;
			}
			if(c=='+'){
				return 207; 
			}
			if(c=='-'){
				return 208;
			}
			if(c=='*'){
				return 209;
			}
			if(c=='/'){
				return 210;
			}
			if(c=='.'){
				curState =113;
				break;
			}
			if(c=='>'){
				curState =111;
				break;
			}
			if(c=='<'){
				curState = 110;
				break;
			}
			if(c=='='){
				curState=112;
				break;
			}
			if(c=='@'){
				return 200;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}	

		case 125:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='u'){
				curState=126;
				break;
			}
			if((isLowerAlpha(c) && c!='u') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}		
		case 126:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='n'){
				curState=127;
				break;
			}
			if((isLowerAlpha(c) && c!='n') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 127:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='c'){
				curState=128;
				break;
			}
			if((isLowerAlpha(c) && c!='c') || isUpperAlpha(c)){
				curState=128;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 128:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='t'){
				curState=129;
				break;
			}
			if((isLowerAlpha(c) && c!='t') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 129:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='i'){
				curState=130;
				break;
			}
			if((isLowerAlpha(c) && c!='i') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 130:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='o'){
				curState=131;
				break;
			}
			if((isLowerAlpha(c) && c!='o') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}
		case 131:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='n'){
				curState=132;
				break;
			}
			if((isLowerAlpha(c) && c!='n') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}
		case 132:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
		
			if((isLowerAlpha(c)) || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 215;
			}						

		case 82:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if((isLowerAlpha(c) && c!='a') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			if(c=='a'){
				curState=83;
				break;
			}
			else{
				retract();
				return 197;
			}		

		case 83:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='t'){
				curState=84;
				break;
			}
			if((isLowerAlpha(c) && c!='t') || isUpperAlpha(c)){
				curState=1;
				break;	
			}

			else{
				retract();
				return 197;
			}

		case 84:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='r'){
				curState=85;
				break;
			}	
			if((isLowerAlpha(c) && c!='r' )&& isUpperAlpha(c)){

				curState=1;
				return 197;
			}
			else{

				retract();
				return 197;
			}

		case 85:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='i'){
				curState=86;
				break;
			}	
			if((isLowerAlpha(c) && c!='i') && isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 86:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='x'){

				curState=93;
				break;
			}
			if((isLowerAlpha(c) && c!='x')){

				curState=1;
				break;
			}	
			else{

				retract();
				return 197;
			}

		
		case 93:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(isLowerAlpha(c)|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 217;
			}	

		case 87:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='t'){
				curState=88;
				break;
			}
			if((isLowerAlpha(c)&& c!='t')|| isUpperAlpha(c)){

				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}


		case 88:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
			}
			if(c=='r'){
				curState=89;
				break;
			}
			if((isLowerAlpha(c)&& c!='r')|| isUpperAlpha(c)){

				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}	
		
		case 89:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='i'){
				curState=90;
				break;
			}
			if((isLowerAlpha(c)&& c!='i')|| isUpperAlpha(c)){

				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}	

		case 90:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='n'){
				curState=91;
				break;
			}
			if((isLowerAlpha(c)&& c!='n') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}	
		
		case 91:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='g'){
				curState=92;
				break;
			}
			if((isLowerAlpha(c)&& c!='g') && isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 92:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isLowerAlpha(c)|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 218;
			}

		case 27:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='e'){
				curState=42;
				break;
			}
			if((isLowerAlpha(c) && c!='e') && isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			} 	 

		case 42:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='a'){
				curState=43;
				break;
			}
			if((isLowerAlpha(c)&& c!='a')&& isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 43:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='l'){
				curState=45;
				break;
			}
			if(c=='d'){
				curState=44;
				break;
			}
			if((isLowerAlpha(c)&& c!='l' && c!='d')|| isUpperAlpha(c)){
				curState=1;
				break;
			}		
			else{
				retract();
				return 197;
			}
		
		case 44:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isUpperAlpha(c)||isLowerAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 220;
			}

		case 45:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isUpperAlpha(c)|| isLowerAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 219;
			}

		case 1:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isLowerAlpha(c)||isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}			
		
		case 4:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='l'){
				curState=46;
				break;
			}
			if(c=='n'){
				curState=5;
				break;
			}

			if((isLowerAlpha(c)&& c!='n'&& c!='l') && isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 5:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='d'){
				curState=6;
				break;
			}
			if((isLowerAlpha(c)&& c!='d')&& isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 6:	
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='i'){
				curState=122;
				break;	
			}
			if((isLowerAlpha(c)&& c!='i')&& isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 216;
			}

		case 122:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c))	{
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='f'){
				curState=123;
				break;
			}
			if((isLowerAlpha(c)&& c!='f') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 123:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isLowerAlpha(c)|| isUpperAlpha(c)){
				curState=1;
				break;
			}	

			else{
				retract();
				return 221;
			}

		case 46:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='s'){
				curState=47;
				break;
			}	
			if((isLowerAlpha(c)&& c!='s')&& isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 47:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='e'){
				curState=48;
				break;
			}
			if((isLowerAlpha(c)&& c!='e')|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 48:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isUpperAlpha(c)||isLowerAlpha(c)){
				curState=1;
				break;

			}
			else{
				retract();
				return 222;
			}

		case 16:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='n'){
				curState=17;
				break;
			}
			if(c=='f'){
				curState=25;
				break;
			}
			if((isLowerAlpha(c)&& c!='n' && c!='f') || isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 17:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='t'){
				curState=18;
				break;
			} 
			if((isLowerAlpha(c)&& c!='t')|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 18:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}

			if(isLowerAlpha(c)|| isUpperAlpha(c)){
				curState=1;
				break;

			}
			else{
				retract();
				return 223;
			}

		case 25:				
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(isLowerAlpha(c)|| isUpperAlpha(c)){
				curState=1;
				break;

			}
			else{
				retract();
				return 224;
			}

		case 28:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='r'){
				curState=29;
				break;
			}
			if((isLowerAlpha(c) && c!='r')|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}

		case 29:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='i'){
				curState=30;
				break;
			}
			if((isLowerAlpha(c)&& c!='i')|| isUpperAlpha(c)){
				curState=1;
				break;	
			}
			else{
				retract();
				return 197;
			}

		case 30:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='n'){
				curState=31;
				break;	
			}
			if((isLowerAlpha(c)&& c!='n')|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;
			}		

		case 31:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if(c=='t'){
				curState=32;
				break;
			}
			if((isLowerAlpha(c)&& c!='t')|| isUpperAlpha(c)){
				curState=1;
				break;
			}
			else{
				retract();
				return 197;

			}	
		
		case 32:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 197;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

			}
			if((isLowerAlpha(c)|| isUpperAlpha(c))){
				curState=1;
				break;
			}
			else{
				retract();
				return 225;
			}

		case 108:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isLowerAlpha(c) || c==' '){
				curState=109;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))	
					return INVALID;
			}

		case 109:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='"'){
				return 226;
			}
			if(isLowerAlpha(c) || c==' '){
				curState=109;
				break;
			}

			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
					return INVALID;
			}

		case 104:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				curState=104;
				break;
			}
			if(c=='.'){
				curState=105;
				break;
			}
			else{
				
				if((!isDigitOrAlpha(c))|| c==',' || c==';' || c=='\n' || c==' '){
				retract();	
				return 227;
				}else{
					if(isError('%',fp));
						return INVALID;
				}

				//retract();
				//return 228;	
			}

		case 105:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				curState=106;
				break;
			}
			else{
			printf("Invalid Pattern\n");
			if(isError('%',fp))	
				return INVALID;	
			}	
		
		case 106:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(isDigit(c)){
				c=getChar(fp);
				if(!isDigitOrAlpha(c)){
				retract();	
				return 228;
				}else{
					if(isError('%',fp));
						return INVALID;
				}
	
			}
			else{
			printf("Invalid Pattern\n");
			if(isError('%',fp))	
				return INVALID;	
			}

		case 95:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='m'){
				curState=96;
				break;
			}
			if((isLowerAlpha(c)&& c!='m')|| isUpperAlpha(c)|| isDigit(c)){
				curState=100;
					break;
			} 
			else{
			printf("Invalid Pattern\n");
			if(isError('%',fp))
				return INVALID;	
			} 				

		case 96:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='a'){
				curState=97;
				break;
			}
			if((isLowerAlpha(c)&& c!='a')|| isUpperAlpha(c)|| isDigit(c)){
				curState=100;
				break;
			} 
			else{
				retract();
				return 229;	
			}

		case 97:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='i'){
				curState=98;
				break;
			}
			if((isLowerAlpha(c)&& c!='i')|| isUpperAlpha(c) || isDigit(c)){
				curState=100;
				break;
			} 
			else{
				retract();
				return 229;	
			}

		case 98:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='n'){
				curState=99;
				break;
			}
			if((isLowerAlpha(c)&& c!='n')|| isUpperAlpha(c) || isDigit(c)){
				curState=100;
				break;
			} 
			else{
				retract();
				return 229;	
			}

		case 99:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			
			if(isLowerAlpha(c)|| isUpperAlpha(c)|| isDigit(c)){
				curState=100;
				break;
			} 
			else{
				retract();
				return 230;	
			}

		case 100:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			
			if((isLowerAlpha(c))|| isUpperAlpha(c)|| isDigit(c)){
				curState=100;
				break;
			} 
			else{
				retract();
				return 229;	
			}				

		case 112:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='/'){
				curState=124;
				break;
			}
			if(c=='='){
				return 232;
			}
			else{
				if(isDigit(c))
					curStr[len-1]='a';
				retract();
				return 233;
			}

		case 124:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='='){
				return 231;
			}		
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
					return INVALID;
			}

		case 110:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='='){
				return 234;
			}
			else{
				if(isDigit(c))
					curStr[len-1]='a';
				retract();
				return 235;
			}

		case 111:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='='){
				return 236;				
			}
			else{
				if(isDigit(c))
					curStr[len-1]='a';
				retract();
				return 237;
			}		

		case 113:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='a'){
				curState=114;
				break;
			}
			if(c=='o'){
				curState=117;
				break;
			}
			if(c=='n'){
				curState=119;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
					return INVALID;	
			}		
		case 114:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='n'){
				curState=115;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
					return INVALID;
			}

		case 115:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='d'){
				curState=116;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}				

		case 117:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='r'){
				curState=118;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}
		case 118:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='.'){
				return 239;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}		
		
		case 116:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='.'){
			
				return 238;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}

		case 119:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='o'){
				curState=120;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}

		case 120:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='t'){
				curState=121;
				break;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}

		case 121:
			c=getChar(fp);
			curStr[len++]=c;
			if(isError(c,fp))
				return INVALID;
			if(c=='.'){
				return 240;
			}
			else{
				printf("Invalid Pattern\n");
				if(isError('%',fp))
				return INVALID;
			}

		
		}	

	}
		
		
}
		

	





tokenInfo  getNextToken(FILE *fp){

	tokenInfo t;
	char *temp=getToken(getFinal(fp));	
	t=(tokenInfo)malloc(sizeof(tk));
	char *lex =(char *)malloc((len+1)*sizeof(char));
	char *n = (char *)malloc((strlen(temp)+1)*sizeof(char));
	strcpy(lex,curStr);
	strcpy(n,temp);
	t->lexeme=lex;
	t->name =n;
	t->length=strlen(curStr);
	t->line=curLine;
	t->tokenNo=++count;

	return t;
}

/*

void proTok(){



	fptr=getStream(fptr,temp,1024);
	int j=0;
	while(j++<5){
	i=getFinal();
	printf("----------------%d-----------\n",i);
	if(i==INVALID)
		break;
	//getToken();
	//getNextToken(fptr);
	
	}
	
	return ;

}
*/
/*

int main(){
	int i=0;
	fptr=fopen("input.txt","r");
	//buffer buf;
	//bufferSize size=1000;
	//buf=(char *)malloc(size *sizeof(char));	
	//getStream(fptr,temp,size);
	//printf("%s\n\n",temp);
	//int j=0;
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
	printf("--%s--%s---%d---%d----%d\n",new->lexeme,new->name,new->line,new->tokenNo,new->length);
	}
return 0;	
}
*/