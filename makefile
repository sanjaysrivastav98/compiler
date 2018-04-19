# K S Sanjay Srivastav 
#2015A7PS0102P
compile: lexer.o ast.o driver.o parser.o symbolTable.o
	gcc -g lexer.o ast.o driver.o parser.o symbolTable.o -o stage1exe

symbolTable.o: symbolTable.c
	gcc -c -g symbolTable.c

ast.o: ast.c
	gcc -g -c ast.c

parser.o: parser.c
	gcc -g -c parser.c

lexer.o: lexer.c
	gcc -c -g lexer.c

driver.o: driver.c
	gcc -c -g driver.c

clean: 
	rm stage1exe *.o

