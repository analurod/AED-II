#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX 100000000  // 10^8

#include <windows.h>
#include <wincrypt.h>

// Funções de Busca
int busca_linear(long int *v, int n, long int b) {
    for (int i = 0; i < n; i++) {
        if (v[i] == b) return i;
    }
    return -1;
}

int busca_binaria(long int *v, int n, long int b) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (v[meio] == b) return meio;
        if (v[meio] > b) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

int busca_binaria_rec(long int *v, int inicio, int fim, long int b) {
    if (inicio > fim) return -1;

    int meio = (inicio + fim) / 2;

    if (v[meio] == b) return meio;
    if (v[meio] > b) 
        return busca_binaria_rec(v, inicio, meio - 1, b);
    else 
        return busca_binaria_rec(v, meio + 1, fim, b);
}

int main() {
    long int *vetor = (long int *)malloc(sizeof(long int) * MAX);

    // Preenchendo vetor de tamanho 10^8
    for(int i=0; i<MAX; i++){
        vetor[i]=i;
    }

    // Definindo os valores a buscar (Pior Caso: 99999999 - Melhor Caso: 0 - Caso Médio: Aleatórios)
    long int buscar = 0;
    printf("%ld\n", buscar);

    LARGE_INTEGER freq, inicio, fim;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&inicio);
    busca_linear(vetor, MAX, buscar);
    QueryPerformanceCounter(&fim);
    double tempo_linear = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / (double)freq.QuadPart;

    QueryPerformanceCounter(&inicio);
    busca_binaria(vetor, MAX, buscar);
    QueryPerformanceCounter(&fim);
    double tempo_binaria = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / (double)freq.QuadPart;

    QueryPerformanceCounter(&inicio);
    busca_binaria_rec(vetor, 0, MAX-1, buscar);
    QueryPerformanceCounter(&fim);
    double tempo_binaria_rec = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / (double)freq.QuadPart;

    printf("Busca Linear: %.5f ms\n", tempo_linear);
    printf("Busca Binária: %.5f ms\n", tempo_binaria);
    printf("Busca Binária Recursiva: %.5f ms\n", tempo_binaria_rec);

    free(vetor);
    return 0;
}
