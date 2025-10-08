#include <stdio.h>
#include <math.h>

int main() {
    float consumo_kWh, tarifa, valor_total;
    char tipo_consumidor;
    const float taxa_fixa = 15.00;

    // Solicita o consumo e o tipo de consumidor
    printf("Digite o consumo em kWh: ");
    scanf("%f", &consumo_kWh);
    printf("Digite o tipo de consumidor (R para residencial, C para comercial, I para industrial): ");
    scanf(" %c", &tipo_consumidor); // Espaço antes de %c para ignorar o espaço em branco

    // Determina tarifa com base no tipo de consumidor
    if (tipo_consumidor == 'R' || tipo_consumidor == 'r') {
        tarifa = 0.60;
    } else if (tipo_consumidor == 'C' || tipo_consumidor == 'c') {
        tarifa = 0.48;
    } else if (tipo_consumidor == 'I' || tipo_consumidor == 'i') {
        tarifa = 1.29;
    } else {
        printf("Tipo de consumidor inválido.\n");
        return 1; // Sai do programa com código de erro
    }

    //Calcula o valor total da conta
    valor_total = (consumo_kWh * tarifa) + taxa_fixa;

    //Exibe o valor total da conta
    printf("O valor total da conta de energia é: R$ %.2f\n", valor_total);

    return 0;
}