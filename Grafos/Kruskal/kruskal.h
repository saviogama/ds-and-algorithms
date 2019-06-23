#ifndef _KRUSKAL_H
#define _KRUSKAL_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 99

typedef struct grafo{

	int numVertice;
	int grauMax;
	int *indice;
	int ponderado;
	int **arestas;
	int **pesos;

}grafo;

typedef struct elemento{

	int v1;
	int v2;

}elemento;

typedef struct conjunto{// estrutura do conjunto da AGM

	elemento lista[MAX];
	int indice;

}conjunto;

typedef struct informacao{

	int vertice;

}informacao;

typedef struct vetorA{// estrutura do vetor que guarda as arestas do grafo em ordem crescente do seu peso

	informacao lista[MAX];
	int indice;

}vetorA;

grafo *inicializar(int numVertice, int grauMax, int ponderado);
void mostraGrafo(grafo *g);
void liberarGrafo(grafo *g);
void inserirAresta(grafo *g, int v1, int v2, int digrafo, float peso);

void ordenaArestas(conjunto *arestas);
int procuraMenor(conjunto *arestas, int limite);
void troca(conjunto *arestas, int p1, int p2);
conjunto kruskal(grafo *g, vetorA *vf, int inicio, int *custo);
void arestaMenor(grafo *g, vetorA *vf);
void inicializarVetorA(vetorA *v);
void inicializarConjunto(conjunto *cj);

#endif
