#include "kruskal.h"

//Inicializa um grafo
grafo *inicializar(int numVertice, int grauMax, int ponderado){

	grafo *g = (grafo *) malloc(sizeof(grafo));

	g->numVertice = numVertice;
	g->grauMax = grauMax;
	g->ponderado = ponderado;

	g->indice = (int *)malloc(numVertice * sizeof(int));

	g->arestas = (int **)malloc(g->numVertice * sizeof(int *));
	for(int i = 0; i<numVertice; i++){
		g->arestas[i] = (int *)malloc(g->grauMax * sizeof(int));
	}

	for(int i = 0; i<g->numVertice; i++){
		for(int j = 0; j<g->grauMax; j++){
			g->arestas[i][j] = -1;
		}
	}

	if(g->ponderado > 0){
		g->pesos = (int **)malloc(g->numVertice * sizeof(int *));
		for(int i = 0; i<numVertice; i++){
			g->pesos[i] = (int *)malloc(g->grauMax * sizeof(int));
		}
	}
	for(int i = 0; i<g->numVertice; i++){
		for(int j = 0; j<g->grauMax; j++){
			g->pesos[i][j] = 1;
		}
	}
	
	return g;
}

//Imprime um grafo
void mostraGrafo(grafo *g){
	for(int i = 0;i<g->numVertice;i++){
		printf("%d-> ", i);
		for(int j = 0; j<g->grauMax;j++){
			if(g->arestas[i][j] > -1){
				printf("%d ", g->arestas[i][j]);
			}
		}
		printf("\n");
	}
}

//Insere as arestas
void inserirAresta(grafo *g, int v1, int v2, int digrafo, float peso){

	if(g == NULL)return ;
	if(v1 < 0 || v1 >= g->numVertice)return ;
	if(v2 < 0 || v2 >= g->numVertice)return ;

	g->arestas[v1][g->indice[v1]] = v2;

	if(g->ponderado > 0){
		g->pesos[v1][g->indice[v1]] = peso;
	}
	g->indice[v1]++;

	if(digrafo == 0){
		inserirAresta(g, v2, v1, 1, peso);
	}

}

//Iniciaaliza o conjunto de arestas
void inicializarConjunto(conjunto *cj){
	cj->indice = 0;
}

//Inicializa o vetor de vertices das arestas de menor peso do grafo
void inicializarVetorA(vetorA *v){
	v->indice = 0;
}

//Ordena todas as arestas do grafo por ordem crescente
void arestaMenor(grafo *g, vetorA *vf){
	int v1, v2;
	int k = 0;
	float menor;
	grafo *g2;

	inicializarVetorA(vf);

	g2 = inicializar(g->numVertice, g->grauMax, 1);

	for(int i = 0; i<g2->numVertice; i++){
		for(int j = 0; j<g->indice[i]; j++){
			g2->pesos[i][j] = g->pesos[i][j];
		}
	}

	
	while(k < g->numVertice*g->grauMax){

		v1 = 0;
		v2 = 0;
		menor = g2->pesos[0][0];

		for(int i = 0; i<g2->numVertice; i++){
			for(int j = 0; j < g->indice[i]; j++){
				if(g2->pesos[i][j] < menor){
					menor = g2->pesos[i][j];
					v1 = i;
					v2 = j;

				}
			}
		}
		if(g2->pesos[v1][v2] != MAX){
			vf->lista[vf->indice].vertice = v1;
			vf->indice++;
			vf->lista[vf->indice].vertice = v2;
			vf->indice++;

			g2->pesos[v1][v2] = MAX;

			for(int i = g->arestas[v1][v2]; i==g->arestas[v1][v2]; i++){
				for(int j = 0; j<g2->indice[i]; j++){
					if(g->arestas[i][j] == v1){
						g2->pesos[i][j] = MAX;
						break;
					}
				}
			}
		}else{
			break;
		}

		k++;
	}

}

//Algoritmo de Kruskal retorna um conjunto de arestas
conjunto kruskal(grafo *g, vetorA *vf, int inicio, int *custo){
	 custo[0] = 0;
	int pai[g->numVertice];
	int arvore[g->numVertice];
	conjunto saida;
	int i, j;

	for(int i = 0; i<g->numVertice; i++){
		pai[i] = -1;
		arvore[i] = i;
	}

	pai[0] = inicio;
	inicializarConjunto(&saida);

	for( i = 0, j = 1; i<vf->indice || j<vf->indice; i=i+2, j=j+2){
		if(arvore[vf->lista[i].vertice] != arvore[ g->arestas[ vf->lista[i].vertice ][ vf->lista[j].vertice ] ] 
		&& pai[g->arestas[ vf->lista[i].vertice ][ vf->lista[j].vertice ]] == -1){

			custo[0] += g->pesos[vf->lista[i].vertice] [vf->lista[j].vertice];
			saida.lista[saida.indice].v1 = vf->lista[i].vertice;
			saida.lista[ saida.indice ].v2 = g->arestas[ vf->lista[i].vertice ][ vf->lista[j].vertice ];
			saida.indice++;
			pai[g->arestas[ vf->lista[i].vertice ][ vf->lista[j].vertice ]] = 1;

			for(int i2 = 0; i2<g->numVertice; i2++){
				if(arvore[i2] == g->arestas[vf->lista[i].vertice][vf->lista[j].vertice]){
					arvore[i2] = arvore[vf->lista[i].vertice];
				}
			}
		}
	}

	return saida;
}

//Ordena em ordem crescente o conjunto de arestas
void ordenaArestas(conjunto *arestas){
	int menor;

	for(int i = 0; i<arestas->indice; i++){
		menor = procuraMenor(arestas, i);
		troca(arestas, i, menor);
	}
}

//Procura e retorna o indice da menor aresta do conjunto de arestas
int procuraMenor(conjunto *arestas, int limite){
	int menorIndice;
	int menorV1, menorV2;

	menorIndice = limite;
	menorV1 = arestas->lista[limite].v1;
	menorV2 = arestas->lista[limite].v2;


	for(int j = limite+1; j<arestas->indice; j++){
		if(arestas->lista[j].v1 < menorV1){
			menorV1 = arestas->lista[j].v1;
			menorV2 = arestas->lista[j].v2;
			menorIndice = j;
		}
		if(arestas->lista[j].v1 == menorV1){
			if(arestas->lista[j].v2 < menorV2){
				menorV1 = arestas->lista[j].v1;
				menorV2 = arestas->lista[j].v2;
				menorIndice = j;
			}
		}
	}

	return menorIndice;
}

//Troca a posição de dois elementos, auxilia na ordenação do conjunto de arestas
void troca(conjunto *arestas, int p1, int p2){
	int tempv1;
	int tempv2;

	tempv1 = arestas->lista[p2].v1;
	tempv2 = arestas->lista[p2].v2;

	if(p1 == p2) return;

	arestas->lista[p2].v1 = arestas->lista[p1].v1;
	arestas->lista[p2].v2 = arestas->lista[p1].v2;

	arestas->lista[p1].v1 = tempv1;
	arestas->lista[p1].v2 = tempv2;
}
