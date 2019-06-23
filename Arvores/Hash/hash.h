#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE 11

typedef struct hash{
	
	int dado;
	struct hash *prox;

}hash;

int hashing(int num, int tam);
void inicializarHash(hash *h[]);
void inicializarHash2(hash *h[], int tamanho);
void inserirHash(hash *h[], int num);
void inserirHash2(hash *h[], int num, int tamanho);
void imprimirHash(hash *h[]);
void imprimirHash2(hash *h[], int tamanho);

#endif
