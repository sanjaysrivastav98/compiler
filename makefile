# K S Sanjay Srivastav 
#2015A7PS0102P
compile: lexer.o driver.o parser.o
	gcc -g lexer.o driver.o parser.o -o stage1exe

parser.o: parser.c
	gcc -g -c parser.c

lexer.o: lexer.c
	gcc -c -g lexer.c

driver.o: driver.c
	gcc -c -g driver.c

clean: 
	rm stage1exe *.o

