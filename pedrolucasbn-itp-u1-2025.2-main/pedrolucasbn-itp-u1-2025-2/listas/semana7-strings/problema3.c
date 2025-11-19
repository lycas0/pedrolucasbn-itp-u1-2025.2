#include <stdio.h>
#include <string.h>

// Tamanhos definidos conforme o problema:
// Nome do aluno: max 10 caracteres + '\0'
#define MAX_NOME 11
// Relatório de frequências: max 1000 caracteres + '\0'
#define MAX_RELATORIO 1001

// Função para verificar se um token é uma data no formato DD/MM
// A verificação é simplificada, assume que o formato é sempre 5 caracteres (DD/MM)
int is_date(const char *token) {
    if (strlen(token) != 5) {
        return 0;
    }
    // Verifica se os caracteres são dígitos e se o separador é '/'
    // (Poderia ser mais robusta, mas para este problema, é suficiente)
    if (token[2] == '/') {
        return 1;
    }
    return 0;
}

int main() {
    char nome_aluno[MAX_NOME];
    char relatorio[MAX_RELATORIO];
    
    // Leitura das Entradas
    
    // Ler o nome do aluno que será pesquisado
    printf("Digite o nome do aluno (max 10 chars): ");
    // Lê no máximo MAX_NOME - 1 caracteres para o nome do aluno
    if (scanf("%10s", nome_aluno) != 1) {
        fprintf(stderr, "Erro ao ler o nome do aluno.\n");
        return 1;
    }
    
    // Limpar o buffer de entrada (após o scanf, o '\n' fica no buffer)
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Ler a string completa do relatório de frequências
    printf("Digite o relatorio de presenca (max 1000 chars):\n");
    // Usar fgets para ler a linha inteira, incluindo espaços
    if (fgets(relatorio, MAX_RELATORIO, stdin) == NULL) {
        fprintf(stderr, "Erro ao ler o relatorio.\n");
        return 1;
    }

    // Remover o '\n' que o fgets adiciona no final da string, se estiver presente
    size_t len = strlen(relatorio);
    if (len > 0 && relatorio[len - 1] == '\n') {
        relatorio[len - 1] = '\0';
    }
    
    // Processamento do Relatório
    
    int aulas_ausentes = 0;
    int aluno_presente_na_aula = 0;
    int nova_aula = 1; // Flag para indicar que um novo bloco de aula está começando
    
    char *token;
    // O delimitador é o espaço (' ')
    const char delimitador[] = " ";

    // Inicia a tokenização (divide a string do relatório usando o espaço)
    token = strtok(relatorio, delimitador);

    // Loop para processar cada token
    while (token != NULL) {
        
        // VERIFICAR SE O TOKEN É UMA DATA (Início de uma nova aula)
        if (is_date(token)) {
            // Se encontrou uma data, a aula anterior terminou.
            // Se a flag 'nova_aula' for 0, significa que a aula anterior não tinha o aluno.
            if (nova_aula == 0) {
                // Se a aula anterior não registrou o aluno, ele estava ausente.
                aulas_ausentes++;
            }
            
            // Inicia uma nova aula:
            nova_aula = 0; // Por padrão, o aluno está ausente (ausência só é cancelada se for encontrado)
            aluno_presente_na_aula = 0; // Reinicia a flag de presença para a nova aula
            
        } 
        
        // VERIFICAR SE O TOKEN É O NOME DO ALUNO
        else if (strcmp(token, nome_aluno) == 0) {
            // Se o nome do aluno foi encontrado
            aluno_presente_na_aula = 1; // O aluno foi encontrado nesta aula.
            nova_aula = 1; // Usa esta flag para indicar que a próxima data não deve contar ausência.
        }
        
        // Continua para o próximo token
        token = strtok(NULL, delimitador);
    }
    
    // Tratamento da ÚLTIMA AULA
    // Após o loop, o último bloco de aula ainda precisa ser verificado.
    // Se a última aula não encontrou o aluno (aluno_presente_na_aula == 0)
    // E a flag nova_aula não foi setada (o aluno não foi encontrado *após* a última data),
    // é porque ele estava ausente na última aula.
    if (nova_aula == 0 && aluno_presente_na_aula == 0) {
        aulas_ausentes++;
    }
    
    // Saída
    printf("%d\n", aulas_ausentes);

    return 0;
}