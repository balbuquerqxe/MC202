CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cache

cache: cache.o fila_prioridade.o vetor_tipos.o
	$(CC) $(CFLAGS) cache.o fila_prioridade.o vetor_tipos.o -o cache $(LDFLAGS)

cache.o: cache.c fila_prioridade.h
	$(CC) $(CFLAGS) -c cache.c -o cache.o

vetor_tipos.o: vetor_tipos.c fila_prioridade.h
	$(CC) $(CFLAGS) -c vetor_tipos.c -o vetor_tipos.o

fila_prioridade.o: fila_prioridade.c fila_prioridade.h
	$(CC) $(CFLAGS) -c fila_prioridade.c -o fila_prioridade.o

clean:
	rm -f *.o cache
