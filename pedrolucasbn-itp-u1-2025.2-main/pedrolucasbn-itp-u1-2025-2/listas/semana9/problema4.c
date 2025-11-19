#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para usar INT_MAX

// Define a constante para o tamanho máximo da matriz
#define MAX_CIDADES 10

/**
 * @brief Resolve o problema da Viagem, encontrando o caminho mais barato de X para Z 
 * com no máximo 1 cidade intermediária.
 */
void encontrar_pechincha() {
    int M;
    int X, Z; // Cidades de origem e destino
    int i, j, Y;
    
    // Leitura do número de cidades (M)
    printf("--- Programa de Busca da Passagem Mais Barata (Pechincha) ---\n");
    printf("Digite o numero total de cidades (M, max: %d): ", MAX_CIDADES);
    
    if (scanf("%d", &M) != 1) {
        fprintf(stderr, "Erro ao ler o numero de cidades M.\n");
        return;
    }

    // Verifica a restrição de tamanho
    if (M < 1 || M > MAX_CIDADES) {
        fprintf(stderr, "Erro: M deve estar entre 1 e %d.\n", MAX_CIDADES);
        return;
    }

    // Declaração e leitura da matriz de custos (M x M)
    int custo[MAX_CIDADES][MAX_CIDADES];

    // Leitura dos custos
    printf("\nDigite a matriz de custos (%d x %d):\n", M, M);
    printf("O valor na posicao [i][j] e o custo da passagem de i para j.\n");
    printf("Digite 0 para trechos inexistentes.\n");
    
    for (i = 0; i < M; i++) {
        printf("Custos da Cidade %d (para cidades 0 a %d): ", i, M - 1);
        for (j = 0; j < M; j++) {
            if (scanf("%d", &custo[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler o elemento (%d, %d) da matriz.\n", i, j);
                return;
            }
        }
    }
    
    // Leitura das cidades de origem (X) e destino (Z)
    printf("\nDigite a Cidade de Origem (X, 0 a %d): ", M - 1);
    if (scanf("%d", &X) != 1) {
        fprintf(stderr, "Erro ao ler a cidade X.\n");
        return;
    }
    
    printf("Digite a Cidade de Destino (Z, 0 a %d): ", M - 1);
    if (scanf("%d", &Z) != 1) {
        fprintf(stderr, "Erro ao ler a cidade Z.\n");
        return;
    }

    // Variáveis para rastrear a melhor rota
    int menor_custo = INT_MAX;
    int cidade_intermediaria = -1; 
    
    // Verificação do caminho DIRETO: X -> Z
    // Custo > 0 indica que a passagem existe
    if (custo[X][Z] > 0) {
        menor_custo = custo[X][Z];
    }

    // Verificação dos caminhos com 1 INTERMEDIÁRIA: X -> Y -> Z
    for (Y = 0; Y < M; Y++) {
        
        // Y não pode ser X ou Z
        if (Y == X || Y == Z) {
            continue; 
        }

        int custo_xy = custo[X][Y];
        int custo_yz = custo[Y][Z];
        
        // Verifica se ambos os trechos existem (custo > 0)
        if (custo_xy > 0 && custo_yz > 0) {
            
            int custo_total = custo_xy + custo_yz;
            
            // Verifica se esta rota é mais barata
            if (custo_total < menor_custo) {
                menor_custo = custo_total;
                cidade_intermediaria = Y; 
            }
        }
    }

    // Impressão do Resultado
    printf("\n--- MELHOR ROTA ENCONTRADA ---\n");
    if (menor_custo == INT_MAX) {
        printf("Nenhuma rota valida (direta ou com 1 intermediaria) encontrada.\n");
    } else {
        // Imprime a rota (caminho)
        printf("Caminho mais barato: ");
        if (cidade_intermediaria == -1) {
            // Rota Direta X -> Z
            printf("%d-%d\n", X, Z);
        } else {
            // Rota com Intermediária X -> Y -> Z
            printf("%d-%d-%d\n", X, cidade_intermediaria, Z);
        }
        printf("Custo Total: R$%d\n", menor_custo);
        printf("Saida Formatada: %d", X);
        if (cidade_intermediaria != -1) {
            printf("-%d", cidade_intermediaria);
        }
        printf("-%d R$%d\n", Z, menor_custo);
    }
}

/**
 * @brief Função principal
 */
int main() {
    encontrar_pechincha();
    
    // Pausa para visualização no console do Visual Studio
    printf("\nPressione ENTER para fechar...");
    getchar(); // Limpa o buffer
    getchar(); // Espera a tecla ENTER
    
    return 0;
}