#include <stdio.h>
#include <stdlib.h>

// Define a constante para o tamanho máximo da matriz
#define MAX_USUARIOS 100

/**
 * @brief Resolve o problema de Sugestão de Amigos, identificando usuários com amigos em comum.
 * * A lógica é: para cada usuário 'j' que não é amigo do usuário 'x',
 * verifica se existe um usuário 'k' tal que 'k' é amigo de 'x' E 'k' é amigo de 'j'.
 */
void sugerir_amigos() {
    int M;
    int x; // Usuário de referência (1-based)
    int i, j, k;

    // Torna a leitura do número de usuários (M) interativa
    printf("\nPrograma de Sugestao de Amigos\n");
    printf("Digite o numero total de usuarios (M, max: %d): ", MAX_USUARIOS);
    
    if (scanf("%d", &M) != 1) {
        fprintf(stderr, "Erro ao ler o numero de usuarios M.\n");
        return;
    }

    // Verifica a restrição de tamanho
    if (M < 1 || M > MAX_USUARIOS) {
        fprintf(stderr, "Erro: M deve estar entre 1 e %d.\n", MAX_USUARIOS);
        return;
    }

    // Declaração da matriz de adjacência
    int amizades[MAX_USUARIOS][MAX_USUARIOS];

    // Torna a leitura da matriz de amizades (M x M) interativa
    printf("\nDigite a matriz de amizades (%d x %d):\n", M, M);
    printf("1 se sao amigos, 0 se nao sao.\n");
    printf("Digite os valores linha por linha, separados por espacos.\n");
    
    for (i = 0; i < M; i++) {
        printf("Linha %d (amizades do usuario %d): ", i, i + 1);
        for (j = 0; j < M; j++) {
            if (scanf("%d", &amizades[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler o elemento (%d, %d) da matriz.\n", i, j);
                return;
            }
        }
    }
    
    // Torna a leitura do usuário de referência (x) interativa
    printf("\nDigite o numero do usuario de referencia (X, entre 1 e %d): ", M);
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Erro ao ler o usuario de referencia X.\n");
        return;
    }
    
    // Ajusta o índice do usuário X para 0-base
    int usuario_x_idx = x - 1;

    // Verifica se o usuário X está nos limites da matriz
    if (usuario_x_idx < 0 || usuario_x_idx >= M) {
        fprintf(stderr, "Erro: Usuario de referencia X fora dos limites (1 a %d).\n", M);
        return;
    }
    
    // Cálculo de sugestão
    int primeira_sugestao = 1; 
    int sugestoes_encontradas = 0;

    printf("\n--- SUGESTOES PARA O USUARIO %d ---\n", x);

    // Iteramos por todos os usuários 'j' (índice 0 a M-1)
    for (j = 0; j < M; j++) {
        
        // Verifica se j é o próprio x OU se já são amigos.
        if (j == usuario_x_idx || amizades[usuario_x_idx][j] == 1) {
            continue; 
        }

        // Verifica se existe pelo menos um amigo em comum.
        for (k = 0; k < M; k++) {
            
            // Verifica se 'k' é amigo de 'x' E 'k' é amigo de 'j'.
            if (amizades[usuario_x_idx][k] == 1 && amizades[j][k] == 1) {
                
                // Passo C: Se encontrou pelo menos um amigo em comum, 'j' é uma sugestão.
                
                // Impressão da sugestão (j+1 para retornar ao formato 1-base do usuário)
                if (!primeira_sugestao) {
                    printf(" "); 
                }
                printf("%d", j + 1);
                primeira_sugestao = 0; 
                sugestoes_encontradas++;
                
                break; // Encontrou 1 amigo em comum, é o suficiente.
            }
        }
    }
    
    // Adiciona uma nova linha para formatação e mensagem de "nenhuma sugestão"
    if (sugestoes_encontradas == 0) {
        printf("Nenhuma sugestao encontrada.");
    }
    
    printf("\n");
}

/**
 * @brief Função principal
 */
int main() {
    sugerir_amigos();
    
    // Pausa para visualização no console do Visual Studio
    printf("\nPressione ENTER para fechar...");
    getchar(); // Limpa o buffer de entrada
    getchar(); // Espera a tecla ENTER
    
    return 0;
}