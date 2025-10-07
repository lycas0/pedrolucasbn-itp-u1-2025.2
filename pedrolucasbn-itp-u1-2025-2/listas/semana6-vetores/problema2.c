#include <stdio.h>
#include <stdbool.h> // Para usar o tipo bool (true/false)

// Define o limite máximo de figurinhas (m <= 1000)
#define MAX_FIGURINHAS 1001 
// Usamos 1001 para que os índices 1 a 1000 possam ser usados diretamente.

int main() {
    int m; // Total de figurinhas da coleção (1 a m)
    int n; // Quantidade de figurinhas que você possui
    int i; // Contador
    int num_fig; // Número da figurinha lida
    
    // O array 'possuo' será nosso marcador de presença (flag).
    // possuo[k] = true se você tiver a figurinha k, false caso contrário.
    // O tamanho é MAX_FIGURINHAS (1001) para usar os índices de 1 a 1000.
    bool possuo[MAX_FIGURINHAS]; 
    
    // O loop while(scanf(...) == 2) permite processar múltiplas entradas de teste
    while (scanf("%d %d", &m, &n) == 2) {
        
        // Inicialização: Marca todas as figurinhas como 'não possuo' (false)
        // Só precisamos inicializar de 1 a m.
        for (i = 1; i <= m; i++) {
            possuo[i] = false;
        }
        
        // Marca as figurinhas que você possui
        for (i = 0; i < n; i++) {
            scanf("%d", &num_fig);
            // Marca a figurinha lida como 'possuo' (true)
            // Assumimos que a entrada é válida (1 <= num_fig <= m)
            possuo[num_fig] = true;
        }
        
        // Imprime as figurinhas que estão faltando (em ordem crescente)
        // Faltando significa: possuo[i] é false
        
        // Variável para formatar a saída (espaço entre os números)
        bool primeiro_faltando = true; 
        
        for (i = 1; i <= m; i++) {
            if (possuo[i] == false) {
                // Se esta é a primeira figurinha faltando, não imprime espaço antes
                if (!primeiro_faltando) {
                    printf(" ");
                }
                
                // Imprime o número da figurinha
                printf("%d", i);
                
                // Marca que a primeira já foi impressa
                primeiro_faltando = false;
            }
        }
        
        // Imprime uma quebra de linha após o resultado
        printf("\n");
    }

    return 0;
}