#include <stdio.h>
#include <stdlib.h> // Coloquei essa biblioteca para usar a função abs()

int soma_divisores_proprios(int n) {
    int soma = 0;

    // Não precisamos verificiar o número 1, pois ele não é um divisor próprio
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            soma += i;
        }
    }
    return soma;
}

int main() {
    int a, b;
    int d_a, d_b;

    printf("Verificador de Números Amigos\n");

    // Solicita ao usuário os dois números
    printf("Digite o primeiro número (A): ");
    scanf("%d", &a);~

    printf("Digite o segundo número (B): ");
    scanf("%d", &b);

    if (a == b) {
    printf("N (Os números devem ser diferentes\n");
    return 1;
    } 

    // Calcular a soma dos divisores próprios
    d_a = soma_divisores_proprios(a);
    d_b = soma_divisores_proprios(b);

    printf("\nD(A) = Soma dos divisores proprios de %d e: %d\n", a, d_a);
    printf("D(B) = Soma dos divisores proprios de %d e: %d\n", b, d_b);
    
    // Aplicar a condição de Números Colegas: |D(A) - B| <= 2 e |D(B) - A| <= 2
    
    // Calcular as diferenças em valor absoluto
    int dif_a_b = abs(d_a - b); // |D(A) - B|
    int dif_b_a = abs(d_b - a); // |D(B) - A|
    
    printf("Diferenca |D(A) - B|: %d\n", dif_a_b);
    printf("Diferenca |D(B) - A|: %d\n", dif_b_a);
    
    // Verifica a condicao final
    if (dif_a_b <= 2 && dif_b_a <= 2) {
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}