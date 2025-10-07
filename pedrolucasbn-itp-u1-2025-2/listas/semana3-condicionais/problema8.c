#include <stdio.h>
#include <math.h>

int main() {
    float lado1, lado2, lado3;
    float maior_lado_quadrado, soma_outros_lados_quadrado;

    printf("--- Validador de Triangulos ---\n\n");
    printf("Digite o comprimento do primeiro lado: ");
    scanf("%f", &lado1);
    printf("Digite o comprimento do segundo lado: ");
    scanf("%f", &lado2);
    printf("Digite o comprimento do terceiro lado: ");
    scanf("%f", &lado3);

    // Verificação da existência do triângulo
    if (lado1 + lado2 > lado3 && lado1 + lado3 > lado2 && lado2 + lado3 > lado1) {
        printf("\nOs valores PODEM formar um triângulo.\n");

        // Classificação quanto aos lados
        if (lado1 == lado2 && lado2 == lado3) {
            printf("Classificação: Triângulo Equilátero\n");
        } else if (lado1 == lado2 || lado1 == lado3 || lado2 == lado3) {
            printf("Classificação: Triângulo Isósceles\n");
        } else {
            printf("Classificação: Triângulo Escaleno\n");
        }

        // Classificação quanto aos ângulos
        float a = lado1, b = lado2, c = lado3;

        // Encontra o maior lado e os outros dois
        if (a < b) {
            float temp = a;
            a = b;
            b = temp;
        }
        if (a < c) {
            float temp = a;
            a = c;
            c = temp;
        }

        maior_lado_quadrado = a * a;
        soma_outros_lados_quadrado = b * b + c * c;

        // Devido a imprecisão dos números de ponto flutuante,
        // usamos um pequeno epsilon para a verificação de igualdade
        float epsilon = 0.0001;

        if (fabs(maior_lado_quadrado - soma_outros_lados_quadrado) < epsilon) {
            printf("Ângulos: Triângulo Retangulo\n");
        } else if (maior_lado_quadrado < soma_outros_lados_quadrado) {
            printf("Ângulos: Triângulo Acutângulo\n");
        } else if(maior_lado_quadrado > soma_outros_lados_quadrado) {
            printf("Ângulos: Triângulo Obtusângulo\n");
        }

    } else {
        printf("\nOs valores NÃO podem formar um triângulo.\n");
    }

    return 0;
}