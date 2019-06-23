#include "floyd.h"

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
void floyd(grafo *G, int v0, int *dist){
	
	int k, i, j, vertices;
	vertices = G->vertices + 1;

	for(k = 0; k < vertices; k++){
		
		for(i = 0; i < vertices; i++){
			
			for(j = 0; j < vertices; j++){
					
				if(G->matriz[i][j].peso > G->matriz[i][k].peso + G->matriz[k][j].peso)
					//Atualiza o vertice intermediario tendo k como novo vertice
				  	G->matriz[i][j].peso = G->matriz[i][k].peso + G->matriz[k][j].peso;

			}
		}
	}

	//As linhas de baixo sao so para facilitar minha impressao do resultado
	k = 0, j = 1;

	//Armazenando em um vetor
	while(j < vertices){
		if(k == (v0-1)){
			dist[k] = 0;
			k++;
			j++;
		}
		else{
			dist[k] = G->matriz[v0][j].peso;
			k++;
			j++;
		}
	}

}

//Funcao auxiliar para imprimir o resultado do algoritmo passando vertice inicial
void imprimirFloyd(int *dist, int v){
	
	int i = 0, j = 1;
	
	while(i < v){
		printf("%d:%d   ", j, dist[i]);
		i++;
		j++;
	}

}

//Funcao auxiliar para imprimir a distancia minima de um vertice a outro
void calcularFloyd(int *dist, int vf){
	
	printf("%d", dist[vf-1]);

}

