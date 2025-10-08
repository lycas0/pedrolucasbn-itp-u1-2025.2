#include <stdio.h>
#include <math.h>

int main() {
    int n;
    int numero_atual = 0;

    printf("Gerador de padrão numérico sequencial\n");
    printf("Digite o número de linhas ou n: ");

    // Leitura do número de linhas
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida. Digite um número positivo.\n");
        return 1;
    }
    
    printf("Padrão com %d linhas\n", n);

    // Loop externo: Controla o número de linhas (i)
    for (int i = 1; i <= n; i++) {
        
        // Loop interno para controlar o número de elementos por linha (j)
        for (int j = 1; j <= i; j++) {
            
            // Imprime o número atual
            printf("%d ", numero_atual);
            
            // Incrementa o contador para o PRÓXIMO número
            numero_atual++;
        }
        
        // Quebra de linha para iniciar uma nova linha do padrão
        printf("\n");
    }
    
    return 0;
}