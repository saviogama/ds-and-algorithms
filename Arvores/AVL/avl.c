#include "avl.h"



void iniciarArray(array *saida){
	saida->indice = 0;
}

void iniciar(avl *t){
	t->raiz = NULL;
}

//Insere um no na arvore
void inserir(avl *t, int numero){

	int fatorBalanceamento;
	int alturaFilhoTempEsq;
	int alturaFilhoTempDir;
	no *novo;	
	no *ultimo, *penultimo;
	no *tempRotacao, *filhoTempRotacao;

	novo = (no *)malloc(sizeof(no));

	novo->chave = numero;	
	ultimo = t->raiz;
	penultimo = NULL; 


	while(ultimo != NULL){

		penultimo = ultimo;

		if(novo->chave < ultimo->chave){
			ultimo = ultimo->esq;
		}

		else{
			ultimo = ultimo->dir;
		}
	}

	novo->pai = penultimo;

	if(penultimo == NULL){
		t->raiz = novo;
	}

	else if(novo->chave < penultimo->chave){
		penultimo->esq = novo;
	}

	else{
		penultimo->dir = novo;
	}

	tempRotacao = novo;

	while(tempRotacao != NULL){

		fatorBalanceamento = Fb(tempRotacao);

		if(fatorBalanceamento > 1){

			filhoTempRotacao = tempRotacao->esq;

			alturaFilhoTempEsq = Fb(filhoTempRotacao);			

			if(alturaFilhoTempEsq > 0){
				rotacaoSimplesDir(t, tempRotacao);
			}
			else{
				rotacaoSimplesEsq(t, filhoTempRotacao);
				rotacaoSimplesDir(t, tempRotacao);
			}
		}

		else if(fatorBalanceamento < -1){

			filhoTempRotacao = tempRotacao->dir;

			alturaFilhoTempEsq = Fb(filhoTempRotacao);

			if(alturaFilhoTempEsq < 0){
				rotacaoSimplesEsq(t, tempRotacao);
			}
			else if (alturaFilhoTempEsq > 0){
				rotacaoSimplesDir(t, filhoTempRotacao);
				rotacaoSimplesEsq(t, tempRotacao);
			}
		}
		tempRotacao = tempRotacao->pai;
	}


}

//Calcula altura da arvore
int alturaDoNo(no *atual){

	int he, hd;

	if(atual == NULL){
		return -1;
	}

	else{

		he = alturaDoNo(atual->esq);
		hd = alturaDoNo(atual->dir);

		if(he < hd){
			return hd + 1;
		}

		else{
			return he + 1;
		}
	}
}

//Calcula o fator de balanceamento
int Fb(no *atual){

	int fb, he, hd;
	
	he = alturaDoNo(atual->esq);
	hd = alturaDoNo(atual->dir);

	fb = he - hd;

	return fb;

}


//Rotacao simpĺes a direita
void rotacaoSimplesDir(avl *t, no *x){
	no *aux;

	if(x->pai == NULL){
		aux = x->esq;
		x->esq = aux->dir;
		aux->dir = x;
		x->pai = aux;
		t->raiz = aux;
		t->raiz->pai = NULL;
		
	}

	else if(x->pai->chave < x->chave){
		aux = x->esq;
		x->esq = aux->dir;
		aux->dir = x;
		x->pai->dir = aux;
		aux->pai = x->pai;
		x->pai = aux;
		return;
	}

	else{
		aux = x->esq;
		x->esq = aux->dir;
		aux->dir = x;
		x->pai->esq = aux;
		aux->pai = x->pai;
		x->pai = aux;
		return;
	}

}


//Faz percurso em preordem da arvore
void PercursoPreOrdem(no *atual){
	
	if(atual != NULL){
		printf("(");
		printf("%d ", atual->chave);
		PercursoPreOrdem(atual->esq);
		printf(")");
		PercursoPreOrdem(atual->dir);
	}	
}

//Rotacao simpĺes a esquerda
void rotacaoSimplesEsq(avl *t, no *x){
	no *aux;

	if(x->pai == NULL){
		aux = x->dir;
		x->dir = aux->esq;
		aux->esq = x;
		x->pai = aux;
		t->raiz = aux;
		aux->pai = NULL;
		return;
	}

	else if(x->pai->chave < x->chave){
		aux = x->dir;
		x->dir = aux->esq;
		aux->esq = x;
		x->pai->dir = aux;
		aux->pai = x->pai;
		x->pai = aux;
		return;
	}

	else{
		aux = x->dir;
		x->dir = aux->esq;
		aux->esq = x;
		x->pai->esq = aux;
		aux->pai = x->pai;
		x->pai = aux;
		return;
	}

}

void arraySaida(no *atual, array *saida){
	
	if(atual != NULL){
		saida->lista[saida->indice].num = atual->chave;
		saida->indice++;
		arraySaida(atual->esq, saida);
		arraySaida(atual->dir, saida);
	}	
}

void Menor(no *x){ //busca menor elemento da arvore

	while(x->esq != NULL && x != NULL){
		x = x->esq;
	}

	printf("\n%d\n", x->chave);
}

void Maior(no *x){ //busca maior elemento da arvore

	while(x->dir != NULL && x != NULL){
		x = x->dir;
	}

	printf("\n%d\n", x->chave);
}

// Busca o sucessor de um elemento da arvore
void sucessor(avl *t, int chave){

	no *ret = t->raiz;

	while(ret != NULL && ret->chave != chave){
		if(chave > ret->chave){
			ret = ret->dir;
		}

		else{
			ret = ret->esq;
		}

	}

	if(ret == NULL){
		printf("\n%d\n", -1);
		return;
	}

	if(ret->dir != NULL){
		return Menor(ret->dir);
	}

	ret = ret->pai;

	while(ret != NULL && ret->dir->chave == chave){
		chave = ret->chave;
		ret = ret->pai;
	}

	if(ret == NULL){
		printf("\n%d\n", -1);
		return;
	}

	printf("\n%d\n", ret->chave);
}

//Busca o predecessor de um elemento da arvore
void antecessor(avl *t, int chave){

	no *ret = t->raiz;

	while(ret != NULL && ret->chave != chave){

		if(chave > ret->chave){
			ret = ret->dir;
		}

		else{
			ret = ret->esq;
		}
	}

	if(ret == NULL){
		printf("\n%d\n", -1);
		return;
	}

	if(ret->esq != NULL){
		return Maior(ret->esq);
	}

	ret = ret->pai;

	while(ret != NULL && ret->esq->chave == chave){
		chave = ret->chave;
		ret = ret->pai;
	}

	if(ret == NULL){
		printf("\n%d\n", -1);
		return;
	}


	printf("\n%d\n", ret->chave);
}

