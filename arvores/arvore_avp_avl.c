/*
 * Programa para comparar operações em Árvores AVL e Vermelho e Preto (AVP).
 * 
 * Regras:
 * - Entrada e saída "secas", sem textos explicativos, seguindo o modelo.
 * - Identificadores claros e documentação adequada (comentários e cabeçalho).
 * - Código em C/C++ com desalocação correta da memória dinâmica.
 * - Submissão pelo judge da Unifesp (http://judge.unifesp.br/AEDII202401).
 * 
 * Funcionalidades:
 * - Criar uma AVL e uma AVP, realizar inserção, pesquisa e cálculo de altura.
 * - Na AVP, calcular também a altura negra (contando só nós pretos).
 * - Contar total de rotações e mudanças de cor durante balanceamentos.
 * - Entrada: sequência de inteiros positivos, terminando com inteiro negativo.
 * - Saída: alturas das árvores, altura negra da AVP e totais de mudanças de cor e rotações.
 * 
 * Condições:
 * - Complexidade dos métodos conforme aulas.
 * - Nós não são removidos.
 * - Balanceamento e atualizações conforme regras específicas de AVL e AVP.
 */


#include <stdio.h>
#include <stdlib.h>

#define PRETO 0
#define VERMELHO 1

// Estrutura árvore AVL
typedef struct AVL {
    int chave;
    struct AVL *esq, *dir;
    int altura;
} AVL;

typedef struct AVL *Pavl;

// Estrutura árvor vermelho e preto
typedef struct AVP {
    int chave;
    struct AVP *esq, *dir, *pai;
    int cor;
} AVP;

typedef struct AVP *Pavp;

/* ---------- FUNÇÕES AVL ---------- */
Pavl criar_no_avl(int chave) {
    Pavl novo = (Pavl) malloc(sizeof(AVL));
    if (!novo) {
        exit(1);
    }

    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1; 
    return novo;
}

Pavl buscar_avl(Pavl raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) return raiz;
    if (chave < raiz->chave) return buscar_avl(raiz->esq, chave);
    return buscar_avl(raiz->dir, chave);
}

int altura_avl(Pavl no) {
    if (no == NULL) return 0;  // árvore vazia tem altura 0
    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualizar_altura(Pavl no) {
    if (no != NULL)
        no->altura = 1 + max(altura_avl(no->esq), altura_avl(no->dir));
}

int fator_balanceamento_avl(Pavl no) {
    if (no == NULL) return 0;
    return altura_avl(no->esq) - altura_avl(no->dir);
}

Pavl rot_dir_avl(Pavl y) {
    Pavl x = y->esq;
    Pavl T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

Pavl rot_esq_avl(Pavl x) {
    Pavl y = x->dir;
    Pavl T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

Pavl balancear_avl(Pavl no, int *rotacoes){
    atualizar_altura(no);
    int fb = fator_balanceamento_avl(no);

    if (fb > 1) {
        if (fator_balanceamento_avl(no->esq) < 0) {
            no->esq = rot_esq_avl(no->esq);
        }
        (*rotacoes)++;
        Pavl nova_raiz = rot_dir_avl(no);
        atualizar_altura(nova_raiz);
        return nova_raiz;
    }

    if (fb < -1) {
        if (fator_balanceamento_avl(no->dir) > 0) {
            no->dir = rot_dir_avl(no->dir);
        }
        (*rotacoes)++;
        Pavl nova_raiz = rot_esq_avl(no);
        atualizar_altura(nova_raiz);
        return nova_raiz;
    }

    return no;
}

Pavl inserir_avl(Pavl raiz, int chave, int *rotacoes) {
    if (raiz == NULL) return criar_no_avl(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir_avl(raiz->esq, chave, rotacoes);
    else if (chave > raiz->chave)
        raiz->dir = inserir_avl(raiz->dir, chave, rotacoes);
    else
        return raiz;

    return balancear_avl(raiz, rotacoes);
}

void imprimir_alturas_avl(Pavl no) {
    if (no == NULL) {
        printf("0, 0, 0");
        return;
    }
    printf("%d, %d, %d\n", (no->altura)-1, altura_avl(no->esq), altura_avl(no->dir));
}

void liberar_avl(AVL* raiz) {
    if (!raiz) return;
    liberar_avl(raiz->esq);
    liberar_avl(raiz->dir);
    free(raiz);
}


/* ---------- FUNÇÕES AVP ---------- */
Pavp criar_no_avp(int chave){
    Pavp novo = (Pavp) malloc(sizeof(AVP));

    if (!novo) {
        exit(1);
    }

    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai=NULL;
    novo->cor = VERMELHO; 
    return novo;
}

Pavp buscar_avp(Pavp raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) return raiz;
    if (chave < raiz->chave) return buscar_avp(raiz->esq, chave);
    return buscar_avp(raiz->dir, chave);
}

void rot_dir_avp(Pavp *raiz, Pavp x){
    Pavp y = x->esq;  // y é o filho esquerdo de x
    x->esq = y->dir; // O filho direito se torna o filho esquerdo

    if(y->dir != NULL){ // se existir novo filho a direita
        y->dir->pai = x; //atuaiza o pai (x)
    }
    
    y->pai = x->pai; // y assume o lugar de x, herda seu pai

    if(x->pai == NULL){ // se x era raiz
        *raiz = y;
        y->pai = NULL;

    } 
    else if(x == x->pai->dir){ //se x era filho a dir
        x->pai->dir = y;
    } 
    else{
        x->pai->esq = y;
    }

    // x se torna filho direito de y
    y->dir = x; 
    x->pai = y;
}

void rot_esq_avp(Pavp *raiz, Pavp x){
    Pavp y = x->dir;  // y é o filho direito de x
    x->dir = y->esq; // O filho esquerdo se torna o filho direito

    if(y->esq != NULL){ // se existir novo filho a esquerda
        y->esq->pai = x; //atuaiza o pai (x)
    }
    y->pai = x->pai; // y assume o lugar de x, herda seu pai

    if(x->pai == NULL){ // se x era raiz
        *raiz = y;
        y->pai = NULL;

    } 
    else if(x == x->pai->esq){ //se x era filho a esq
        x->pai->esq = y;
    } 
    else{
        x->pai->dir = y;
    }

    // x se torna filho esq de y
    y->esq = x; 
    x->pai = y;
}

void corrigir_insercao(Pavp *raiz, Pavp novo, int *mud_cor, int *rotacoes){
    while(novo->pai && novo->pai->cor == VERMELHO){ // Enquanto o pai for vermelho (Violação: Verm -> Verm)
        
        if(novo->pai == novo->pai->pai->esq){ // Se o pai for filho a esq
            Pavp tio = novo->pai->pai->dir; // Então tio é filho a dir

            // Caso 1: TIO VERMELHO - Recolore tio e pai para pretos e avô vermelho
            if(tio && tio->cor == VERMELHO){
                (*mud_cor)+=3;
                novo->pai->cor = PRETO;
                tio->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                novo = novo->pai->pai; // Sobe para olhar o avô
            } 

            // Caso 2: TIO PRETO
            else {
                if(novo == novo->pai->dir){ // Caso 2A: "zig-zag" esq-dir
                    novo = novo->pai;
                    (*rotacoes)++;
                    rot_esq_avp(raiz, novo);
                }

                // Caso 2C: "reto" esq-esq
                (*mud_cor)+=2;
                novo->pai->cor = PRETO; // Troca cor entre pai e avô
                novo->pai->pai->cor = VERMELHO;
                (*rotacoes)++;
                rot_dir_avp(raiz, novo->pai->pai); // Rotação direita no avô
            }

        }
        else{ // Pai filho a dir
            Pavp tio = novo->pai->pai->esq; // Então tio é filho a esq

            // Caso 1: TIO VERMELHO - Recolore tio e pai para pretos e avô vermelho
            if(tio && tio->cor == VERMELHO){
                (*mud_cor)+=3;
                novo->pai->cor = PRETO;
                tio->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                novo = novo->pai->pai; // Sobe para olhar o avô
            } 

            // Caso 2: TIO PRETO
            else {
                if(novo == novo->pai->esq){ // Caso 2B: "zig-zag" dir-esq
                    novo = novo->pai;
                    (*rotacoes)++;
                    rot_dir_avp(raiz, novo);
                }

                // Caso 2D: "reto" dir-dir
                (*mud_cor)+=2;
                novo->pai->cor = PRETO; // Troca cor entre pai e avô
                novo->pai->pai->cor = VERMELHO;
                (*rotacoes)++;
                rot_esq_avp(raiz, novo->pai->pai); // Rotação esquerda no avô
            }

        }
    }
        
    (*raiz)->cor = PRETO;  // Garante que raiz seja preta
    
}

Pavp inserir_avp(Pavp *raiz, int chave,int *mud_cor, int *rotacoes){
    Pavp novo = criar_no_avp(chave);
    Pavp y = NULL; // Pai temporário
    Pavp aux = *raiz;

    while(aux != NULL){ // Achar posição de inserção
        y = aux; // Segue o auxiliar (pai de novo)

        if(novo->chave < aux->chave){ // Verifica se irá para esquerda ou direita
            aux = aux->esq;
        } 
        else{
            aux = aux->dir;
        }
    }

    novo->pai=y; // Define o pai de z

    if(y == NULL){ // se a árvore estava vazia
        *raiz = novo; 
    } 
    else if(novo->chave < y->chave){ // Se for menor que o pai insere a esq
        y->esq = novo;
    } 
    else{
        y->dir = novo;
    }

    corrigir_insercao(raiz, novo, mud_cor, rotacoes); // Corrige as propriedas da AVP após inserir
}

int altura_avp(Pavp no){
    if(no == NULL) return 0;// Árvore vazia

    int esq = altura_avp(no->esq); //subarvore esq
    int dir = altura_avp(no->dir); // Subarvore dir

    return 1 + (esq > dir ? esq : dir); // 1 + maior das alturas
}

int altura_preta(Pavp no) {
    if (no == NULL) return 0;
    int alt_esq = altura_preta(no->esq);
    int alt_dir = altura_preta(no->dir);
    return (alt_esq == alt_dir ? alt_esq + (no->cor == PRETO ? 1 : 0) : -1);
}

void imprimir_alturas_avp(Pavp no) {
    if (no == NULL) {
        printf("0, 0, 0\n");
        return;
    }
    int h = altura_avp(no)-1;
    int h_esq = altura_avp(no->esq);
    int h_dir = altura_avp(no->dir);
    printf("%d, %d, %d\n", h, h_esq, h_dir);
}

// Libera a memória alocada para a árvora AVP
void liberar_avp(AVP* raiz) {
    if (!raiz) return;
    liberar_avp(raiz->esq);
    liberar_avp(raiz->dir);
    free(raiz);
}

int main() {
    int mudanca_cor = 0, rot_avp = 0, rot_avl = 0;
    Pavl raiz_avl = NULL;
    Pavp raiz_avp = NULL;
    int x;

    while (scanf("%d", &x), x >= 0) {
        raiz_avl = inserir_avl(raiz_avl, x, &rot_avl);
        raiz_avp = inserir_avp(&raiz_avp, x, &mudanca_cor, &rot_avp);
    }

    imprimir_alturas_avl(raiz_avl);
    imprimir_alturas_avp(raiz_avp);
    printf("%d\n", altura_preta(raiz_avp));
    printf("%d, %d, %d\n", mudanca_cor, rot_avp, rot_avl);

    liberar_avl(raiz_avl);
    liberar_avp(raiz_avp);

    return 0;
}
