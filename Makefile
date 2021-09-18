all: prime_calculate

prime_calculate: prime_calculate.c
	gcc prime_calculate.c -Wall -lm -o prime_calculate
