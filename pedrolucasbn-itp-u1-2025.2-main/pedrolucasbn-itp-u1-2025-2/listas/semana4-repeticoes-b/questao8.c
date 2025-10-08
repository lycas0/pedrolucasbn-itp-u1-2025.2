#include <stdio.h>

int main() {
    float preco1, preco2, quantia_disponivel;
    float custo_total, restante;
    
    printf("Verificador de Troco para Placas de Aluminio\n");

    // Entradas dos valores
    printf("Digite o preço do primeiro fornecedor: ");
    scanf("%f", &preco1);
    printf("Digite o preço do segundo fornecedor: ");
    scanf("%f", &preco2);
    printf("Digite a quantia disponível: ");
    scanf("%f", &quantia_disponivel);

    printf("\n");

    // Loop externo: Unidades compradas do Fornecedor 1 (de 0 a 10)
    for (int unidades1 = 0; unidades1 <= 10; unidades1++) {
        
        // Loop interno: Unidades compradas do Fornecedor 2 (de 0 a 10)
        for (int unidades2 = 0; unidades2 <= 10; unidades2++) {
            
            // Calcula o custo total para esta combinação
            custo_total = (unidades1 * preco1) + (unidades2 * preco2);
            
            // Verifica se a compra é possível (custo <= quantia)
            if (custo_total <= quantia_disponivel) {
                
                // Calcula o restante
                restante = quantia_disponivel - custo_total;
                
                // Imprime o resultado formatado
                printf("Comprando %d do primeiro e %d do segundo resta: %.0f\n", 
                       unidades1, unidades2, restante);
            }
        }
    }

    return 0;
}