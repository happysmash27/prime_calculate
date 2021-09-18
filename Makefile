all: prime_calculate

prime_calculate: prime_calculate.c
	gcc prime_calculate.c -Wall -o prima_calculate
