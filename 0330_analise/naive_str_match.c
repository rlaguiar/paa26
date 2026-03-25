#include <stdio.h>
#include <string.h>

int naive_string_match(char* texto, char* padrao) {
    int n = strlen(texto);
    int m = strlen(padrao);
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (texto[i + j] != padrao[j]) {
                break; // Caractere não bateu, sai do laço interno
            }
        }
        if (j == m) {
            return i; // Padrão encontrado no índice i
        }
    }
    return -1; // Padrão não encontrado
}

int main() {
    char texto[] = "ababcababcabc";
    char padrao[] = "abc";
    
    int resultado = naive_string_match(texto, padrao);
    
    if (resultado != -1) {
        printf("Padrão encontrado no índice: %d\n", resultado);
    } else {
        printf("Padrão não encontrado.\n");
    }
    
    return 0;
}