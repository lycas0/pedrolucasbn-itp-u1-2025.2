#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Resolve o problema do Campo Agrícola, contando setores férteis irrigados e não irrigados.
 * * Um setor fértil (1) é considerado irrigado se for vizinho (Norte, Sul, Leste, Oeste) a um
 * setor ocupado por um irrigador (2).
 */
void resolver_campo_agricola() {
    int M, N;
    int i, j;
    
    // 1. Torna a leitura das dimensões M e N interativa
    printf("\nPrograma de Irrigacao do Campo Agricola\n");
    printf("Digite o numero de linhas (M) e o numero de colunas (N), separados por espaco (Max: 10 10): ");
    
    if (scanf("%d %d", &M, &N) != 2) {
        fprintf(stderr, "Erro ao ler as dimensoes M e N.\n");
        return;
    }

    // Verifica as restrições de tamanho
    if (M < 1 || M > 10 || N < 1 || N > 10) {
        fprintf(stderr, "Erro: M e N devem estar entre 1 e 10.\n");
        return;
    }

    // Declaração e leitura da matriz do campo
    int campo[10][10];
    int total_ferteis = 0;

    printf("\nDigite a matriz do campo (%d linhas e %d colunas):\n", M, N);
    printf("0 = Infertil, 1 = Fertil, 2 = Irrigador.\n");

    for (i = 0; i < M; i++) {
        printf("Linha %d (separada por espacos): ", i);
        for (j = 0; j < N; j++) {
            if (scanf("%d", &campo[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler o elemento (%d, %d) da matriz.\n", i, j);
                return;
            }
            if (campo[i][j] == 1) {
                total_ferteis++; // Conta o total de setores férteis
            }
        }
    }

    int irrigados_count = 0;
    
    // Vetores para representar os deslocamentos dos 4 vizinhos: (Linha, Coluna)
    int dr[] = {0, 0, 1, -1}; // Deslocamentos: Leste, Oeste, Sul, Norte
    int dc[] = {1, -1, 0, 0}; 

    // Percorre todos os setores da matriz para calcular a irrigação
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            
            // Só processa os setores férteis (1)
            if (campo[i][j] == 1) {
                
                int esta_irrigado = 0;
                
                // Verifica os 4 vizinhos (Norte, Sul, Leste, Oeste)
                for (int k = 0; k < 4; k++) {
                    int viz_i = i + dr[k]; // Índice da linha do vizinho
                    int viz_j = j + dc[k]; // Índice da coluna do vizinho

                    // Verifica se o vizinho está dentro dos limites da matriz
                    if (viz_i >= 0 && viz_i < M && viz_j >= 0 && viz_j < N) {
                        
                        // Verifica se o vizinho é um irrigador (2)
                        if (campo[viz_i][viz_j] == 2) {
                            esta_irrigado = 1;
                            break; // Se encontrou um irrigador, o setor está irrigado
                        }
                    }
                }

                // Contabiliza o setor fértil se estiver irrigado
                if (esta_irrigado) {
                    irrigados_count++;
                }
            }
        }
    }

    // Calcula o número de setores férteis não irrigados
    int nao_irrigados_count = total_ferteis - irrigados_count;

    // Impressão interativa do resultado
    printf("\nRESULTADO DA SIMULACAO\n");
    printf("Total de Setores Ferteis: %d\n", total_ferteis);
    printf("Setores Ferteis Irrigados: %d\n", irrigados_count);
    printf("Setores Ferteis NAO Irrigados: %d\n", nao_irrigados_count);
    printf("SAIDA FORMATADA: %d %d\n", irrigados_count, nao_irrigados_count);
}

/**
 * @brief Função principal
 */
int main() {
    resolver_campo_agricola();
    
    // O Visual Studio geralmente fecha a janela do console muito rápido após a execução.
    // Adicionar esta linha pausa o console até o usuário pressionar uma tecla,
    // o que é útil para programas interativos.
    printf("\nPressione ENTER para fechar...");
    getchar(); // Limpa o buffer
    getchar(); // Espera a tecla ENTER
    
    return 0;
}