CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cidades

cidades: cidades.o funcoes.o
	$(CC) $(CFLAGS) cidades.o funcoes.o -o cidades $(LDFLAGS)

cidades.o: cidades.c funcoes.h
	$(CC) $(CFLAGS) -c cidades.c -o cidades.o

funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -c funcoes.c -o funcoes.o

clean:
	rm -f *.o cidades