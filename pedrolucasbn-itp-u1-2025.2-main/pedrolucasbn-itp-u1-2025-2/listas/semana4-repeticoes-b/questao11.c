#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

int main() {
    // C0, C1, C2, C3 representam a coluna da rainha nas linhas 0, 1, 2, 3
    int c0, c1, c2, c3; 
    int contador = 0;

    printf("Soluções para o Problema das 4 Rainhas (Tabuleiro 4x4)\n\n");

    // Loop 1: Rainha na Linha 0 (Colunas 0 a 3)
    for (c0 = 0; c0 < 4; c0++) {
        
        // Loop 2: Rainha na Linha 1
        for (c1 = 0; c1 < 4; c1++) {
            
            // Loop 3: Rainha na Linha 2
            for (c2 = 0; c2 < 4; c2++) {
                
                // Loop 4: Rainha na Linha 3
                for (c3 = 0; c3 < 4; c3++) {
                    
                    // Inicializa a combinação como válida
                    int valido = 1;

                    // Checagem entre R0 e as outras (Linhas 0 e 1, 0 e 2, 0 e 3)
                    if (c0 == c1 || abs(c0 - c1) == 1) valido = 0; // Coluna ou Diagonal L1-L0
                    if (c0 == c2 || abs(c0 - c2) == 2) valido = 0; // Coluna ou Diagonal L2-L0
                    if (c0 == c3 || abs(c0 - c3) == 3) valido = 0; // Coluna ou Diagonal L3-L0

                    // Se ainda for válido, checar R1 e as outras (Linhas 1 e 2, 1 e 3)
                    if (valido && (c1 == c2 || abs(c1 - c2) == 1)) valido = 0; // Coluna ou Diagonal L2-L1
                    if (valido && (c1 == c3 || abs(c1 - c3) == 2)) valido = 0; // Coluna ou Diagonal L3-L1

                    // Se ainda for válido, checar R2 e R3 (Linhas 2 e 3)
                    if (valido && (c2 == c3 || abs(c2 - c3) == 1)) valido = 0; // Coluna ou Diagonal L3-L2

                    
                    // Se a combinação passou por todas as checagens
                    if (valido) {
                        contador++;
                        // Imprime a solução no formato (Linha, Coluna)
                        printf("Solução %d: R0:(0,%d), R1:(1,%d), R2:(2,%d), R3:(3,%d)\n", 
                               contador, c0, c1, c2, c3);
                    }
                }
            }
        }
    }

    printf("\nTotal de soluções encontradas: %d\n", contador);
    return 0;
}