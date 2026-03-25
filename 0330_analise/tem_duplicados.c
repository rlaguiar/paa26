#include <stdio.h>
#include <stdbool.h>

bool tem_duplicata(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                return true; // Encontrou duplicata, encerra imediatamente
            }
        }
    }
    return false; // Todos os elementos são únicos
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2}; // Exemplo de array com duplicata
    int n = sizeof(arr) / sizeof(arr[0]);

    if (tem_duplicata(arr, n)) {
        printf("O array tem duplicatas.\n");
    } else {
        printf("O array não tem duplicatas.\n");
    }

    return 0;
}