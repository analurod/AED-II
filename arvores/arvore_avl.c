/*
Descrição:
Este programa implementa as operações básicas de uma Árvore AVL, incluindo:
(1) inicialização, (2) pesquisa, (3) inserção, (4) remoção, 
(5) cálculo da altura de um nó e (6) busca de nós dentro de uma faixa de valores.

Regras e observações:
- Na remoção, deve-se promover o sucessor (menor chave da subárvore à direita).
- A altura de um nó é o número de passos até a folha mais distante (caminho mais longo).
- Após cada inserção ou remoção, o balanceamento da árvore deve ser verificado 
  e, se necessário, rotações devem ser realizadas para manter a AVL balanceada.

Restrições:
1. A complexidade de cada procedimento deve seguir o que foi apresentado em aula.
2. O código deve ser escrito em C, C++ ou Java.
3. Toda memória alocada dinamicamente deve ser corretamente liberada.
Soluções que violarem estas condições não serão aceitas.

Entrada:
- Linha 1: Lista de números inteiros positivos a serem inseridos na AVL. 
  A sequência termina com um número negativo (não inserido).
- Linha 2: Lista de números inteiros positivos para pesquisa. A sequência 
  também termina com um número negativo. Se o número for encontrado, ele é removido; 
  caso contrário, é inserido.
- Linha 3: Dois inteiros positivos representando a faixa de valores a ser buscada na árvore.

Saída:
1. Altura máxima da AVL (a partir da raiz), seguida das alturas das subárvores esquerda e direita da raiz, 
   com base apenas na árvore construída com os números da primeira linha de entrada.
2. As mesmas informações da linha anterior, mas após o processamento da segunda linha de entrada. 
   Caso a árvore esteja vazia, deve-se imprimir: "ARVORE VAZIA".
3. Lista de valores encontrados dentro da faixa especificada na terceira linha da entrada. 
   Se nenhum valor for encontrado, imprimir: "NADA A EXIBIR".
4. Para cada valor exibido na terceira linha de saída (caso existam), imprimir a altura do nó, 
   seguida das alturas de suas subárvores esquerda e direita.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esq;
    struct No *dir;
    int altura;
} No;

No* criar_no(int chave) {
    No* novo = (No*) malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;  // nó folha tem altura 1
    return novo;
}

int altura(No* no) {
    if (no == NULL) return 0;  // árvore vazia tem altura 0
    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualizar_altura(No* no) {
    if (no != NULL)
        no->altura = 1 + max(altura(no->esq), altura(no->dir));
}

int fator_balanceamento(No* no) {
    if (no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

No* rotacao_direita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

No* rotacao_esquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

No* balancear(No* no) {
    atualizar_altura(no);
    int fb = fator_balanceamento(no);

    if (fb > 1) {
        if (fator_balanceamento(no->esq) < 0)
            no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }

    if (fb < -1) {
        if (fator_balanceamento(no->dir) > 0)
            no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }

    return no;
}

No* inserir(No* raiz, int chave) {
    if (raiz == NULL) return criar_no(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else
        return raiz;

    return balancear(raiz);
}

No* minimo(No* no) {
    No* atual = no;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

No* remover(No* raiz, int chave) {
    if (raiz == NULL) return NULL;

    if (chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = remover(raiz->dir, chave);
    else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                free(raiz);
                return NULL;
            } else {
                No* aux = raiz;
                raiz = temp;
                free(aux);
            }
        } else {
            No* temp = minimo(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = remover(raiz->dir, temp->chave);
        }
    }
    return balancear(raiz);
}

int pesquisar(No* raiz, int chave) {
    if (raiz == NULL) return 0;
    if (chave == raiz->chave) return 1;
    if (chave < raiz->chave) return pesquisar(raiz->esq, chave);
    return pesquisar(raiz->dir, chave);
}

void buscar_faixa(No* raiz, int min, int max, int* vetor, int* tamanho) {
    if (raiz == NULL) return;

    if (raiz->chave > min) buscar_faixa(raiz->esq, min, max, vetor, tamanho);

    if (raiz->chave >= min && raiz->chave <= max) {
        vetor[(*tamanho)++] = raiz->chave;
    }

    if (raiz->chave < max) buscar_faixa(raiz->dir, min, max, vetor, tamanho);
}

No* obter_no(No* raiz, int chave) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == chave) return raiz;
    if (chave < raiz->chave) return obter_no(raiz->esq, chave);
    return obter_no(raiz->dir, chave);
}

void imprimir_alturas(No* no) {
    if (no == NULL) {
        printf("0, 0, 0");
        return;
    }
    printf("%d, %d, %d", no->altura - 1, altura(no->esq), altura(no->dir));
}

void liberar_arvore(No* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    No* raiz = NULL;
    int valor;

    // 1ª linha: inserir até valor negativo
    while (scanf("%d", &valor) == 1 && valor >= 0) {
        raiz = inserir(raiz, valor);
    }

    imprimir_alturas(raiz);
    printf("\n");

    // 2ª linha: pesquisar até negativo, inserir/remover
    while (scanf("%d", &valor) == 1 && valor >= 0) {
        if (pesquisar(raiz, valor))
            raiz = remover(raiz, valor);
        else
            raiz = inserir(raiz, valor);
    }

    if (raiz == NULL)
        printf("ARVORE VAZIA\n");
    else {
        imprimir_alturas(raiz);
        printf("\n");
    }

    // 3ª linha: faixa min max
    int min, max;
    scanf("%d %d", &min, &max);

    int vetor[10000], tamanho = 0;
    buscar_faixa(raiz, min, max, vetor, &tamanho);

    if (tamanho == 0) {
        printf("NADA A EXIBIR\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            if (i > 0) printf(", ");
            printf("%d", vetor[i]);
        }
        printf("\n");
        for (int i = 0; i < tamanho; i++) {
            No* no = obter_no(raiz, vetor[i]);
            imprimir_alturas(no);
            printf("\n");
        }
    }

    liberar_arvore(raiz);
    return 0;
}
