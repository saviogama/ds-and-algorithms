#include "rn.h"

//Inicializa a arvore
rn* inicializar(){
	rn* raiz = (rn*) malloc(sizeof(rn));
	*raiz = NULL;
	return raiz;
}

//Rotacao esquerda e ajuste de cores
no* rotacaoesquerda(no *n){ 
	no *aux;

	aux = n->dir;
	n->dir = aux->esq;
	aux->esq = n;
	aux->cor = n->cor;
	n->cor = vermelho;

	return aux;
}

//Rotacao direita e ajuste de cores
no* rotacaodireita(no *n){ 
	no *aux;

	aux = n->esq;
	n->esq = aux->dir;
	aux->dir = n;
	aux->cor = n->cor;
	n->cor = vermelho;

	return aux;
}

/*
Funcao que verifica onde o novo dado vai ser adicionado recursivamente...
insere...
e chama as funcoes de balanceamento de cores caso precise
*/
no* buscarNo(no *n, int dado){
	
	if(n == NULL){
		no* novo = (no*) malloc(sizeof(no));
		novo->dado = dado;
		novo->cor = vermelho;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(dado < n->dado){
		n->esq = buscarNo(n->esq, dado); //Chamada recursiva para o lado esquerdo do no
	}
	else{
		n->dir = buscarNo(n->dir, dado); //Chamada recursiva para o lado direito do no
	}

	if(acessarcor(n->dir) == vermelho && acessarcor(n->esq) == preto){ //Se existir elemento a direita e o elemento a esquerda for NULL, rotaciona
		n = rotacaoesquerda(n);
	}

	if(acessarcor(n->esq) == vermelho && acessarcor(n->esq->esq) == vermelho){ //Se tiver dois nos seguidos vermelhos, rotaciona
		n = rotacaodireita(n);
	}	

	if(acessarcor(n->dir) == vermelho && acessarcor(n->esq) == vermelho){ //Troca cores caso necessario
		n->cor = !n->cor;
		if(n->esq != NULL){
			n->esq->cor = !n->esq->cor;
		}
		if(n->dir != NULL){
			n->dir->cor = !n->dir->cor;
		}
	}
	
	return n; //Retorna o no para ser adicionado
}

int inserirElemento(rn *raiz, int dado){
	
	*raiz = buscarNo(*raiz, dado);
	if((*raiz) != NULL){
		(*raiz)->cor = preto;
		return 1;
	}
	
	else{ //Se der erro na alocacao retorna 0 pro main
		return 0;
	}
}

//Retorna a cor de um no
int acessarcor(no *n){
	if(n == NULL){
		return preto;
	}
	else{
		return n->cor;
	}
}	

//Faz o percurso em ordem
void percursoEmOrdem(rn *raiz){
	
	if(*raiz != NULL){
		percursoEmOrdem(&((*raiz)->esq));
		printf("%d\n", (*raiz)->dado);
		percursoEmOrdem(&((*raiz)->dir));
	}	
}

//Faz o percurso em preordem
void percursoPreOrdem(rn *raiz){

	if(*raiz != NULL){
		
		printf("(%d", (*raiz)->dado);
		if((*raiz)->cor == 1)
			printf("R");
		else
			printf("N");

		if((*raiz)->esq == NULL)
			printf(") (X) ");
		
		else
			printf(" ");
		
		percursoPreOrdem(&((*raiz)->esq));
		percursoPreOrdem(&((*raiz)->dir));
		
	}
		
}

//Faz o percurso em posordem
void percursoPosOrdem(rn *raiz){
	
	if(*raiz != NULL){
		percursoPosOrdem(&((*raiz)->esq));
		percursoPosOrdem(&((*raiz)->dir));
		printf("%d\n", (*raiz)->dado);
	}	
}

//Busca o menor elemento da arvore
int buscarMenor(rn *raiz){ 
	
	int x;
	no* aux = *raiz;
	while(aux->esq != NULL){
		aux = aux->esq;
	}
	x = aux->dado;
	return x;
}

//Busca o maior elemento da arvore
int buscarMaior(rn *raiz){ 
	
	int x;
	no* aux = *raiz;
	while(aux->dir != NULL){
		aux = aux->dir;
	}
	x = aux->dado;
	return x;
}

//Busca o sucessor de um elemento na rn
int sucessor(rn *raiz, int valor){

	int x;
	no *aux = *raiz;
	while(aux != NULL){
		if(valor == aux->dado){
			if(aux->dir != NULL){
				aux = aux->dir;
				x = aux->dado;
				return x;
			}
			else{
				return -1;
			}
		}
		if(valor > aux->dado)
			aux = aux->dir;
		
		else
			aux = aux->esq;

	}
	return -1;
}

//Busca o predecessor de um elemento na rn
int predecessor(rn *raiz, int valor){

	int x, pai;
	no *aux = *raiz;
	while(aux != NULL){
		if(aux->dado == valor){
			if(aux->esq != NULL){
				aux = aux->esq;
				x = aux->dado;
				return x;
			}
			else{
				return pai;
			}
		}
		if(valor > aux->dado){
			pai = aux->dado;
			aux = aux->dir;
		}
		
		else{
			pai = aux->dado;
			aux = aux->esq;
		}		
	}
	return -1;
}

