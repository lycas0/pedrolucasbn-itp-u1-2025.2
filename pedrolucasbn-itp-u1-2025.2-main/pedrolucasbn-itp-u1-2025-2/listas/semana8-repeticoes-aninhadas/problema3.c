#include <stdio.h>

// Função principal
int main() {
    int n; // Quantidade de pilotos
    
    // Leitura da Quantidade de Pilotos (n)
    printf("Digite a quantidade de pilotos (n, 1 <= n <= 20):\n");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Erro na leitura de n.\n");
        return 1;
    }

    if (n < 1 || n > 20) {
        printf("Valor de n fora do intervalo especificado.\n");
        return 0;
    }

    // Pilotos são identificados pelos números de 1 a n.
    // Usaremos arrays de tamanho n+1 para usar o índice 1 a n, facilitando o mapeamento.
    // Ex: pos_largada[P] armazena a posição de largada do piloto P.

    // Vetor para armazenar a POSIÇÃO DE LARGADA de cada PILOTO.
    // O valor em pos_largada[i] é a posição de largada do piloto 'i'.
    // pos_largada[piloto] = posicao_largada
    int pos_largada[n + 1]; 
    
    // Vetor para armazenar a POSIÇÃO DE CHEGADA de cada PILOTO.
    // pos_chegada[piloto] = posicao_chegada
    // Não é estritamente necessário um vetor, mas simplifica a leitura.
    int pos_chegada[n + 1]; 

    
    // Leitura da Ordem de Largada e Mapeamento da Posição
    // A entrada fornece o piloto que está em cada posição (ordem de largada).
    printf("Digite a ordem de largada (n inteiros, do 1o ao n-esimo):\n");
    for (int posicao = 1; posicao <= n; posicao++) {
        int piloto;
        if (scanf("%d", &piloto) != 1) {
            fprintf(stderr, "Erro na leitura do piloto na largada.\n");
            return 1;
        }
        // Mapeamento: a posição de largada do 'piloto' é a 'posicao' atual.
        // Exemplo: se o 1º lido é 2, então pos_largada[2] = 1.
        pos_largada[piloto] = posicao;
    }
    
    // Leitura da Ordem de Chegada e Mapeamento da Posição
    // A entrada fornece o piloto que está em cada posição (ordem de chegada).
    printf("Digite a ordem de chegada (n inteiros, do 1o ao n-esimo):\n");
    for (int posicao = 1; posicao <= n; posicao++) {
        int piloto;
        if (scanf("%d", &piloto) != 1) {
            fprintf(stderr, "Erro na leitura do piloto na chegada.\n");
            return 1;
        }
        // Mapeamento: a posição de chegada do 'piloto' é a 'posicao' atual.
        // Exemplo: se o 1º lido é 1, então pos_chegada[1] = 1.
        pos_chegada[piloto] = posicao;
    }

    // Cálculo do Ganho Máximo e Identificação do Piloto
    
    int max_ganho = -n; // Inicializa com o pior ganho possível (largar em 1, chegar em n)
    int piloto_ganhador = -1; // Armazena o ID do piloto com o ganho máximo
    int empates = 0; // Contador para verificar se há empate no ganho máximo

    // Laço Externo: Percorre todos os pilotos (de 1 a n) para calcular o ganho.
    for (int i = 1; i <= n; i++) {
        // Ganho = Posição de Largada - Posição de Chegada
        // Um valor positivo é um ganho de posições (melhorou).
        // Um valor negativo é uma perda de posições (piorou).
        int ganho = pos_largada[i] - pos_chegada[i];
        
        if (ganho > max_ganho) {
            // Novo ganho máximo encontrado
            max_ganho = ganho;
            piloto_ganhador = i;
            empates = 0; // Zera o contador, pois o ganho atual é estritamente maior
        } else if (ganho == max_ganho) {
            // Empate com o ganho máximo atual
            empates++;
        }
    }
    
    // Saída do Resultado

    // A condição 'piloto_ganhador == -1' nunca deve ser atingida se n >= 1
    // A condição 'max_ganho <= 0' verifica se o ganho máximo foi 0 ou negativo.
    if (max_ganho <= 0 || empates > 0) {
        printf("Output:\nempate\n");
    } else {
        // Se max_ganho > 0 e não houve empate, imprime o piloto
        printf("Output:\n%d\n", piloto_ganhador);
    }

    return 0;
}