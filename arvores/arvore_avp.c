/*
Descrição:
-----------
Implementar uma Árvore Rubro-Negra (AVP) que suporte as seguintes operações:

1. Inserção de elementos.
2. Busca de elementos.
3. Remoção de elementos (quando necessário, promove o sucessor — menor chave da
   subárvore à direita).
4. Cálculo da altura total da árvore (distância até o nó folha mais distante).
5. Cálculo da altura rubro (distância até o nó folha mais distante, contando
   apenas nós vermelhos, incluindo o próprio nó se for vermelho).

Formato da Entrada:
--------------------
1. Primeira linha:
   - Lista de inteiros positivos (chaves) a serem inseridos na árvore.
   - A entrada termina com um número negativo (não inserido).

2. Segunda linha:
   - Lista de inteiros para busca na árvore.
   - Se encontrado, o elemento deve ser removido.
   - Se não encontrado, deve ser inserido.
   - Termina com um número negativo.

3. Terceira linha:
   - Um único inteiro para busca da altura rubro.
   - Se encontrado, retorna a altura rubro desse nó.
   - Se não encontrado, imprime: "Valor nao encontrado".

Formato da Saída:
-------------------
1. Altura total da árvore após a primeira inserção:
   - Formato: altura_da_raiz, altura_subarvore_esq, altura_subarvore_dir

2. Para cada elemento da segunda linha que for encontrado (antes de ser removido):
   - Formato: altura_do_no, altura_subarvore_esq, altura_subarvore_dir

3. Para o elemento da terceira linha:
   - Se encontrado: altura rubro (número inteiro)
   - Se não encontrado: "Valor nao encontrado"
*/


#include <stdio.h>
#include <stdlib.h>

#define PRETO 0
#define VERMELHO 1

typedef struct AVP {
    int chave;
    struct AVP *esq, *dir, *pai;
    int cor;
} AVP;

typedef struct AVP *Pavp;

// Cria nó
Pavp criar_no_avp(int chave){
    Pavp novo = (Pavp) malloc(sizeof(AVP));
    novo->chave = chave;
    novo->esq = novo->dir = novo->pai = NULL;
    novo->cor = VERMELHO;
    return novo;
}

// Rotações
void rot_dir_avp(Pavp *raiz, Pavp x){
    Pavp y = x->esq;
    x->esq = y->dir;
    if (y->dir) y->dir->pai = x;
    y->pai = x->pai;
    if (!x->pai) *raiz = y;
    else if (x == x->pai->dir) x->pai->dir = y;
    else x->pai->esq = y;
    y->dir = x;
    x->pai = y;
}

void rot_esq_avp(Pavp *raiz, Pavp x){
    Pavp y = x->dir;
    x->dir = y->esq;
    if (y->esq) y->esq->pai = x;
    y->pai = x->pai;
    if (!x->pai) *raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

// Correção após inserção
void corrigir_insercao(Pavp *raiz, Pavp z){
    while (z->pai && z->pai->cor == VERMELHO){
        if (z->pai == z->pai->pai->esq){
            Pavp y = z->pai->pai->dir;
            if (y && y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir){
                    z = z->pai;
                    rot_esq_avp(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rot_dir_avp(raiz, z->pai->pai);
            }
        } else {
            Pavp y = z->pai->pai->esq;
            if (y && y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq){
                    z = z->pai;
                    rot_dir_avp(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rot_esq_avp(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

// Inserção
void inserir_avp(Pavp *raiz, int chave){
    Pavp z = criar_no_avp(chave);
    Pavp y = NULL;
    Pavp x = *raiz;
    while (x != NULL){
        y = x;
        if (z->chave < x->chave) x = x->esq;
        else x = x->dir;
    }
    z->pai = y;
    if (!y) *raiz = z;
    else if (z->chave < y->chave) y->esq = z;
    else y->dir = z;
    corrigir_insercao(raiz, z);
}

// Busca
Pavp buscar_avp(Pavp raiz, int chave){
    while (raiz && raiz->chave != chave)
        raiz = (chave < raiz->chave) ? raiz->esq : raiz->dir;
    return raiz;
}

// Altura
int altura_avp(Pavp no){
    if (!no) return 0;
    int e = altura_avp(no->esq);
    int d = altura_avp(no->dir);
    return 1 + (e > d ? e : d);
}

// Altura rubro
int altura_rubro(Pavp no){
    if (!no) return 0;
    int e = altura_rubro(no->esq);
    int d = altura_rubro(no->dir);
    return (no->cor == VERMELHO ? 1 : 0) + (e > d ? e : d);
}

// Transplante
void transplante(Pavp *raiz, Pavp u, Pavp v){
    if (!u->pai) *raiz = v;
    else if (u == u->pai->esq) u->pai->esq = v;
    else u->pai->dir = v;
    if (v) v->pai = u->pai;
}

// Mínimo
Pavp minimo(Pavp no){
    while (no->esq) no = no->esq;
    return no;
}

// Correção após remoção
void corrigir_remocao(Pavp *raiz, Pavp x){
    while (x != *raiz && (!x || x->cor == PRETO)){
        Pavp w;
        if (x == x->pai->esq){
            w = x->pai->dir;
            if (w && w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rot_esq_avp(raiz, x->pai);
                w = x->pai->dir;
            }
            if ((!w->esq || w->esq->cor == PRETO) &&
                (!w->dir || w->dir->cor == PRETO)){
                if (w) w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (!w->dir || w->dir->cor == PRETO){
                    if (w->esq) w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rot_dir_avp(raiz, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                if (w->dir) w->dir->cor = PRETO;
                rot_esq_avp(raiz, x->pai);
                x = *raiz;
            }
        } else {
            w = x->pai->esq;
            if (w && w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rot_dir_avp(raiz, x->pai);
                w = x->pai->esq;
            }
            if ((!w->dir || w->dir->cor == PRETO) &&
                (!w->esq || w->esq->cor == PRETO)){
                if (w) w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (!w->esq || w->esq->cor == PRETO){
                    if (w->dir) w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rot_esq_avp(raiz, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                if (w->esq) w->esq->cor = PRETO;
                rot_dir_avp(raiz, x->pai);
                x = *raiz;
            }
        }
    }
    if (x) x->cor = PRETO;
}

// Remoção
void remover(Pavp *raiz, Pavp z){
    Pavp y = z;
    int cor_original = y->cor;
    Pavp x;
    if (!z->esq){
        x = z->dir;
        transplante(raiz, z, z->dir);
    } else if (!z->dir){
        x = z->esq;
        transplante(raiz, z, z->esq);
    } else {
        y = minimo(z->dir);
        cor_original = y->cor;
        x = y->dir;
        if (y->pai == z){
            if (x) x->pai = y;
        } else {
            transplante(raiz, y, y->dir);
            y->dir = z->dir;
            if (y->dir) y->dir->pai = y;
        }
        transplante(raiz, z, y);
        y->esq = z->esq;
        if (y->esq) y->esq->pai = y;
        y->cor = z->cor;
    }
    free(z);
    if (cor_original == PRETO)
        corrigir_remocao(raiz, x);
}

// Liberação
void liberar(Pavp raiz){
    if (!raiz) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}

// Impressão de alturas
void imprimir_alturas(Pavp no){
    int h = altura_avp(no) - 1;
    int he = altura_avp(no->esq);
    int hd = altura_avp(no->dir);
    printf("%d, %d, %d\n", h, he, hd);
}

// Main
int main(){
    Pavp raiz = NULL;
    int v;

    // Linha 1 - Inserção inicial
    while (scanf("%d", &v), v >= 0)
        inserir_avp(&raiz, v);
    imprimir_alturas(raiz);

    // Linha 2 - Busca e insere ou remove
    while (scanf("%d", &v), v >= 0){
        Pavp encontrado = buscar_avp(raiz, v);
        if (encontrado){
            imprimir_alturas(encontrado);
            remover(&raiz, encontrado);
        } else {
            inserir_avp(&raiz, v);
        }
    }

    // Linha 3 - Altura rubro
    scanf("%d", &v);
    Pavp alvo = buscar_avp(raiz, v);
    if (alvo){
        printf("%d\n", altura_rubro(alvo));
    } else {
        printf("Valor nao encontrado\n");
    }

    liberar(raiz);
    return 0;
}
