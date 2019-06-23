#ifndef _PRIM_H
#define _PRIM_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 99

typedef struct aresta {

   	int aresta;
   	int peso;

}aresta;

typedef struct grafo {

   	aresta matriz[MAX][MAX];
	int vertices;

}grafo;

grafo* inicializar();
void inserirAresta(grafo *G, int v1, int v2, int peso);
int prim(grafo *G, int v, int *vertices);

#endif
