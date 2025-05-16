/*
Descrição:
Implemente os algoritmos de ordenação quadráticos (Selection Sort, Bubble Sort e
Insertion Sort) que realizem a ordenação de forma ascendente, com uma modificação:
parar o processamento assim que o vetor estiver totalmente ordenado, retornando
o número de comparações entre dois elementos da lista e de trocas de posição ou
movimentações de dados executadas.

Para comparações, considere todas as vezes, em qualquer trecho do código, em
que se comparam dois elementos do vetor/lista a ordenar, sendo verdadeiro ou não o
resultado dessa comparação (normalmente expresso com uma operação relacional do
tipo "maior que" ou "menor que").

Para trocas ou movimentações de dados, considere todas as execuções de swaps
quando os índices dos dados a serem trocados são distintos. Dessa forma, quando
os argumentos dos dados da função swap indicarem dois valores que representam a
mesma posição, a função não deve ser executada e, consequentemente, não computar como uma troca.

Para o algoritmo Insertion Sort, devem-se computar também como
movimentações os deslocamentos efetuados nos dados do vetor, bem como a colocação
do dado chave (key) na posição correta, quando essa nova posição for diferente da original.

ENTRADA:
• Um inteiro N (1 ≤ N ≤ 1000), representando o tamanho do vetor.
• N inteiros distintos (cada um entre −10^5 e 10^5), representando os elementos do vetor, separados por um espaço em branco entre si.

SAÍDA:
Três (3) linhas, cada qual com dois inteiros, representando a quantidade de comparações
e de trocas de elementos efetuadas até finalizar a ordenação. Cada linha corresponde a
um algoritmo de ordenação, na seguinte ordem: Selection Sort, Bubble Sort e Insertion Sort.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Realiza a troca de valores entre duas posições distintas de memória
void troca_elemento(int *num_a, int *num_b){
    if(num_a == num_b) return; // Não troca se apontam para o mesmo endereço
    int aux = *num_a;
    *num_a = *num_b;
    *num_b = aux;
}

// Algoritmo Selection Sort: encontra o menor valor e o coloca na posição correta
// Conta todas as comparações e trocas realizadas
void selection_sort(int *v, int tamanho, int *cont_comp, int *cont_troca){ 
    for(int i = 0; i < tamanho - 1; i++){
        int menor_indice = i;
        for(int j = i + 1; j < tamanho; j++){
            (*cont_comp)++; // Conta comparação entre elementos
            if(v[j] < v[menor_indice]){
                menor_indice = j;
            }
        }
        if(menor_indice != i){
            troca_elemento(&v[i], &v[menor_indice]);
            (*cont_troca)++; // Conta troca de posição
        }
    }
}

// Algoritmo Bubble Sort: compara elementos adjacentes e os troca se necessário
// Encerra antecipadamente se o vetor já estiver ordenado
void bubble_sort(int *v, int tamanho, int *cont_comp, int *cont_troca){
    for(int i = 0; i < tamanho - 1; i++){
        int trocou = 0;
        for(int j = 0; j < tamanho - 1 - i; j++){
            (*cont_comp)++; // Conta comparação entre v[j] e v[j+1]
            if(v[j] > v[j+1]){
                troca_elemento(&v[j], &v[j+1]);
                (*cont_troca)++; // Conta troca entre elementos adjacentes
                trocou = 1;
            }
        }
        if(!trocou) break; // Interrompe se nenhuma troca ocorreu
    }
}

// Algoritmo Insertion Sort: insere cada elemento na posição correta à esquerda
// Conta todas as comparações e movimentações de elementos (inclusive a inserção final)
void insertion_sort(int *v, int tamanho, int *cont_comp, int *cont_troca) {
    for (int i = 0; i < tamanho; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*cont_comp)++; // Conta comparação entre v[j] e chave
            if (v[j] > chave) {
                v[j + 1] = v[j]; // Desloca o elemento para a direita
                (*cont_troca)++; // Conta a movimentação
                j--;
            } else {
                break;
            }
        }
        if (j + 1 != i) {
            v[j + 1] = chave; // Insere a chave na posição correta
            (*cont_troca)++;  // Conta a inserção final
        }
    }
}

int main(){
    int tamanho_vetor, cont_comp, cont_troca;
    int *vetor, *copia_vetor;

    // Lê o tamanho do vetor
    scanf("%d", &tamanho_vetor);

    // Aloca dinamicamente memória para o vetor original e sua cópia
    vetor = (int*) malloc(tamanho_vetor * sizeof(int));
    copia_vetor = (int*) malloc(tamanho_vetor * sizeof(int));

    // Verifica se a alocação deu certo
    if(!vetor || !copia_vetor){
        return 1;
    }

    // Lê os elementos do vetor
    for(int i = 0; i < tamanho_vetor; i++){
        scanf("%d", &vetor[i]);
    }

    // Executa Selection Sort e imprime comparações e trocas
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int)); // Faz a cópia do vetor não ordenado 
    cont_comp = cont_troca = 0;
    selection_sort(copia_vetor, tamanho_vetor, &cont_comp, &cont_troca);
    printf("%d %d\n", cont_comp, cont_troca);

    // Executa Bubble Sort e imprime comparações e trocas
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int)); // Faz a cópia do vetor não ordenado 
    cont_comp = cont_troca = 0;
    bubble_sort(copia_vetor, tamanho_vetor, &cont_comp, &cont_troca);
    printf("%d %d\n", cont_comp, cont_troca);

    // Executa Insertion Sort e imprime comparações e trocas
    memcpy(copia_vetor, vetor, tamanho_vetor * sizeof(int)); // Faz a cópia do vetor não ordenado 
    cont_comp = cont_troca = 0;
    insertion_sort(copia_vetor, tamanho_vetor, &cont_comp, &cont_troca);
    printf("%d %d\n", cont_comp, cont_troca);

    // Libera a memória alocada
    free(vetor);
    free(copia_vetor);

    return 0;
}
