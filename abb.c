/*
 * Arvores binarias de busca.
 */

#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

void cria_arvore(Arvore *p) {
		*p = NULL;
}

void inorder(Arvore p) {
		if (p == NULL) return;
		inorder(p->esq);
		printf("%d ", p->filme);
		inorder(p->dir);
}

void preorder(Arvore p) {
		if (p == NULL) return;
		printf("%d ", p->filme);
		preorder(p->esq);
		preorder(p->dir);
}

void postorder(Arvore p) {
		if (p == NULL) return;
		postorder(p->esq);
		postorder(p->dir);
		printf("%d ", p->filme);
}

void largura(Arvore p) {
		if (p == NULL) return;
		No *fila[100];
		int ini = 0, fim = 0;
		fila[fim++] = p;

		while (ini < fim) {
				No *atual = fila[ini++];
				printf("%d ", atual->filme);
				if (atual->esq) fila[fim++] = atual->esq;
				if (atual->dir) fila[fim++] = atual->dir;
		}
}

int busca(Arvore p, Filme filme) {
		if (p == NULL) return 0;
		if (filme < p->filme) return busca(p->esq, filme);
		else if (filme > p->filme) return busca(p->dir, filme);
		else return 1;
}

int n_rec_busca(Arvore p, Filme filme) {
		while (p != NULL) {
				if (filme < p->filme)
						p = p->esq;
				else if (filme > p->filme)
						p = p->dir;
				else
						return 1;
		}
		return 0;
}

int insere(Arvore *p, Filme filme) {
		if (*p == NULL) {
				*p = (No*)malloc(sizeof(No));
				(*p)->filme = filme;
				(*p)->esq = (*p)->dir = NULL;
				return 1;
		}
		if (filme < (*p)->filme)
				return insere(&(*p)->esq, filme);
		else if (filme > (*p)->filme)
				return insere(&(*p)->dir, filme);
		else
				return 0; // já existe
}

int n_rec_insere(Arvore *p, Filme filme) {
		while (*p != NULL) {
				if (filme < (*p)->filme) {
						p = &(*p)->esq;
				} else if (filme > (*p)->filme) {
						p = &(*p)->dir;
				} else {
						return 0;
				}
		}
		*p = (No*)malloc(sizeof(No));
		(*p)->filme = filme;
		(*p)->esq = (*p)->dir = NULL;
		return 1;
}

No *encontra_pai(Arvore *p, Filme filme) {
		if (*p == NULL || (*p)->filme == filme) return NULL;
		No *atual = *p;
		while (atual != NULL) {
				if ((atual->esq && atual->esq->filme == filme) || (atual->dir && atual->dir->filme == filme)) {
						return atual;
				}
				if (filme < atual->filme)
						atual = atual->esq;
				else
						atual = atual->dir;
		}
		return NULL;
}

int remove_arv(Arvore *p, Filme filme) {
		if (*p == NULL) return 0;

		if (filme < (*p)->filme) {
				return remove_arv(&(*p)->esq, filme);
		} else if (filme > (*p)->filme) {
				return remove_arv(&(*p)->dir, filme);
		} else {
				No *temp = *p;
				if ((*p)->esq == NULL && (*p)->dir == NULL) {
						free(temp);
						*p = NULL;
				} else if ((*p)->esq == NULL) {
						*p = (*p)->dir;
						free(temp);
				} else if ((*p)->dir == NULL) {
						*p = (*p)->esq;
						free(temp);
				} else {
						No *sucessor = (*p)->dir;
						while (sucessor->esq != NULL)
								sucessor = sucessor->esq;
						(*p)->filme = sucessor->filme;
						remove_arv(&(*p)->dir, sucessor->filme);
				}
				return 1;
		}
}

int verifica_busca(Arvore p) {
		if (p == NULL) return 1;
		if (p->esq && p->esq->filme > p->filme) return 0;
		if (p->dir && p->dir->filme < p->filme) return 0;
		return verifica_busca(p->esq) && verifica_busca(p->dir);
}