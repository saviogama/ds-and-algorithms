#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 9999

typedef struct dados{
	int dado;
}dados;

typedef struct heap{
	dados heap[MAX];
	int indice;
}heap;

void inicializarHeap(heap *h);
void inserirHeap(heap *h, int x);
void organizarHeapMax(heap *h);
void trocar(heap *h, int i1, int i2);
void imprimirHeap(heap *h);
int heapMax(heap *h);
void heapSort(heap *h);
void reorganizarHeap(heap *h, int max);
int maxFilho(heap *h, int max, int pai);

#endif
