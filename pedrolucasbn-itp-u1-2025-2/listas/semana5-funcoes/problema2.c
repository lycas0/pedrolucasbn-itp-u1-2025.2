#include <stdio.h>
#include <stdbool.h> // Para usar true e false

// Define o limite máximo para a busca
#define LIMITE 50000

// Função para verificar se um número é primo
// Retorna true se n for primo, false caso contrário.
bool eh_primo(int n) {
    // Casos triviais
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true; // 2 e 3 são primos
    }
    
    // Otimização: Elimina múltiplos de 2 e 3
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    // Loop otimizado: Checa divisores da forma 6k ± 1
    // A busca só precisa ir até a raiz quadrada de n (i * i <= n)
    for (int i = 5; i * i <= n; i = i + 6) {
        // Checa i (6k - 1)
        if (n % i == 0) {
            return false;
        }
        // Checa i + 2 (6k + 1)
        if (n % (i + 2) == 0) {
            return false;
        }
    }

    return true; // É primo
}


int main() {
    int x;
    
    printf("Trios de Primos na forma (x, x+2, x+6) até %d:\n", LIMITE);
    
    // Itera x até o ponto onde x + 6 não ultrapasse o limite
    for (x = 2; x <= LIMITE - 6; x++) {
        
        // Verifica se o primeiro número (x) é primo
        if (eh_primo(x)) {
            
            // Verifica se o segundo número (x + 2) é primo
            if (eh_primo(x + 2)) {
                
                // Verifica se o terceiro número (x + 6) é primo
                if (eh_primo(x + 6)) {
                    // Se todos forem primos, imprime o trio no formato solicitado
                    printf("(%d, %d, %d)\n", x, x + 2, x + 6);
                }
            }
        }
    }

    return 0;
}