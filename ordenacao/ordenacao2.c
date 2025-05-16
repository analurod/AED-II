#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENTINELA 100000000

// Realiza a troca de valores entre duas posições distintas de memória
void troca_elemento(int *num_a, int *num_b){
    if(*num_a == *num_b) return; 
    int aux = *num_a;
    *num_a = *num_b;
    *num_b = aux;
}

// Acha a mediana entre 3 valores (primeiro, meio e último) do vetor/subvetor
void mediana3(int *v, int esq, int dir, int *comparacoes){
    int meio = (esq + dir) / 2;

    (*comparacoes)++;
    if(v[esq] > v[meio]) troca_elemento(&v[esq], &v[meio]);
    (*comparacoes)++;
    if(v[esq] > v[dir]) troca_elemento(&v[esq], &v[dir]);
    (*comparacoes)++;
    if(v[meio] > v[dir]) troca_elemento(&v[meio], &v[dir]);

    troca_elemento(&v[meio], &v[dir]); // Coloca o pivô (mediana) na última posição
}

// Intercala dois subvetores ordenados (merge) e conta comparações
void merge(int *v, int esq, int dir, int meio, int *comparacoes){
    int n1 = meio - esq + 1; 
    int n2 = dir - meio;
    int j = 0, k = 0;

    // Aloca vetores auxiliares (com espaço para a sentinela)
    int *esq_v = malloc((n1 + 1) * sizeof(int));
    int *dir_v = malloc((n2 + 1) * sizeof(int));

    if(!esq_v || !dir_v){
        printf("erro ao alocar\n");
        exit(EXIT_FAILURE); // Sai do programa com erro
    }

    // Copia os dados para os vetores auxiliares
    for(int i = 0; i < n1; i++) esq_v[i] = v[esq + i];
    for(int i = 0; i < n2; i++) dir_v[i] = v[meio + 1 + i];

    esq_v[n1] = SENTINELA; // Adiciona sentinela ao final
    dir_v[n2] = SENTINELA;

    // Intercala os dois subvetores ordenados de volta ao vetor original
    for(int c = esq; c <= dir; c++){
        (*comparacoes)++;
        if(esq_v[j] <= dir_v[k]) {
            v[c] = esq_v[j];
            j++;
        }
        else{
            v[c] = dir_v[k];
            k++;
        }
    }

    free(esq_v);
    free(dir_v);
}

// Algoritmo Merge Sort recursivo com contagem de comparações
void mergesort(int *v, int esq, int dir, int *comparacoes){
    if(esq < dir){
        int meio = (esq + dir) / 2;
        mergesort(v, esq, meio, comparacoes);
        mergesort(v, meio + 1, dir, comparacoes);
        merge(v, esq, dir, meio, comparacoes);
    }
}

// Função de partição do QuickSort com mediana de três como pivô
int particao(int *v, int esq, int dir, int *comparacoes){
    mediana3(v, esq, dir, comparacoes); // Seleciona e posiciona pivô
    int pivo = v[dir];
    int i = esq - 1;

    for(int j = esq; j < dir; j++){
        (*comparacoes)++;
        if(v[j] < pivo){
            i++;
            troca_elemento(&v[i], &v[j]);
        }
    }

    troca_elemento(&v[i+1], &v[dir]); // Coloca pivô na posição correta
    return i + 1;
}

// Algoritmo QuickSort recursivo com pivô pela mediana de três
void quicksort(int *v, int esq, int dir, int *comparacoes){
    if(esq < dir){
        int pivo = particao(v, esq, dir, comparacoes);
        quicksort(v, esq, pivo - 1, comparacoes);
        quicksort(v, pivo + 1, dir, comparacoes);
    }
}

// Algoritmo Insertion Sort com contagem de comparações
void insertion_sort(int *v, int tamanho, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++; // Conta comparação entre v[j] e chave
            if (v[j] > chave) {
                v[j + 1] = v[j]; // Desloca o elemento para a direita
                j--;
            } else {
                break;
            }
        }
        if (j + 1 != i) {
            v[j + 1] = chave; // Insere a chave na posição correta
        }
    }
}

// QuickSort híbrido: usa Insertion Sort para subvetores pequenos
void quicksort_hibrido(int *v, int esq, int dir, int *comparacoes){
    int tamanho = dir - esq + 1;
    if(tamanho <= 5){
        insertion_sort(v + esq, tamanho, comparacoes); // Aplica Insertion Sort no subvetor
    }
    else{
        if(esq < dir){
            int pivo = particao(v, esq, dir, comparacoes);
            quicksort_hibrido(v, esq, pivo - 1, comparacoes);
            quicksort_hibrido(v, pivo + 1, dir, comparacoes);
        }
    }
}

// Imprime vetor ordenado e total de comparações
void print_resp(int *v, int tamanho, int *comparacoes){
    for(int i = 0; i < tamanho; i++){
        printf("%d ", v[i]);
    }
    printf("\n%d\n", *comparacoes);
}

int main(){
    int tamanho_vetor, cont_comp = 0;
    int *vetor, *copia_vetor;

    // Leitura do tamanho do vetor
    scanf("%d", &tamanho_vetor);

    // Aloca de forma dinâmica a memória para o vetor e sua cópia
    vetor = (int*)malloc(tamanho_vetor * sizeof(int));
    copia_vetor = (int*)malloc(tamanho_vetor * sizeof(int));

    // Verifica alocação
    if(!vetor || !copia_vetor){
        printf("Erro ao alocar");
        exit(EXIT_FAILURE);
    }

    // Leitura dos elementos do vetor
    for(int i = 0; i < tamanho_vetor; i++){
        scanf("%d", &vetor[i]);
    }

    // Merge Sort
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int));
    cont_comp = 0;
    mergesort(copia_vetor, 0, tamanho_vetor - 1, &cont_comp);
    print_resp(copia_vetor, tamanho_vetor, &cont_comp);

    // QuickSort - Mediana de três
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int));
    cont_comp = 0;
    quicksort(copia_vetor, 0, tamanho_vetor - 1, &cont_comp);
    print_resp(copia_vetor, tamanho_vetor, &cont_comp);

    // QuickSort - Híbrido com Insertion Sort
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int));
    cont_comp = 0;
    quicksort_hibrido(copia_vetor, 0, tamanho_vetor - 1, &cont_comp);
    print_resp(copia_vetor, tamanho_vetor, &cont_comp);

    // Libera memória alocada dinamicamente
    free(vetor);
    free(copia_vetor);

    return 0;
}
