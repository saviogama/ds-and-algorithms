#ifndef _FLOYD_H
#define _FLOYD_H

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
void floyd(grafo *G, int v0, int *dist);
void imprimirFloyd(int *dist, int v);
void calcularFloyd(int *dist, int vf);

#endif
