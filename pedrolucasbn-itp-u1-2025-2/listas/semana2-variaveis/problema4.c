#include <stdio.h>
#include <math.h>

int main() {
    int numerox, numeroy;
    float soma, diferenca, divisao, produto, media;
    int resto;

    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &numerox);

    printf("Digite o segundo número inteiro: ");
    scanf("%d", &numeroy);
    soma = numerox + numeroy;
    diferenca = numerox - numeroy;
    divisao = (float)numerox / numeroy;
    produto = numerox * numeroy;
    resto = numerox % numeroy;
    media = (numerox + numeroy) / 2.0;

    printf("Soma: %.2f\n", soma);
    printf("Diferença: %.2f\n", diferenca);
    printf("Produto: %.2f\n", produto);
    printf("Divisao real: %.2f\n", divisao);
    printf("Resto da divisao inteira: %d\n", resto);
    printf("Média aritmética: %.2f\n", media);
    
    return 0;
}
