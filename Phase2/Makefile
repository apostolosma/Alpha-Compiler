CC=gcc
FLEX=flex
BISON=bison
BFLAGS=--yacc --defines --output=parser.c
CFLAGS=-Wall -pedantic -Werror
FLAGS=--outfile
ONAME=scanner.c
YFILE=syntax.y
EXEC=syntax
LFILE=lex.l
HEADER=lib.h
HASHLIB=hashtable.h
HASH=hashtable.c

calc:  parser.o scanner.o hashtable.o
	$(CC) -g -o $(EXEC) scanner.o parser.o hashtable.o

hashtable.o: $(HASH) $(HASHLIB) $(HEADER)
	$(CC) -c $(HASH)

scanner.o: $ scanner.c $(HEADER) $(HASHLIB)
	$(CC) -c $ scanner.c

parser.o: parser.c $(HASH) $(HASHLIB) $(HEADER)
	$(CC) -c parser.c $(HASH)

parser.c: $(YFILE)
	$(BISON)  $(BFLAGS) $(YFILE)

scanner.c: $(LFILE)
	$(FLEX) $(FLAGS)=$(ONAME) $(LFILE)


clean:
	rm -rf *.o
	rm -rf scanner.c
	rm -rf parser.c
	rm -rf parser.h
	rm -rf $(EXEC)

