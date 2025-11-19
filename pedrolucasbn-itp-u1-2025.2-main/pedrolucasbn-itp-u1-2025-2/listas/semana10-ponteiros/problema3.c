#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strlen e operações com strings

// Define o tamanho máximo das strings de entrada
#define MAX_STR_LEN 100

/**
 * @brief Cria uma nova string alocada dinamicamente, alternando os caracteres das duas strings de entrada.
 * @param str1 Primeira string.
 * @param str2 Segunda string.
 * @return char* A nova string misturada (deve ser liberada pelo chamador).
 */
char* misturar(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int total_len = len1 + len2;
    int i;
    int k = 0; // Índice da nova string
    
    // Alocação dinâmica da nova string
    // O tamanho é a soma dos comprimentos + 1 para o terminador nulo '\0'.
    char *nova_string = (char*) malloc((total_len + 1) * sizeof(char));
    
    if (nova_string == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria na funcao misturar.\n");
        return NULL;
    }

    // Mistura alternada dos caracteres
    // O loop continua enquanto houver caracteres em pelo menos uma das strings.
    for (i = 0; i < total_len; i++) {
        
        // Se a primeira string ainda tiver caracteres, adiciona um.
        if (i < len1) {
            nova_string[k++] = str1[i];
        }
        
        // Se a segunda string ainda tiver caracteres, adiciona um.
        if (i < len2) {
            nova_string[k++] = str2[i];
        }
        
        // Nota: A lógica de alternância é feita a cada iteração 'i' do loop, 
        // pegando um caractere de str1 e um de str2 (se existirem).
    }
    
    // Adiciona o terminador nulo
    nova_string[total_len] = '\0';

    return nova_string;
}

/**
 * @brief Função principal para o problema "Sopa de letrinhas".
 */
int main() {
    char str1[MAX_STR_LEN + 1];
    char str2[MAX_STR_LEN + 1];
    char *resultado = NULL;
    
    printf("Programa Sopa de Letrinhas\n");
    
    // Leitura interativa da primeira string
    printf("Digite a primeira string (max %d caracteres): ", MAX_STR_LEN);
    // Usamos scanf com [%^\n] para ler a linha inteira, incluindo espaços, e limita o tamanho
    if (scanf("%100[^\n]", str1) != 1) {
        fprintf(stderr, "Erro ao ler a primeira string.\n");
        return 1;
    }
    // Limpa o buffer de entrada
    while(getchar() != '\n'); 

    // Leitura interativa da segunda string
    printf("Digite a segunda string (max %d caracteres): ", MAX_STR_LEN);
    if (scanf("%100[^\n]", str2) != 1) {
        fprintf(stderr, "Erro ao ler a segunda string.\n");
        return 1;
    }
    // Limpa o buffer de entrada
    while(getchar() != '\n'); 

    // Chamada da função de mistura
    resultado = misturar(str1, str2);

    // Impressão do resultado
    printf("\n--- RESULTADO DA MISTURA ---\n");
    if (resultado != NULL) {
        printf("SAIDA: %s\n", resultado);
        
        // Liberação da memória alocada dinamicamente
        free(resultado);
    } else {
        printf("Erro ao processar as strings.\n");
    }
    
    printf("\nPressione ENTER para fechar...");
    getchar(); // Espera a tecla ENTER
    
    return 0;
}