# 📚 AED-II  

Bem-vindo ao repositório da disciplina **Algoritmos e Estruturas de Dados II (AED II)**. Aqui você encontrará materiais, exercícios e projetos desenvolvidos ao longo do semestre.  

## 📌 Informações Gerais  

- **Disciplina:** Algoritmos e Estruturas de Dados II (AED II)  
- **Período:** 2025.1  

## 👩‍🎓 Aluna  

- **Nome:** Ana Luisa  
- **Turma:** Noturno  
- **Linguagem utilizada:**  C

---

## 🗂️ Conteúdo

- [📘 Resumo Teórico](#-resumo-teórico)
  - [🔎 Análise Assintótica](#-análise-assintótica)
  - [🔁 Relações de Recorrência](#-relações-de-recorrência)
  - [🧠 Métodos de Análise de Recorrência](#-métodos-de-análise-de-recorrência)
- [🔃 Algoritmos de Ordenação](#-algoritmos-de-ordenação)
  - [Insertion Sort](#insertion-sort)
  - [Selection Sort](#selection-sort)
  - [Bubble Sort](#bubble-sort)
  - [Quick Sort](#quick-sort)
  - [Merge Sort](#merge-sort)
  - [HeapSort](#heapsort)
  - [Counting Sort](#counting-sort)
  - [Radix Sort](#radix-sort)
  - [Bucket Sort](#bucket-sort)
- [🔍 Busca em Memória Principal](#-busca-em-memória-principal)
- [🌳 Árvores de Busca](#-árvores-de-busca)
  - [ABB (Árvore Binária de Busca)](#abb-árvore-binária-de-busca)
  - [AVL](#avl)

---

## 📘 Resumo Teórico

### 🔎 Análise Assintótica
Estuda o comportamento de algoritmos em função do tamanho da entrada (n), usando notações como:
- **O(f(n))**: limite superior (pior caso).
- **Ω(f(n))**: limite inferior (melhor caso).
- **Θ(f(n))**: comportamento exato (caso médio).

### 🔁 Relações de Recorrência
Modelam o tempo de execução de algoritmos recursivos.  
Exemplo: `T(n) = 2T(n/2) + n` para MergeSort.

### 🧠 Métodos de Análise de Recorrência
Técnicas para resolver recorrências e estimar complexidade:

- **Substituição (Adivinhação e Indução)**  
  Adivinha uma solução e prova por indução.

- **Árvore de Recursão**  
  Representa chamadas recursivas como árvore e soma os custos por nível.

- **Teorema Mestre**  
  Para `T(n) = aT(n/b) + f(n)`:
  1. `f(n) = O(n^c)` com `c < log_b(a)` → `T(n) = Θ(n^log_b(a))`
  2. `f(n) = Θ(n^log_b(a))` → `T(n) = Θ(n^log_b(a) * log n)`
  3. `f(n) = Ω(n^c)` com `c > log_b(a)` → `T(n) = Θ(f(n))`, sob condições.

---

## 🔃 Algoritmos de Ordenação

### Insertion Sort
- Tempo: O(n²) pior, O(n) melhor.
- Estável e in-place.

### Selection Sort
- Tempo: O(n²) em todos os casos.
- In-place, não estável.

### Bubble Sort
- Tempo: O(n²), melhora com verificação de ordenação.
- Estável e in-place.

### Quick Sort
- Tempo: O(n log n) médio, O(n²) pior caso.
- In-place, não estável.

### Merge Sort
- Tempo: O(n log n) sempre.
- Estável, requer O(n) extra de memória.

### HeapSort
- Tempo: O(n log n) sempre.
- In-place, não estável.

### Counting Sort
- Tempo: O(n + k), onde k é o maior valor.
- Estável, não comparativo.

### Radix Sort
- Tempo: O(nk), com k = dígitos.
- Estável, não comparativo.

### Bucket Sort
- Tempo: O(n + k) esperado (com distribuição uniforme).
- Estável (dependente da ordenação interna).

---

## 🔍 Busca em Memória Principal
- **Sequencial:** O(n)
- **Binária:** O(log n), exige vetor ordenado.
- Depende da estrutura de dados utilizada (vetor, árvore, hash, etc).

---

## 🌳 Árvores de Busca

### ABB (Árvore Binária de Busca)
- Nó à esquerda < raiz < nó à direita.
- Operações: O(h) (altura da árvore), pior caso O(n) se desbalanceada.

### AVL
- ABB auto-balanceada.
- Mantém altura O(log n) com rotações.
- Inserção, remoção e busca em O(log n) garantido.
