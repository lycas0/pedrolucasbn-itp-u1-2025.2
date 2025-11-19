#include <stdio.h>
#include <stdlib.h> // Para malloc, realloc, free
#include <string.h> // Para funções de string (strcpy, etc.)
#include <stdbool.h>

// --- DEFINIÇÕES E CONSTANTES ---
#define MAX_NOME 50
#define NOME_ARQUIVO "estoque.dat"
#define CAPACIDADE_INICIAL 10 // Capacidade inicial do vetor dinâmico.

// Definição da Estrutura (Produto)
typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

// --- PROTÓTIPOS DE FUNÇÕES ---
void menu_principal();
void limpar_buffer();
void listar_estoque(const Produto *estoque, int num_produtos); 

// Funções de Lógica do Estoque
int buscar_indice_por_id(const Produto *estoque, int num_produtos, int id_procurado);
bool realizar_desconto(Produto *estoque, int indice_produto, int qtd_venda, float *subtotal);

// Persistência de Dados (U2: I/O de Arquivo, Alocação Dinâmica)
Produto* carregar_estoque(int *num_produtos, int *capacidade_atual);
bool salvar_estoque(const Produto *estoque, int num_produtos);


// --- MAIN (COM ALOCAÇÃO DINÂMICA) ---
int main() {
    // VARIÁVEIS PRINCIPAIS (ALOCADAS DINAMICAMENTE)
    Produto *estoque = NULL; 
    int num_produtos = 0;    
    int capacidade_atual = 0; 
    int opcao;

    // Tenta CARREGAR O ESTOQUE SALVO (malloc/realloc)
    estoque = carregar_estoque(&num_produtos, &capacidade_atual);
    
    if (num_produtos == 0) {
        printf("\nNenhum estoque salvo encontrado. Inicializando sistema com capacidade base.\n");
    }

    // Estrutura de Repetição Principal (do-while)
    do {
        menu_principal();
        
        // Tratamento de entrada (U1: Comandos Condicionais)
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite apenas números.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer();

        // Comandos Condicionais (switch)
        switch (opcao) {
            case 1:
                listar_estoque(estoque, num_produtos);
                break;
            case 2:
                // LÓGICA DO CARRINHO DE COMPRAS
                {
                    int id_venda, qtd_venda, indice_produto;
                    int continuar = 1; 
                    float total_compra = 0.0;
                    float subtotal_item = 0.0;

                    printf("\n--- INICIANDO NOVA VENDA ---\n");
                    
                    // Estrutura de Repetição Aninhada (while dentro de do-while)
                    while (continuar == 1) {
                        printf("\n------------------------------------\n");
                        printf("Digite o ID do produto: ");
                        if (scanf("%d", &id_venda) != 1) {
                            printf("ID inválido.\n");
                            limpar_buffer();
                            continue;
                        }
                        limpar_buffer();
                        
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

                            // Passagem por Referência (Ponteiros)
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
                    } 
                    
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
            case 0:
                printf("Tentando salvar estoque...\n");
                // SALVA O ESTOQUE E LIBERA A MEMÓRIA
                if (salvar_estoque(estoque, num_produtos)) {
                    printf("Estoque salvo em %s.\n", NOME_ARQUIVO);
                } else {
                    printf("Erro ao salvar o estoque.\n");
                }
                if (estoque != NULL) {
                    free(estoque); // U2: free() para evitar memory leaks
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

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Retorna o índice do produto ou -1 se não encontrar (U1: Funções, Vetores)
int buscar_indice_por_id(const Produto *estoque, int num_produtos, int id_procurado) {
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i].id == id_procurado) {
            return i;
        }
    }
    return -1;
}

// Realiza o desconto e calcula o subtotal (U1: Passagem por Referência)
bool realizar_desconto(Produto *estoque, int indice_produto, int qtd_venda, float *subtotal) {
    if (estoque[indice_produto].quantidade >= qtd_venda) {
        estoque[indice_produto].quantidade -= qtd_venda;
        *subtotal = estoque[indice_produto].preco * qtd_venda;
        return true;
    } else {
        return false;
    }
}

// Lista o estoque atual (U1: Estruturas, Funções)
void listar_estoque(const Produto *estoque, int num_produtos) {
    printf("\n======================== ESTOQUE ATUAL ========================\n");
    printf("| ID  | Nome do Produto               | Preço (R$) | Quantidade |\n");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < num_produtos; i++) {
        printf("| %-3d | %-30s| %-10.2f | %-10d |\n", 
               estoque[i].id, 
               estoque[i].nome, 
               estoque[i].preco, 
               estoque[i].quantidade);
    }
    printf("===============================================================\n\n");
}


// NOVO: Carrega o estoque de um arquivo (U2: malloc, realloc, I/O, Strings)
Produto* carregar_estoque(int *num_produtos, int *capacidade_atual) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        // Arquivo não existe: Aloca a capacidade inicial e popula com dados de demonstração
        *capacidade_atual = CAPACIDADE_INICIAL;
        *num_produtos = 0;
        Produto *estoque_vazio = (Produto *)malloc(*capacidade_atual * sizeof(Produto));
        
        if (estoque_vazio == NULL) {
            printf("ERRO: Falha na alocação de memória inicial.\n");
            exit(EXIT_FAILURE);
        }
        
        printf("INFO: Inicializando estoque de demonstração...\n");
    // 5 produtos de exemplo
    estoque_vazio[0] = (Produto){101, "Refrigerante Cola (Lata)", 4.00, 120};
    estoque_vazio[1] = (Produto){102, "Salgadinho Queijo", 1.50, 80};
    estoque_vazio[2] = (Produto){103, "Chocolate ao Leite", 6.25, 60};
    estoque_vazio[3] = (Produto){104, "Água Mineral (500ml)", 2.00, 200};
    estoque_vazio[4] = (Produto){105, "Cerveja Pilsen (Lata)", 4.50, 150};
    
    *num_produtos = 5; 
        
        return estoque_vazio;
    }

    // Arquivo existe: Lê dados
    *capacidade_atual = CAPACIDADE_INICIAL;
    *num_produtos = 0;
    Produto *estoque = (Produto *)malloc(*capacidade_atual * sizeof(Produto));

    if (estoque == NULL) {
        printf("ERRO: Falha na alocação de memória para carregamento.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }
    
    int resultado;
    do {
        // Realocação dinâmica
        if (*num_produtos == *capacidade_atual) {
            *capacidade_atual *= 2;
            Produto *novo_estoque = (Produto *)realloc(estoque, *capacidade_atual * sizeof(Produto));
            if (novo_estoque == NULL) {
                printf("ERRO: Falha na realocação durante o carregamento. Lendo até o que foi possível.\n");
                break;
            }
            estoque = novo_estoque;
        }
        
        // Leitura de string e dados do arquivo (fscanf)
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

// NOVO: Salva o estoque no arquivo (U2: I/O, Strings)
bool salvar_estoque(const Produto *estoque, int num_produtos) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        return false;
    }
    
    for (int i = 0; i < num_produtos; i++) {
        // Escrita de string e dados no arquivo (fprintf)
        fprintf(arquivo, "%d;%s;%.2f;%d\n", 
                estoque[i].id, 
                estoque[i].nome, 
                estoque[i].preco, 
                estoque[i].quantidade);
    }
    
    fclose(arquivo);
    return true;
}


// Funções de Menu (Sem a opção de Gerenciamento)
void menu_principal() {
    printf("\n==== SUPER CONVENIENCIA 24H ====\n");
    printf("1. Listar Estoque\n");
    printf("2. Iniciar Venda\n");
    printf("0. Sair e Salvar\n"); 
    printf("Escolha uma opção: ");
}