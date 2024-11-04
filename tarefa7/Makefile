CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

otimizar: otimizar.o criacao_arvore.o simplifica_expressao.o corrige_negacao.o
	gcc $(CFLAGS) otimizar.o criacao_arvore.o simplifica_expressao.o corrige_negacao.o -o otimizar $(LDFLAGS)

otimizar.o: otimizar.c declaracoes_otimizar.h
	gcc $(CFLAGS) -c otimizar.c -o otimizar.o

criacao_arvore.o: criacao_arvore.c declaracoes_otimizar.h
	gcc $(CFLAGS) -c criacao_arvore.c -o criacao_arvore.o

simplifica_expressao.o: simplifica_expressao.c declaracoes_otimizar.h
	gcc $(CFLAGS) -c simplifica_expressao.c -o simplifica_expressao.o

corrige_negacao.o: corrige_negacao.c declaracoes_otimizar.h
	gcc $(CFLAGS) -c corrige_negacao.c -o corrige_negacao.o

clean:
	rm -f *.o otimizar
