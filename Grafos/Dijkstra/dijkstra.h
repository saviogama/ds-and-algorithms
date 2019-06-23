#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

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
int dijkstra(grafo *G, int v0, int vf);

#endif
