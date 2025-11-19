#include <stdio.h>
#include <stdlib.h>

// Define a constante para o tamanho máximo da matriz
#define MAX_TIMES 20

/**
 * @brief Resolve o problema do Campeonato de Empates, contando o numero de partidas empatadas.
 * * A partida entre time i e time j é um empate se placar[i][j] == placar[j][i].
 * * Cada partida deve ser contada apenas uma vez (iterando apenas i < j).
 */
void contar_empates() {
    int M;
    int i, j;
    
    // Leitura do número de times (M)
    printf("--- Programa de Campeonato de Empates ---\n");
    printf("Digite o numero total de times (M, max: %d): ", MAX_TIMES);
    
    if (scanf("%d", &M) != 1) {
        fprintf(stderr, "Erro ao ler o numero de times M.\n");
        return;
    }

    // Verifica a restrição de tamanho
    if (M < 1 || M > MAX_TIMES) {
        fprintf(stderr, "Erro: M deve estar entre 1 e %d.\n", MAX_TIMES);
        return;
    }

    // Declaração da matriz de placares (M x M)
    int placar[MAX_TIMES][MAX_TIMES];

    // Leitura da matriz de placares (M x M)
    printf("\nDigite a matriz de placares (%d x %d):\n", M, M);
    printf("O valor na posicao [i][j] e os gols do time i contra o time j.\n");
    printf("Digite os valores linha por linha, separados por espacos.\n");

    for (i = 0; i < M; i++) {
        printf("Placares do Time %d (contra times 0 a %d): ", i, M - 1);
        for (j = 0; j < M; j++) {
            if (scanf("%d", &placar[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler o elemento (%d, %d) da matriz.\n", i, j);
                return;
            }
        }
    }
    
    int empates_count = 0;
    
    // Contagem dos Empates (Iterando apenas o triângulo superior, i < j)
    for (i = 0; i < M; i++) {
        // Começa em i + 1 para evitar a diagonal (i vs i) e a dupla contagem (i vs j e j vs i)
        for (j = i + 1; j < M; j++) {
            
            // placar[i][j] (gols de i) == placar[j][i] (gols de j)?
            if (placar[i][j] == placar[j][i]) {
                empates_count++;
            }
        }
    }

    // Impressão do Resultado
    printf("\n--- RESULTADO DO CAMPEONATO ---\n");
    printf("O numero de partidas que terminaram empatadas foi: %d\n", empates_count);
}

/**
 * @brief Função principal
 */
int main() {
    contar_empates();
    
    // Pausa para visualização no console do Visual Studio
    printf("\nPressione ENTER para fechar...");
    // Adicione mais um getchar() se estiver usando VS para limpar o buffer
    getchar(); 
    getchar(); 
    
    return 0;
}