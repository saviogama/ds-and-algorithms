#ifndef _RN_H
#define _RN_H

#include <stdio.h>
#include <stdlib.h>

#define preto 0
#define vermelho 1

typedef struct no{
	
	int dado;
	int cor;
	struct no *esq;
	struct no *dir;
	
}no;

typedef struct no *rn;
rn *raiz;

no* rotacaoesquerda(no *n);
no* rotacaodireita(no *n);
no* buscarNo(no *n, int dado);
rn* inicializar();
int inserirElemento(rn *raiz, int dado);
int acessarcor(no *n);
void percursoEmOrdem(rn *raiz);
void percursoPreOrdem(rn *raiz);
void percursoPosOrdem(rn *raiz);
int buscarMenor(rn *raiz);
int buscarMaior(rn *raiz);
int sucessor(rn *raiz, int valor);
int predecessor(rn *raiz, int valor);

#endif
