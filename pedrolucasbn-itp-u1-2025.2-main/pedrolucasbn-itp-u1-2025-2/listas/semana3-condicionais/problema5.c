#include <stdio.h>
#include <math.h>

int main() {
    float valor_compra, valor_final;
    float valor_desconto = 0.0;
    float porcentagem_desconto = 0.0;

    // Solicita o valor da compra
    printf("Digite o valor da compra: ");
    scanf("%f", &valor_compra);

    // Determina a porcentagem de desconto com base no valor da compra
    if (valor_compra > 1000.00) {
        porcentagem_desconto = 0.20;
    } else if (valor_compra > 500.00) {
        porcentagem_desconto = 0.15;
    } else if (valor_compra > 100.00) {
        porcentagem_desconto = 0.10;
    } else {
        porcentagem_desconto = 0.00;
    }

    // Calcula o valor do desconto e o valor final
    valor_desconto = valor_compra * porcentagem_desconto;
    valor_final = valor_compra - valor_desconto;

    // Exibe os resultados
    printf("\n--- Detalhes da Compra ---\n");
    printf("Valor original: R$ %.2f\n", valor_compra);
    printf("Porcentagem de desconto: %.0f%%\n", porcentagem_desconto * 100);
    printf("Valor do desconto: R$ %.2f\n", valor_desconto);
    printf("Valor a pagar: R$ %.2f\n", valor_final);
    printf("-------------------------\n");

    return 0;
}