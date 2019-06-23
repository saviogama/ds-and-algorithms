#include "heap.h"

//Inicializa o heap
void inicializarHeap(heap *h){
	h->indice = 1;
}

//Insere um valor na heap
void inserirHeap(heap *h, int x){
	if(h->indice <= 1){
		inicializarHeap(h);
	}
	h->heap[h->indice].dado = x;	
	organizarHeapMax(h);
	h->indice++;
}

//Organiza a heap
void organizarHeapMax(heap *h){

	int i = h->indice;
	int pai = i/2;

	if(h->indice > MAX){		
		printf("ERRO! Heap exedeu o tamanho\n");
		return;
	}

	while(i > 1 && h->heap[pai].dado < h->heap[i].dado){
		trocar(h, pai, i);
		i = pai;
		pai = i/2;
	}
}


//Troca dois elementos na heap
void trocar(heap *h, int i1, int i2){
	int aux = h->heap[i1].dado;
	h->heap[i1].dado = h->heap[i2].dado;
	h->heap[i2].dado = aux;
}

//Retorna o maior valor inserido na heap
int heapMax(heap *h){
	return h->heap[1].dado;	
}

//Ordena em ordem crescente a heap
void heapSort(heap *h){
	for(int i = h->indice-1;i > 1; i--){
		trocar(h, 1, i);				
		reorganizarHeap(h, i);	
	}
}

//Reorganiza a heap fazendo com que o elemento na posição 1 vá para a posição correta
void reorganizarHeap(heap *h, int max){

	int filho, atual;
	atual = 1;

	filho = maxFilho(h, max, atual);

	while(1){

		if(h->heap[filho].dado < h->heap[atual].dado || filho > max){
			break;
		}
		
		trocar(h, filho, atual);
		atual = filho;
		filho = maxFilho(h, max, atual);
	}
}

//Retorna o indice do maior filho de um elemento da heap
int maxFilho(heap *h, int max, int pai){// --> Função que auxilia no heapSort

	int filhoEsq = 2*pai;
	int filhoDir = 2*pai+1;

	if(filhoDir >= max){
		if(filhoEsq < max){
			return filhoEsq;
		}
		else{
			return max + 1;
		}
	}

	if(h->heap[filhoEsq].dado > h->heap[filhoDir].dado){
		return filhoEsq;
	}

	if(h->heap[filhoDir].dado > h->heap[filhoEsq].dado && filhoDir < max){
		return filhoDir;
	}


}

//Imprime a heap
void imprimirHeap(heap *h){

	int i;
	printf("\n");
	if(h->indice >= 1){
		for(i = 1;i < h->indice;i++){	
			printf("%d ", h->heap[i].dado);
 		}
	}
	else{
		printf("Lista vazia!");
	}
	 
	printf("\n\n");
}

