#include <stdio.h>
#include <stdlib.h>

#define VAZIO -1    // Marca posição vazia
#define REMOVIDO -2 // Marca posição removida

// Função h1
int h1(int k, int m) {
    return k % m;
}

// Função h2
int h2(int k, int m) {
    return 1 + (k % (m - 1));
}

// Função hash com duplo hashing
int hash(int k, int i, int m) {
    return (h1(k, m) + i * h2(k, m)) % m;
}

// Inserção na tabela hash
void inserir(int *tabela, int m, int chave) {
    for (int i = 0; i < m; i++) {
        int pos = hash(chave, i, m);
        if (tabela[pos] == VAZIO || tabela[pos] == REMOVIDO) {
            tabela[pos] = chave;
            return;
        }
    }
    // Caso não encontre espaço, não insere (mas não ocorre se m for adequado)
}

// Busca chave na tabela hash
int buscar(int *tabela, int m, int chave) {
    for (int i = 0; i < m; i++) {
        int pos = hash(chave, i, m);
        if (tabela[pos] == VAZIO) {
            return -1; // Não encontrado
        }
        if (tabela[pos] == chave) {
            return pos; // Encontrado
        }
    }
    return -1; // Não encontrado
}

// Remove todas as ocorrências da chave
int remover(int *tabela, int m, int chave) {
    int encontrado = 0;
    for (int i = 0; i < m; i++) {
        int pos = hash(chave, i, m);
        if (tabela[pos] == VAZIO) {
            return encontrado;
        }
        if (tabela[pos] == chave) {
            tabela[pos] = REMOVIDO;
            encontrado = 1;
            // Continua buscando outras ocorrências
        }
    }
    return encontrado;
}

// Imprime a tabela no formato exigido
void imprimirTabela(int *tabela, int m) {
    for (int i = 0; i < m; i++) {
        if (tabela[i] == VAZIO) {
            printf("\\");
        } else if (tabela[i] == REMOVIDO) {
            printf("D");
        } else {
            printf("%d", tabela[i]);
        }
        if (i != m - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

// Programa principal
int main() {
    int m;
    scanf("%d", &m);

    // Aloca tabela e inicializa
    int *tabela = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        tabela[i] = VAZIO;
    }

    // Leitura dos valores para inserção
    int valor;
    while (1) {
        scanf("%d", &valor);
        if (valor == -1) break;
        inserir(tabela, m, valor);
    }

    // Leitura do valor a ser pesquisado/removido
    int chave;
    scanf("%d", &chave);

    // Busca e remoção
    int encontrado = remover(tabela, m, chave);

    // Saída
    if (!encontrado) {
        printf("Valor nao encontrado\n");
    }
    imprimirTabela(tabela, m);

    // Libera memória
    free(tabela);
    return 0;
}
