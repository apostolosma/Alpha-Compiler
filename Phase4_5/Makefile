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

load: avm.c avm.h
	$(CC) -g -o load avm.c -lm

syntax: parser.c scanner.c hashtable.c stack.c target.c
	$(CC) -g -o $(EXEC) scanner.c hashtable.c stack.c target.c parser.c 


# hashtable.o: $(HASH) $(HASHLIB) $(HEADER)
# 	$(CC) -c $(HASH)

# target.o: target.c target.h
# 	$(CC) -c target.c

# stack.o: stack.c stack.h
# 	$(CC) -c stack.c

# scanner.o: $ scanner.c $(HEADER) $(HASHLIB)
# 	$(CC) -c $ scanner.c

# parser.o: parser.c $(HASH) $(HASHLIB) $(HEADER)
# 	$(CC) -c parser.c $(HASH)


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
	rm -rf load
