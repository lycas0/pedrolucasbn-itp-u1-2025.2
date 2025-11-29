#include <stdio.h>
#include <stdlib.h> // Para malloc, realloc, free
#include <string.h> // Para funções de string (strcpy, etc.)
#include <stdbool.h>

// --- DEFINIÇÕES E CONSTANTES ---
#define MAX_NOME 50
#define NOME_ARQUIVO "estoque.dat"
#define CAPACIDADE_INICIAL 10 // Capacidade inicial do vetor dinâmico. Pode ser ajustado.

// Definição da Estrutura (Produto)
typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

// Funções de Interface
void menu_principal();
void menu_gerenciamento();
void limpar_buffer();
void listar_estoque(const Produto *estoque, int num_produtos); // Usa const Produto *

// Funções de Lógica do Estoque
int buscar_indice_por_id(const Produto *estoque, int num_produtos, int id_procurado); // Usa const Produto *
bool realizar_desconto(Produto *estoque, int indice_produto, int qtd_venda, float *subtotal);
int gerar_novo_id(const Produto *estoque, int num_produtos); // Para IDs automáticos

// Gerenciamento e Alocação Dinâmica
// ** Ponteiro para Ponteiro (Produto **estoque) e Passagem por Referência
bool adicionar_produto(Produto **estoque, int *num_produtos, int *capacidade_atual);

// NOVOS: Persistência de Dados (I/O de Arquivo)
// ** Uso de Strings e I/O
Produto* carregar_estoque(int *num_produtos, int *capacidade_atual);
bool salvar_estoque(const Produto *estoque, int num_produtos);

// MAIN
int main() {
    // VARIÁVEIS PRINCIPAIS
    Produto *estoque = NULL; // Ponteiro para o vetor dinâmico de produtos
    int num_produtos = 0;    // Contador de produtos atuais
    int capacidade_atual = 0; // Capacidade alocada (U2: Alocação Dinâmica)
    int opcao;

    // CARREGA O ESTOQUE SALVO (U2: I/O de Arquivo)
    estoque = carregar_estoque(&num_produtos, &capacidade_atual);
    
    // Se não carregou nada e a capacidade é 0, inicializa uma capacidade mínima
    if (num_produtos == 0) {
        printf("\nNenhum estoque salvo encontrado. Inicializando sistema com capacidade base.\n");
    }

    // Estrutura de Repetição Principal (do-while)
    do {
        menu_principal();
        
        // Proteção contra loop infinito por entrada inválida
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite apenas números.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer(); // Limpa o buffer após a leitura de números

        // Comando Condicional (switch)
        switch (opcao) {
            case 1:
                listar_estoque(estoque, num_produtos);
                break;
            case 2:
                // ** LÓGICA DO CARRINHO DE COMPRAS (Mesma da U1) **
                // ... (Manter a lógica de venda da U1, mas assegure-se de usar `limpar_buffer()` após as leituras)
                {
                    int id_venda, qtd_venda, indice_produto;
                    int continuar = 1; 
                    float total_compra = 0.0;
                    float subtotal_item = 0.0;

                    printf("\n--- INICIANDO NOVA VENDA ---\n");
                    
                    // Estrutura de Repetição Aninhada (Exemplo: while dentro de do-while)
                    while (continuar == 1) {
                        printf("\n------------------------------------\n");
                        printf("Digite o ID do produto: ");
                        if (scanf("%d", &id_venda) != 1) {
                            printf("ID inválido.\n");
                            limpar_buffer();
                            continue;
                        }
                        limpar_buffer();
                        
                        // Uso de Funções
                        indice_produto = buscar_indice_por_id(estoque, num_produtos, id_venda);

                        if (indice_produto != -1) {
                            printf("--> %s (R$ %.2f) - Estoque: %d\n", estoque[indice_produto].nome, estoque[indice_produto].preco, estoque[indice_produto].quantidade);
                            
                            printf("Digite a quantidade: ");
                            if (scanf("%d", &qtd_venda) != 1 || qtd_venda <= 0) {
                                printf("Quantidade inválida.\n");
                                limpar_buffer();
                                continue;
                            }
                            limpar_buffer();

                            // Uso de Ponteiros (Passagem por Referência)
                            if (realizar_desconto(estoque, indice_produto, qtd_venda, &subtotal_item)) {
                                total_compra += subtotal_item;
                                printf("  Item adicionado: %d x %s = R$ %.2f\n", qtd_venda, estoque[indice_produto].nome, subtotal_item);
                            } else {
                                printf("  ERRO: Estoque insuficiente (%d restantes).\n", estoque[indice_produto].quantidade);
                            }
                        } else {
                            printf("  ERRO: ID %d não encontrado.\n", id_venda);
                        }
                        
                        printf("\nAdicionar mais produtos? (1 - Sim / 0 - Não): ");
                        if (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
                            printf("Opção inválida. Assumindo que você NÃO quer adicionar mais.\n");
                            continuar = 0;
                        }
                        limpar_buffer();
                    } // FIM DO LOOP DO CARRINHO
                    
                    if (total_compra > 0) {
                        printf("\n=========================================\n");
                        printf("  VENDA FINALIZADA COM SUCESSO!\n");
                        printf("  Total: R$ %.2f\n", total_compra);
                        printf("=========================================\n");
                    } else {
                        printf("\nNenhuma venda realizada nesta transação.\n");
                    }
                }
                break;
            case 3:
                // Opção de Gerenciamento (U2: Adicionar Produto)
                menu_gerenciamento();
                
                // Estrutura de Repetição Aninhada (Loop para o Sub-Menu)
                int opcao_gerenciamento;
                if (scanf("%d", &opcao_gerenciamento) != 1) {
                    printf("\nOpção inválida.\n");
                    limpar_buffer();
                    continue;
                }
                limpar_buffer();
                
                if (opcao_gerenciamento == 1) {
                    // Adicionar Produto (U2: Alocação Dinâmica e Ponteiros)
                    if (adicionar_produto(&estoque, &num_produtos, &capacidade_atual)) {
                        printf("\nProduto adicionado com sucesso!\n");
                    }
                } else if (opcao_gerenciamento == 0) {
                    printf("Voltando ao menu principal.\n");
                } else {
                    printf("Opção de gerenciamento inválida.\n");
                }
                break;
            case 0:
                printf("Tentando salvar estoque...\n");
                // SALVA O ESTOQUE E LIBERA A MEMÓRIA
                if (salvar_estoque(estoque, num_produtos)) { // U2: I/O de arquivo
                    printf("Estoque salvo em %s.\n", NOME_ARQUIVO);
                } else {
                    printf("Erro ao salvar o estoque.\n");
                }
                if (estoque != NULL) {
                    free(estoque); // U2: free() - Alocação Dinâmica e Sem Memory Leaks
                }
                printf("Fechando sistema. Volte sempre!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// -------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// -------------------------------------------------------------

// Limpa o buffer de entrada (Necessário após scanf de números/opções)
void limpar_buffer() {
    int c;
    // Laço de Repetição (while)
    while ((c = getchar()) != '\n' && c != EOF);
}

// Retorna o índice do produto ou -1 se não encontrar (U1: Funções, Vetores, Condicionais)
int buscar_indice_por_id(const Produto *estoque, int num_produtos, int id_procurado) {
    // Laço de Repetição (for)
    for (int i = 0; i < num_produtos; i++) {
        // Operação Relacional e Condicional (if)
        if (estoque[i].id == id_procurado) {
            return i;
        }
    }
    return -1;
}

// Tenta gerar um ID único
int gerar_novo_id(const Produto *estoque, int num_produtos) {
    if (num_produtos == 0) return 1001; // ID inicial
    
    int maior_id = 0;
    // Percorre o vetor de produtos dinâmicos (U2: Ponteiros e Arrays)
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i].id > maior_id) {
            maior_id = estoque[i].id;
        }
    }
    return maior_id + 1;
}

// Realiza o desconto e calcula o subtotal (U1: Passagem por Referência - Ponteiros)
bool realizar_desconto(Produto *estoque, int indice_produto, int qtd_venda, float *subtotal) {
    if (estoque[indice_produto].quantidade >= qtd_venda) {
        // Operação Aritmética
        estoque[indice_produto].quantidade -= qtd_venda;
        *subtotal = estoque[indice_produto].preco * qtd_venda;
        return true;
    } else {
        return false;
    }
}

// Lista o estoque atual (U1: Estruturas, Funções, Formatação de Saída)
void listar_estoque(const Produto *estoque, int num_produtos) {
    printf("\n======================== ESTOQUE ATUAL ========================\n");
    printf("| ID  | Nome do Produto               | Preço (R$) | Quantidade |\n");
    printf("---------------------------------------------------------------\n");
    
    // Percorrimento do vetor
    for (int i = 0; i < num_produtos; i++) {
        printf("| %-3d | %-30s| %-10.2f | %-10d |\n", 
               estoque[i].id, 
               estoque[i].nome, 
               estoque[i].preco, 
               estoque[i].quantidade);
    }
    printf("===============================================================\n\n");
}


// NOVO: Adiciona um novo produto ao estoque dinâmico
bool adicionar_produto(Produto **estoque, int *num_produtos, int *capacidade_atual) {
    char nome_temp[MAX_NOME];
    float preco_temp;
    int qtd_temp;

    // Coleta de Dados
    printf("\n--- ADICIONAR NOVO PRODUTO ---\n");
    printf("Nome do Produto (max %d caracteres): ", MAX_NOME - 1);
    // Leitura de String
    if (fgets(nome_temp, MAX_NOME, stdin) == NULL) {
        printf("Erro de leitura.\n");
        return false;
    }
    // U2: Strings - Remove o '\n' lido por fgets, se houver
    nome_temp[strcspn(nome_temp, "\n")] = 0; 

    // Validação de Preço
    printf("Preço (R$): ");
    if (scanf("%f", &preco_temp) != 1 || preco_temp <= 0) {
        printf("Preço inválido.\n");
        limpar_buffer();
        return false;
    }
    // Validação de Quantidade
    printf("Quantidade Inicial: ");
    if (scanf("%d", &qtd_temp) != 1 || qtd_temp < 0) {
        printf("Quantidade inválida.\n");
        limpar_buffer();
        return false;
    }
    limpar_buffer(); // Limpa o buffer após a leitura de números

    // Alocação Dinâmica (U2: Alocação Dinâmica e Ponteiros)
    if (*num_produtos == *capacidade_atual) {
        // Capacidade esgotada, precisamos realocar
        int nova_capacidade = (*capacidade_atual == 0) ? CAPACIDADE_INICIAL : (*capacidade_atual) * 2;
        
        // Uso de realloc
        Produto *novo_estoque = (Produto *)realloc(*estoque, nova_capacidade * sizeof(Produto));
        
        // U2: Verificação de Alocação Bem-Sucedida
        if (novo_estoque == NULL) {
            printf("ERRO: Falha na alocação de memória (realloc).\n");
            return false;
        }
        
        *estoque = novo_estoque;
        *capacidade_atual = nova_capacidade;
        printf("INFO: Estoque realocado para %d posições.\n", *capacidade_atual);
    }

    // Inserção
    Produto novo_produto;
    novo_produto.id = gerar_novo_id(*estoque, *num_produtos);
    // U2: Strings - strcpy
    strcpy(novo_produto.nome, nome_temp); 
    novo_produto.preco = preco_temp;
    novo_produto.quantidade = qtd_temp;
    
    // Adiciona o produto na próxima posição livre (U2: Ponteiros e Arrays)
    (*estoque)[*num_produtos] = novo_produto;
    (*num_produtos)++;
    
    return true;
}

// NOVO: Carrega o estoque de um arquivo (U2: I/O de Arquivo, Strings, Ponteiros)
Produto* carregar_estoque(int *num_produtos, int *capacidade_atual) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir, aloca a capacidade inicial
        *capacidade_atual = CAPACIDADE_INICIAL;
        *num_produtos = 0;
        // U2: malloc()
        Produto *estoque_vazio = (Produto *)malloc(*capacidade_atual * sizeof(Produto));
        
        if (estoque_vazio == NULL) {
            printf("ERRO: Falha na alocação de memória inicial.\n");
            exit(EXIT_FAILURE); // Saída em caso de erro crítico de memória
        }
        return estoque_vazio;
    }

    // Inicializa com capacidade para ler os dados
    *capacidade_atual = CAPACIDADE_INICIAL;
    *num_produtos = 0;
    Produto *estoque = (Produto *)malloc(*capacidade_atual * sizeof(Produto));

    if (estoque == NULL) {
        printf("ERRO: Falha na alocação de memória para carregamento.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }
    
    int resultado;
    // Loop para ler todos os produtos
    do {
        // Se a capacidade foi atingida, realoca
        if (*num_produtos == *capacidade_atual) {
            *capacidade_atual *= 2;
            Produto *novo_estoque = (Produto *)realloc(estoque, *capacidade_atual * sizeof(Produto));
            if (novo_estoque == NULL) {
                printf("ERRO: Falha na realocação durante o carregamento. Lendo até o que foi possível.\n");
                break;
            }
            estoque = novo_estoque;
        }
        
        // U2: Strings (sscanf do arquivo)
        resultado = fscanf(arquivo, "%d;%49[^;];%f;%d\n", 
                           &estoque[*num_produtos].id, 
                           estoque[*num_produtos].nome, 
                           &estoque[*num_produtos].preco, 
                           &estoque[*num_produtos].quantidade);
        
        if (resultado == 4) {
            (*num_produtos)++;
        }
    } while (resultado == 4);
    
    fclose(arquivo);
    printf("Estoque carregado: %d produtos encontrados.\n", *num_produtos);
    return estoque;
}

// NOVO: Salva o estoque no arquivo (U2: I/O de Arquivo, Strings)
bool salvar_estoque(const Produto *estoque, int num_produtos) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        return false;
    }
    
    // Percorre o vetor de produtos
    // Laço de Repetição (for)
    for (int i = 0; i < num_produtos; i++) {
        // U2: Strings (fprintf para arquivo)
        fprintf(arquivo, "%d;%s;%.2f;%d\n", 
                estoque[i].id, 
                estoque[i].nome, 
                estoque[i].preco, 
                estoque[i].quantidade);
    }
    
    fclose(arquivo);
    return true;
}


// Funções de Menu (Mantidas, com nova opção)
void menu_principal() {
    printf("\n==== SUPER CONVENIENCIA 24H ====\n");
    printf("1. Listar Estoque\n");
    printf("2. Iniciar Venda\n");
    printf("3. Gerenciamento do Estoque\n"); // NOVA OPÇÃO
    printf("0. Sair e Salvar\n");
    printf("Escolha uma opção: ");
}

void menu_gerenciamento() {
    printf("\n--- GERENCIAMENTO DO ESTOQUE ---\n");
    printf("1. Adicionar Novo Produto\n");
    printf("0. Voltar\n");
    printf("Escolha uma opção: ");
}