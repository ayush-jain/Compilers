stage1exe :  driver.c lexer.c parser.c

	gcc -c  lexer.c
	gcc -c  parser.c
	gcc driver.c lexer.o parser.o -o stage1exe	

 
clean:
	rm *.o 