#include "dijkstra.h"

//Inicializa a matriz
grafo* inicializar() {
	
	int i, j;
	grafo *G = (grafo *) malloc(sizeof(grafo));

	for(i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
		        G->matriz[i][j].aresta = 0;
		        G->matriz[i][j].peso = MAX;
		}
	}
	
	return G;

}

//Adiciona arestas a matriz
void inserirAresta(grafo *G, int v1, int v2, int peso) {
	
	G->matriz[v1][v2].aresta = 1;
	G->matriz[v1][v2].peso = peso;
	G->matriz[v2][v1].aresta = 1;
	G->matriz[v2][v1].peso = peso;

}

//Algoritmo principal
int dijkstra(grafo *G, int v0, int vf) {

	int dist[MAX], aux[MAX], i, atual, prox, distaux, novadist;

	for (i = 0; i < MAX; i++) {
		aux[i] = 0;
		dist[i] = MAX;
	}

	//insere v0(vertice inicial) no vetor auxiliar com distancia 0
	aux[v0] = 1;
	dist[v0] = 0;

	//v0 é o vertice inicial para calcular o custo ate o vertice final
	atual = v0;
	prox = atual;

	//enquanto for diferente do vertice final
	while (atual != vf) {

		distaux = MAX;

		for (i = 0; i < MAX; i++) {

			//se o vertice nao esta no vetor auxiliar (se i == 1 esta)
		   	if (aux[i] == 0) {

		   		//distancia do vertice atual ao vertice mais proximo
		   		novadist = dist[atual] + G->matriz[atual][i].peso;

		   		//se a distancia for menor, atualiza o vetor de dist
		   		if (novadist < dist[i]) {
		    		dist[i] = novadist;
		   		}

		   		//determina o vertice com menor distancia
		   		if (dist[i] < distaux) {
		    		distaux = dist[i];
		    		prox = i;
		   		}

			}

		}

		atual = prox;
		aux[atual] = 1;

	}

	return dist[vf];

}

