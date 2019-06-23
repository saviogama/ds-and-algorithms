#include "prim.h"

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
  
int prim(grafo *G, int v, int *vertices) { 
	
	int j, i, total = 0; 

	for(i = 0; i < v; i++) vertices[i] = -1; 
   
	vertices[0] = 0; 

	while(1) {

		int min = MAX;
		int v0, w0;

		for(i = 0; i < v; i++){
			if(vertices[i] == -1) 
				for(j = 0; j < v; j++)
					if(vertices[v] != -1 && min > G->matriz[j][i].peso) 
						min = G->matriz[v0=j][w0=i].peso;
		}

		if(min == MAX) break; 
     
		total += min;
		vertices[w0] = v0;

	}

	return total;
}

