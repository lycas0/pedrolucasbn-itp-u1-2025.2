#include <stdio.h>
#include <stdlib.h> // Para usar a função qsort, se quisermos ordenar (opcional, mas bom)

// Função principal
int main() {
    int m, n;
    
    // Leitura das Quantidades
    
    // m: Quantidade de números sorteados (1 <= m <= 30)
    // n: Quantidade de números na aposta (m <= n <= 50)
    printf("Digite a quantidade de numeros sorteados (m, max 30) e apostados (n, max 50): ");
    if (scanf("%d %d", &m, &n) != 2) {
        fprintf(stderr, "Erro na leitura de m e n.\n");
        return 1;
    }

    // Validação básica (o problema garante o intervalo, mas é boa prática)
    if (m < 1 || m > 30 || n < m || n > 50) {
        printf("Valores de m e n fora do intervalo especificado.\n");
        return 0;
    }

    // Declaração dos Vetores (Arrays)
    // Usamos os limites máximos para evitar problemas de memória (embora m e n sejam menores)
    int sorteados[30];
    int apostados[50];
    
    // Leitura dos Números Sorteados (m)
    printf("Digite os %d numeros sorteados:\n", m);
    for (int i = 0; i < m; i++) {
        // Assume que os números cabem em um int e que o usuário digitará no formato correto
        if (scanf("%d", &sorteados[i]) != 1) {
            fprintf(stderr, "Erro na leitura do numero sorteado %d.\n", i + 1);
            return 1;
        }
    }

    // Leitura dos Números Apostados (n)
    printf("Digite os %d numeros apostados:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &apostados[i]) != 1) {
            fprintf(stderr, "Erro na leitura do numero apostado %d.\n", i + 1);
            return 1;
        }
    }

    // Lógica da Contagem (Repetições Aninhadas)
    
    int acertos = 0;

    // Laço Externo: Percorre todos os números da APOSTA (n números)
    for (int i = 0; i < n; i++) {
        int numero_aposta = apostados[i];

        // Laço Interno: Compara o número da aposta atual (i) com TODOS os números SORTEADOS (m números)
        for (int j = 0; j < m; j++) {
            int numero_sorteado = sorteados[j];
            
            // Verifica se há correspondência
            if (numero_aposta == numero_sorteado) {
                acertos++;
                
                // O problema diz: "Assuma que um número não aparece mais de uma vez
                // no mesmo sorteio nem na mesma aposta."
                // Por isso, após encontrar uma correspondência, podemos parar de verificar
                // para esse número da aposta atual e ir para o próximo número da aposta.
                break; 
            }
        }
    }

    // Saída do Resultado
    printf("Output:\n%d\n", acertos);

    return 0;
}