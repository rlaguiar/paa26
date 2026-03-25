#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Função que troca dois elementos de lugar na memória
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função que verifica se o array está ordenado: O(n)
bool is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void drunkards_bogo_sort(int arr[], int n) {
    long long tentativas = 0; // Pode crescer absurdamente rápido

 // Continua enquanto o array não estiver ordenado
    while (!is_sorted(arr, n)) {
        // Sorteia dois índices aleatórios
        int i = rand() % n;
        int j = rand() % n;

        // Chama a função passando os endereços de memória
        swap(&arr[i], &arr[j]);

        tentativas++;
    }

    printf("Array ordenado com sucesso apos %lld trocas aleatorias!\n", tentativas);
}

// Função auxiliar para imprimir o vetor
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Inicializa a semente de aleatoriedade usando o relógio do sistema
    srand(time(NULL));

    // tentem ordenar com o maior N possível, mas aumentem devagar...
    int arr[] = {5, 2, 4, 1, 3}; 
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    print_array(arr, n);

    printf("\nIniciando o Drunkard's Bogo Sort...\n");
    drunkards_bogo_sort(arr, n);

    printf("Array resultante: ");
    print_array(arr, n);

    return 0;
}