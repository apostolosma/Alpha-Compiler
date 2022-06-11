CC=gcc
FLEX=flex
CFLAGS=-Wall -pedantic -Werror
FLAGS=--outfile
ONAME=scanner.c
EXEC=scanner
LFILE=lex.l
MAIN=al.c
HEADER=lib.h


scanner: scanner.o al.o
	$(CC) -g -o $(EXEC) scanner.o al.o


scanner.o: $(MAIN) scanner.c $(HEADER)
	$(CC) -c $(MAIN) scanner.c


scanner.c: $(LFILE)
	$(FLEX) $(FLAGS)=$(ONAME) $(LFILE)

clean:
	rm -rf *.o
	rm -rf scanner.c
	rm -rf $(EXEC)
