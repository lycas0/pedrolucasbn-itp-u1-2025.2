#include <stdio.h>
#include <string.h>

// Definindo a Estrutura (Struct) para armazenar Mês e Chuva
typedef struct {
    char mes[20]; // Nome do mês (ex: "Janeiro")
    int chuva;    // Quantidade de chuva (inteiro)
} RegistroChuva;

// Função de Ordenação: Insertion Sort
// Ordena o array 'arr' em ordem DECRESCENTE (do maior para o menor)
void insertionSort(RegistroChuva arr[], int n) {
    int i, j;
    RegistroChuva chave;

    // Começa do segundo elemento (i = 1)
    for (i = 1; i < n; i++) {
        // 'chave' é o elemento que queremos inserir na parte ordenada
        chave = arr[i];
        j = i - 1;

        // Move os elementos da parte ordenada que são MENORES que 'chave'
        // uma posição para a frente para criar o "buraco" de inserção.
        // A comparação 'arr[j].chuva < chave.chuva' garante a ordem decrescente.
        while (j >= 0 && arr[j].chuva < chave.chuva) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // Insere a chave na posição correta
        arr[j + 1] = chave;
    }
}

int main() {
    const char *nomes_meses[] = {
        "Janeiro", "Fevereiro", "Marco", "Abril", 
        "Maio", "Junho", "Julho", "Agosto", 
        "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    // Array de 12 estruturas, uma para cada mês
    RegistroChuva dados[12];
    int i;
    int leitura_chuva[12];
    
    // Leitura dos 12 valores de chuva
    printf("Digite os 12 inteiros de chuva (Janeiro a Dezembro):\n");
    for (i = 0; i < 12; i++) {
        if (scanf("%d", &leitura_chuva[i]) != 1) {
            fprintf(stderr, "Erro na leitura do valor de chuva.\n");
            return 1;
        }
    }
    
    // Inicialização da Estrutura
    for (i = 0; i < 12; i++) {
        // Copia o nome do mês
        strcpy(dados[i].mes, nomes_meses[i]);
        // Associa o valor de chuva lido
        dados[i].chuva = leitura_chuva[i];
    }

    // Ordenação
    // Chama o Insertion Sort para ordenar os 12 registros por quantidade de chuva (Decrescente)
    insertionSort(dados, 12);

    // Escrita do Ranking (Output)
    printf("\nOutput (Ranking de Chuva):\n");
    for (i = 0; i < 12; i++) {
        printf("%s %d\n", dados[i].mes, dados[i].chuva);
    }

    return 0;
}