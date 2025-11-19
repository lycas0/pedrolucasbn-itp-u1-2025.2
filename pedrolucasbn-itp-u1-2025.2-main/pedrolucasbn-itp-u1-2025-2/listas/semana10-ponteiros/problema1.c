#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Aloca dinamicamente um vetor de 'n' inteiros.
 * @param n O tamanho do vetor a ser alocado.
 * @return int* O ponteiro para o novo vetor alocado, ou NULL em caso de falha.
 */
int* alocarVetor(int n) {
    if (n <= 0) return NULL;
    return (int*) malloc(n * sizeof(int));
}

/**
 * @brief Soma dois vetores se tiverem a mesma dimensão.
 * @param u Primeiro vetor.
 * @param v Segundo vetor.
 * @param n1 Dimensão do vetor u.
 * @param n2 Dimensão do vetor v.
 * @return int* O vetor resultante da soma (alocado dinamicamente), ou NULL se dimensões forem incompatíveis.
 */
int* somaVetores(int *u, int *v, int n1, int n2) {
    // Verifica compatibilidade das dimensões
    if (n1 != n2 || n1 <= 0) {
        return NULL;
    }

    int n = n1; // Dimensão comum
    
    // Aloca o vetor resultante
    int *resultado = alocarVetor(n);
    if (resultado == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o vetor soma.\n");
        return NULL;
    }

    // Realiza a soma elemento por elemento
    for (int i = 0; i < n; i++) {
        resultado[i] = u[i] + v[i];
    }

    return resultado;
}

/**
 * @brief Lê 'n' inteiros do usuário para preencher um vetor.
 * @param vetor O vetor a ser preenchido.
 * @param n O número de elementos a serem lidos.
 * @param nome O nome do vetor para o prompt (e.g., "u" ou "v").
 */
void lerNInteiros(int *vetor, int n, char *nome) {
    printf("Digite os %d inteiros para o vetor %s, separados por espacos: ", n, nome);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &vetor[i]) != 1) {
            fprintf(stderr, "Erro ao ler elemento do vetor %s.\n", nome);
            // Poderia adicionar um tratamento de erro mais robusto aqui
            exit(1);
        }
    }
}

/**
 * @brief Função principal para o problema "Soma de Vetores".
 */
int main() {
    int n1, n2;
    int *u = NULL;
    int *v = NULL;
    int *soma = NULL;
    int i;

    printf("Programa Soma de Vetores\n");

    // Leitura interativa das dimensões n1 e n2
    printf("Digite a dimensao do vetor u (n1) e do vetor v (n2), separados por espaco: ");
    if (scanf("%d %d", &n1, &n2) != 2 || n1 <= 0 || n2 <= 0) {
        fprintf(stderr, "Entrada de dimensoes invalida.\n");
        goto cleanup;
    }

    // Alocar dinamicamente os vetores u e v
    u = alocarVetor(n1);
    v = alocarVetor(n2);

    if (u == NULL || v == NULL) {
        fprintf(stderr, "Falha na alocacao de memoria.\n");
        goto cleanup;
    }

    // Ler n1 inteiros para u e n2 inteiros para v
    lerNInteiros(u, n1, "u");
    lerNInteiros(v, n2, "v");

    // Chamar a função somaVetores
    soma = somaVetores(u, v, n1, n2);

    // Escrever o resultado
    printf("\nSAIDA: ");
    if (soma == NULL) {
        // Dimensões incompatíveis ou falha na alocação
        if (n1 != n2) {
            printf("dimensoes incompatíveis\n"); //
        } else {
            printf("Erro interno de soma.\n");
        }
    } else {
        // Imprime o vetor resultante
        for (i = 0; i < n1; i++) {
            printf("%d", soma[i]);
            if (i < n1 - 1) {
                printf(" ");
            }
        }
        printf("\n");
        // Libera a memória do vetor resultante
        free(soma);
    }

cleanup:
    // Libera a memória dos vetores principais
    if (u != NULL) free(u);
    if (v != NULL) free(v);

    printf("\nPressione ENTER para fechar...");
    getchar(); // Limpa o buffer
    getchar(); // Espera a tecla ENTER

    return 0;
}