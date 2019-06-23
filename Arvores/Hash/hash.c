#include "hash.h"

//Funcao principal hash que auxilia na insercao do elemento
int hashing(int num, int tam){
	float x = 0.56968401423;
	float v = num * x;
	v = v - (int) v;
	return (int) (tam * v);
}

//Funcao que aloca espaco e inicializa a hash com tamanho padrao 11
void inicializarHash(hash *h[]){

	int i;
	for(i = 0; i < SIZE; i++){
		h[i] = NULL;
	}
}

//Funcao que aloca espaco e inicializa a hash com tamanho definido pelo usuario
void inicializarHash2(hash *h[], int tamanho){

	int i;
	for(i = 0; i < tamanho; i++){
		h[i] = NULL;
	}
}

//Funcao de insercao da hash
void inserirHash(hash *h[], int num){
	
	int pos;
	pos = hashing(num, SIZE);

	hash* novo;
	novo = (hash*) malloc(sizeof(hash));
	novo->dado = num;

	novo->prox = h[pos];
	h[pos] = novo;
	
}

//Funcao de insercao da hash com tamanho definido pelo usuario
void inserirHash2(hash *h[], int num, int tamanho){
	
	int pos;
	pos = hashing(num, tamanho);

	hash* novo;
	novo = (hash*) malloc(sizeof(hash));
	novo->dado = num;

	novo->prox = h[pos];
	h[pos] = novo;
	
}

//Funcao que imprime todos os dados armazenados na hash
void imprimirHash(hash *h[]){
	
	int i;
	hash* aux;

	for(i = 0; i < SIZE; i++){

		aux = h[i];
		printf("%d: ", i);
		while(aux != NULL){
			
			printf("%d ", aux->dado);
			aux = aux->prox;
		}
		printf("\n");
	}
}

//Funcao que imprime todos os dados armazenados na hash com tamanho definido pelo usuario
void imprimirHash2(hash *h[], int tamanho){
	
	int i;
	hash* aux;

	for(i = 0; i < tamanho; i++){

		aux = h[i];
		printf("%d: ", i);
		while(aux != NULL){
			
			printf("%d ", aux->dado);
			aux = aux->prox;
		}
		printf("\n");
	}
}

