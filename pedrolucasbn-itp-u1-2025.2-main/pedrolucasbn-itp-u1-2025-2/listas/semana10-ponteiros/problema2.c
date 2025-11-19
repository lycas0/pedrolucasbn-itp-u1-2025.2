#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Busca todas as ocorrências de um 'valor' em um vetor 'v'.
 * * @param v Endereço base do vetor de inteiros.
 * @param n Quantidade de inteiros no vetor.
 * @param valor Valor inteiro a ser buscado.
 * @param maior Ponteiro para armazenar o maior número encontrado (não implementado neste problema, mas requerido na assinatura).
 * @param qtd Ponteiro para armazenar a quantidade de ocorrências encontradas.
 * @return int* Um novo vetor alocado dinamicamente contendo os índices das ocorrências, 
 * ou NULL se nenhuma ocorrência for encontrada.
 */
int* buscaNoVetor(int *v, int n, int valor, int *maior, int *qtd) {
    int count = 0;
    int i;
    
    // Contagem das ocorrências e cálculo do maior valor (para atender a assinatura)
    int max_val = (n > 0) ? v[0] : 0;

    for (i = 0; i < n; i++) {
        if (v[i] == valor) {
            count++;
        }
        if (v[i] > max_val) {
            max_val = v[i];
        }
    }
    
    // Armazena a quantidade de ocorrências no endereço apontado por 'qtd'
    *qtd = count; 
    
    // Armazena o maior valor no endereço apontado por 'maior'
    // Embora não seja o foco, isso atende à assinatura da função.
    *maior = max_val; 

    // Verifica se houve ocorrências
    if (count == 0) {
        return NULL;
    }

    // Alocação dinâmica do vetor de índices
    // Precisamos de 'count' posições para armazenar os índices.
    int *indices = (int*) malloc(count * sizeof(int));
    
    // Tratamento de erro na alocação
    if (indices == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para os indices.\n");
        *qtd = 0; // Se falhar, a quantidade é zero
        return NULL;
    }

    // Preenchimento do vetor de índices
    int indice_atual = 0;
    for (i = 0; i < n; i++) {
        if (v[i] == valor) {
            indices[indice_atual] = i; // Armazena o índice da ocorrência
            indice_atual++;
        }
    }

    return indices; // Retorna o endereço do novo vetor de índices
}

/**
 * @brief Função principal para o problema "Ocorrências no vetor".
 */
int main() {
    int n;
    int i;
    int valor_busca;
    int *vetor_dinamico = NULL;
    
    printf("Programa de Ocorrencias no Vetor\n");
    
    // Leitura interativa da quantidade de elementos (n)
    printf("Digite a quantidade de elementos do vetor (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Entrada invalida para n.\n");
        printf("\nPressione ENTER para fechar...");
        getchar(); 
        getchar(); 
        return 1;
    }
    
    // Alocação dinâmica do vetor de entrada
    vetor_dinamico = (int*) malloc(n * sizeof(int));
    if (vetor_dinamico == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o vetor principal.\n");
        printf("\nPressione ENTER para fechar...");
        getchar(); 
        getchar(); 
        return 1;
    }

    // Leitura interativa dos elementos do vetor
    printf("Digite os %d inteiros do vetor, separados por espacos:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &vetor_dinamico[i]) != 1) {
            fprintf(stderr, "Erro ao ler o elemento %d.\n", i);
            free(vetor_dinamico);
            printf("\nPressione ENTER para fechar...");
            getchar(); 
            getchar(); 
            return 1;
        }
    }
    
    // 4. Leitura interativa do valor a ser buscado
    printf("Digite o valor inteiro a ser buscado no vetor: ");
    if (scanf("%d", &valor_busca) != 1) {
        fprintf(stderr, "Erro ao ler o valor de busca.\n");
        free(vetor_dinamico);
        printf("\nPressione ENTER para fechar...");
        getchar(); 
        getchar(); 
        return 1;
    }

    // Variáveis de retorno indireto
    int qtd_ocorrencias = 0;
    int maior_valor = 0; // Variável 'maior' para cumprir a assinatura
    
    // Chamada da função de busca
    int *indices_ocorrencias = buscaNoVetor(
        vetor_dinamico, 
        n, 
        valor_busca, 
        &maior_valor, // Passando o endereço para o retorno indireto
        &qtd_ocorrencias // Passando o endereço para o retorno indireto (o foco do problema)
    );

    // Impressão do resultado
    printf("\n--- RESULTADO DA BUSCA ---\n");
    
    printf("SAIDA FORMATADA: ");
    if (indices_ocorrencias == NULL) {
        printf("Nenhuma ocorrencia\n");
    } else {
        printf("%d\n", qtd_ocorrencias);
        printf("Indices das ocorrencias: ");
        for (i = 0; i < qtd_ocorrencias; i++) {
            printf("%d", indices_ocorrencias[i]);
            if (i < qtd_ocorrencias - 1) {
                printf(" ");
            }
        }
        printf("\n");

        // Liberação da memória alocada dinamicamente
        free(indices_ocorrencias);
    }
    
    // Liberação da memória do vetor principal
    free(vetor_dinamico);
    
    printf("\nPressione ENTER para fechar...");
    getchar(); // Limpa o buffer
    getchar(); // Espera a tecla ENTER
    
    return 0;
}