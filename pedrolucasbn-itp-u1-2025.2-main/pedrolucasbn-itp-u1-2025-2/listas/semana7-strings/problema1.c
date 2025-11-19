#include <stdio.h>
#include <string.h>

int main() {
    // Declaração da string para a palavra (máximo 20 caracteres + '\0' de terminação)
    char palavra[21];
    // Declaração da variável para o índice a ser verificado
    int indice;

    // Ler a palavra (campo minado 1D)
    printf("Digite a palavra (max 20 chars, '.' ou 'x'): ");
    // Usamos scanf para ler a string. O modificador %20s garante que não leremos mais de 20 caracteres.
    if (scanf("%20s", palavra) != 1) {
        // Trata erro de leitura
        fprintf(stderr, "Erro ao ler a palavra.\n");
        return 1;
    }

    // Ler o índice
    printf("Digite o indice a ser verificado (começando em 0): ");
    if (scanf("%d", &indice) != 1) {
        // Trata erro de leitura
        fprintf(stderr, "Erro ao ler o indice.\n");
        return 1;
    }

    // Pega o tamanho real da string lida
    int tamanho = strlen(palavra);

    // Validação do Índice
    // Verifica se o índice está dentro dos limites da string.
    if (indice < 0 || indice >= tamanho) {
        printf("Indice invalido para a palavra de tamanho %d.\n", tamanho);
        return 0;
    }

    // Verificar se o índice é uma bomba ('x')
    if (palavra[indice] == 'x') {
        // A saída deve ser "bum!"
        printf("bum!\n");
    }
    // Se não for uma bomba, contar as bombas adjacentes
    else {
        // Contador de bombas adjacentes
        int bombas_adjacentes = 0;

        // Verificar adjacência à esquerda (indice - 1)
        // A condição 'indice > 0' garante que não estamos fora do limite esquerdo (antes do 0)
        if (indice > 0) {
            if (palavra[indice - 1] == 'x') {
                bombas_adjacentes++;
            }
        }

        // Verificar adjacência à direita (indice + 1)
        // A condição 'indice < tamanho - 1' garante que não estamos fora do limite direito
        if (indice < tamanho - 1) {
            if (palavra[indice + 1] == 'x') {
                bombas_adjacentes++;
            }
        }

        // A saída deve ser o número de bombas adjacentes
        printf("%d\n", bombas_adjacentes);
    }

    return 0;
}