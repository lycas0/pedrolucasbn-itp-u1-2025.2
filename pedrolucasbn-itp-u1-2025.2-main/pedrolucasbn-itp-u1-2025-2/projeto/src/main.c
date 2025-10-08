#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Definição da Estrutura (Produto)
#define MAX_NOME 50
#define CAPACIDADE_MAXIMA 100 

typedef struct {
    int id;               
    char nome[MAX_NOME];  
    float preco;          
    int quantidade;       
} Produto;

// Funções
void menu_principal();
void inicializar_estoque(Produto estoque[], int *num_produtos);
void listar_estoque(Produto estoque[], int num_produtos); 
int buscar_indice_por_id(Produto estoque[], int num_produtos, int id_procurado);
bool realizar_desconto(Produto estoque[], int indice_produto, int qtd_venda, float *subtotal);


int main() {
    Produto estoque[CAPACIDADE_MAXIMA]; 
    int num_produtos = 0;
    int opcao;

    inicializar_estoque(estoque, &num_produtos);

    do {
        menu_principal();
        
        // Proteção contra loop infinito por entrada inválida
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite apenas números.\n");
            while (getchar() != '\n');
            opcao = -1; 
            continue;
        }

        switch (opcao) {
            case 1: 
                listar_estoque(estoque, num_produtos);
                break;
            case 2: {
                // LÓGICA DO CARRINHO DE COMPRAS
                int id_venda, qtd_venda, indice_produto;
                int continuar = 1; // 1: Sim, 0: Não
                float total_compra = 0.0; // Acumula o valor total de todos os itens
                float subtotal_item = 0.0;
                
                printf("\n--- INICIANDO NOVA VENDA ---");
                
                // LOOP DO CARRINHO
                while (continuar == 1) {
                    printf("\n------------------------------------\n");
                    printf("Digite o ID do produto e a quantidade: ");
                    // Proteção de entrada (ID)
                    if (scanf("%d", &id_venda) != 1) {
                        printf("ID inválido.\n");
                        while (getchar() != '\n'); 
                        continue;
                    }

                    indice_produto = buscar_indice_por_id(estoque, num_produtos, id_venda);

                    if (indice_produto != -1) {
                        // Produto ENCONTRADO - Exibe o nome e o preço!
                        printf("--> %s (R$ %.2f)\n", estoque[indice_produto].nome, estoque[indice_produto].preco);
                        
                        // Proteção de entrada (Quantidade)
                        if (scanf("%d", &qtd_venda) != 1 || qtd_venda <= 0) {
                            printf("Quantidade inválida.\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        // Tenta realizar o desconto e calcula o subtotal
                        if (realizar_desconto(estoque, indice_produto, qtd_venda, &subtotal_item)) {
                            
                            // Adiciona o subtotal ao total da compra
                            total_compra += subtotal_item;
                            
                            printf("  Item adicionado: %d x %s = R$ %.2f\n", 
                                   qtd_venda, estoque[indice_produto].nome, subtotal_item);
                            
                        } else {
                            printf("  ERRO: Estoque insuficiente (%d restantes).\n", estoque[indice_produto].quantidade);
                        }
                        
                    } else {
                        printf("  ERRO: ID %d não encontrado.\n", id_venda);
                    }
                    
                    // PERGUNTA SE DESEJA ADICIONAR MAIS PRODUTOS
                    printf("\nAdicionar mais produtos? (1 - Sim / 0 - Não): ");
                    // Limpa o buffer antes de ler a nova opção (boa prática)
                    while (getchar() != '\n'); 
                    
                    if (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
                        printf("Opção inválida. Assumindo que você NÃO quer adicionar mais.\n");
                        continuar = 0;
                    }
                } // FIM DO LOOP DO CARRINHO
                
                // SOMAR O VALOR FINAL
                if (total_compra > 0) {
                    printf("\n=========================================\n");
                    printf("  VENDA FINALIZADA COM SUCESSO!\n");
                    printf("  Total: R$ %.2f\n", total_compra);
                    printf("=========================================\n");
                } else {
                    printf("\nNenhuma venda realizada nesta transação.\n");
                }
                
                break;
            }
            case 0:
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

// NOVA FUNÇÃO: Retorna o índice do produto ou -1 se não encontrar
int buscar_indice_por_id(Produto estoque[], int num_produtos, int id_procurado) {
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i].id == id_procurado) {
            return i;
        }
    }
    return -1;
}

// MODIFICADA: Realiza o desconto e calcula o subtotal do item
bool realizar_desconto(Produto estoque[], int indice_produto, int qtd_venda, float *subtotal) {
    
    // Já sabemos que o produto existe (o índice foi encontrado)
    if (estoque[indice_produto].quantidade >= qtd_venda) {
        // ESTOQUE SUFICIENTE: Realiza o Desconto!
        estoque[indice_produto].quantidade -= qtd_venda; 
        
        *subtotal = estoque[indice_produto].preco * qtd_venda;
        return true; // Sucesso
    } else {
        return false; // Estoque insuficiente
    }
}


void listar_estoque(Produto estoque[], int num_produtos) {
    printf("\n======================== ESTOQUE ATUAL ========================\n");
    printf("| ID  | Nome do Produto                 | Preço (R$) | Quantidade |\n");
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


void inicializar_estoque(Produto estoque[], int *num_produtos) {
    // 5 produtos de exemplo
    estoque[0] = (Produto){101, "Refrigerante Cola (Lata)", 4.00, 120};
    estoque[1] = (Produto){102, "Salgadinho Queijo", 1.50, 80};
    estoque[2] = (Produto){103, "Chocolate ao Leite", 6.25, 60};
    estoque[3] = (Produto){104, "Água Mineral (500ml)", 2.00, 200};
    estoque[4] = (Produto){105, "Cerveja Pilsen (Lata)", 4.50, 150};
    
    *num_produtos = 5; 
}


void menu_principal() {
    printf("\n==== SUPER CONVENIENCIA 24H ====\n");
    printf("1. Listar Estoque\n");
    printf("2. Iniciar Venda\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}