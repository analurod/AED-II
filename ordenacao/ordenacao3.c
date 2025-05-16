#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define uma estrutura que armazena uma palavra com até 20 caracteres + '\0'
typedef struct palavras{
    char entradas[21];
} SPalavras;

typedef SPalavras *Ppalavras;

// Altera as letras maiúsculas da string para minúscula
void maiuscula_para_minuscula(Ppalavras string, int ind){
    int tamanho_palavra = strlen(string[ind].entradas);

    for(int i = 0; i < tamanho_palavra; i++){
        if(string[ind].entradas[i] >= 'A' && string[ind].entradas[i] <= 'Z'){
            string[ind].entradas[i] += 32;
        }
    }
}

// Atualiza a variável 'maior' com o tamanho da maior palavra 
void qual_maior(Ppalavras string, int ind, int *maior){
    int tamanho = strlen(string[ind].entradas);

    if((*maior) < tamanho){
        (*maior) = tamanho;
    }
}

/* Retorna o índice do caractere 'c' no alfabeto personalizado.
Se for '\0' (fim da string), retorna 0. Se não encontrar, também retorna 0. */
int qual_indice(char c, char alfabeto[]){
    if(c == '\0') return 0;
    for (int i = 0; i < 26; i++) {
        if (c == alfabeto[i]) return i + 1;
    }

    return 0;
}

/* Counting Sort para uma posição específica 'i' da palavra, usando o alfabeto personalizado.
Ordena as palavras com base no caractere dessa posição. */
void counting_sort(Ppalavras string, Ppalavras nova_string, int i, int total_palavras, char *alfabeto){
    int aux[27];

    // Inicializa vetor auxiliar com '0'
    for(int m = 0; m < 27; m++){
        aux[m] = 0;
    }

    // Conta quantas vezes cada caractere aparece na posição 'i'
    for(int j = 0; j < total_palavras; j++){
        int ind = qual_indice(string[j].entradas[i], alfabeto);
        aux[ind] = aux[ind] + 1;
    }

    // Realiza a soma acumulativa
    for(int k = 1; k < 27; k++){
        aux[k] = aux[k] + aux[k-1];
    }

    // Imprime o vetor acumulado
    for(int k = 0 ; k < 27 ; k++){
        printf("%d ",aux[k]);
    }
    printf("\n");

    // Ordena as palavras no vetor auxiliar
    for(int j = total_palavras - 1; j >= 0; j--){
        int ind = qual_indice(string[j].entradas[i], alfabeto);
        aux[ind] --;
        nova_string[aux[ind]] = string[j]; 
    }

    // Copia os dados do vetor auxiliar para o original
    for(int k = 0; k < total_palavras; k++){
        string[k] = nova_string[k];
    }
}

/* Executa o Radix Sort nas palavras, caractere por caractere,
usando Counting Sort como sub-rotina e o alfabeto personalizado. */
void radix_sort(Ppalavras string, int total_palavras, char *alfabeto, int *maior){
    Ppalavras nova_string = (Ppalavras)malloc(total_palavras * sizeof(SPalavras));

    for(int i = (*maior) - 1; i >= 0; i--){
        counting_sort(string, nova_string, i, total_palavras, alfabeto);
    }

    free(nova_string);
}

int main(){
    int total_palavras, maior = 0;
    char alfabeto[27];
    
    // Ler número de palavras a serem digitadas
    scanf("%d", &total_palavras);
    getchar(); 
    
    Ppalavras pontpala = (SPalavras*) malloc (total_palavras * sizeof(SPalavras));

    // Verifica erro de alocação dinâmica
    if(!pontpala){
        return EXIT_FAILURE;
    }

    // Ler 'nova ordem alfabética'
    fgets(alfabeto, sizeof(alfabeto), stdin);
    
    // Leitura das palavras
    for(int i = 0; i < total_palavras; i++){
        scanf("%s", pontpala[i].entradas);
        maiuscula_para_minuscula(pontpala, i);
        qual_maior(pontpala, i, &maior);
    }

    // Printa palavras desordenadas em minúsculo
    for(int i = 0; i < total_palavras; i++){
        printf("%s.\n", pontpala[i].entradas);
    }

    // Printa tamanho da maior palavra
    printf("%d\n", maior);

    // Ordena a lista de palavras utilizando Radix Sort
    radix_sort(pontpala, total_palavras, alfabeto, &maior);

    // Imprime lista das palavras ordenadas
    for(int i = 0; i < total_palavras; i++){
        printf("%s\n", pontpala[i].entradas);
    }

    // Libera memória alocada
    free(pontpala);

    return 0;
}