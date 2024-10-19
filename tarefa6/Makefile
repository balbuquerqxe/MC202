CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cobra

cobra: cobra.c cobra_implementacao.c cobra_implementacao.h
	gcc $(CFLAGS) cobra.c cobra_implementacao.c -o cobra $(LDFLAGS)

clean:
	rm -f cobra
