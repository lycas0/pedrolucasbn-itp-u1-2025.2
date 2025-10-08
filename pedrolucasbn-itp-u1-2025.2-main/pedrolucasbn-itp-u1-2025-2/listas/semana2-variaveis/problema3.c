#include <stdio.h>
#include <math.h>

int main() {
    float CapitalInicial, TaxaJuros, TempoAnos, Montante;

    printf("Digite o Capital Inicial: ");
    scanf("%f", &CapitalInicial);

    printf("Digite a Taxa de Juros (em %%): ");
    scanf("%f", &TaxaJuros);

    printf("Digite o Tempo em anos: ");
    scanf("%f", &TempoAnos);

    Montante = CapitalInicial * pow((1 + TaxaJuros / 100), TempoAnos);

    printf("O Montante após %.1f anos é: %.2f\n", TempoAnos, Montante);
    
    return 0;
}