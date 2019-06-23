#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int chave;
	struct no *pai;
	struct no *esq;
	struct no *dir;
}no;

typedef struct avl{
	no *raiz;
}avl;

typedef struct chave{
	int num;
}chave;

typedef struct array{
	chave lista[1000];
	int indice;
}array;

//inicializar
void iniciar(avl *t);
void iniciarArray(array *saida);

// Inserir
void inserir(avl *t, int numero);

// Percursos
void PercursoPreOrdem(no *x);
void arraySaida(no *atual, array *saida);

// Funções de busca
void Menor(no *x);
void Maior(no *x);
void sucessor(avl *t, int chave);
void antecessor(avl *t, int chave);

// AVL
int alturaDoNo(no *atual);
int Fb(no *atual);

//Rotações
void rotacaoSimplesDir(avl *t, no *desbalanceado);
void rotacaoSimplesEsq(avl *t, no *desbalanceado);
void rotacaoDuplaDireita(avl *t, no *desbalanceado);
void rotacaoDuplaEsquerda(avl *t, no *desbalanceado);
