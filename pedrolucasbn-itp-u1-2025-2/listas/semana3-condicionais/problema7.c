#include <stdio.h>
#include <math.h>

int main(){
    float a, b, c, delta, raiz1, raiz2;

    printf("Calculadora de raízes de uma equação de segundo grau.\n");

    //Entrada dos coeficientes
    printf("Digite o valor de a: ");
    scanf("%f", &a);
    //Verificar se é uma equação de segundo grau (Coloquei aqui para evitar desperdício de cálculos)
    if(a == 0) {
        printf("O valor de 'a' não pode ser zero. Não é uma equação de segundo grau.\n");
        return 0;
    }
    printf("Digite o valor de b: ");
    scanf("%f", &b);
    printf("Digite o valor de c: ");
    scanf("%f", &c);
    printf("A equação é: %.2fx^2 + %.2fx + %.2f = 0\n", a, b, c);

    //Cálculo do delta
    delta = b*b - 4*a*c;
    printf("O valor de delta é: %.2f\n", delta);

    //Cálculo das raízes
    if(delta < 0) {
        printf("A equação não possui raízes reais\n");
    } else if(delta == 0) {
        raiz1 = -b / (2*a);
        printf("A equação possui uma raíz real: x = %.2f\n", raiz1);
    } else if (delta > 0) {
        raiz1 = (-b + sqrt(delta)) / (2*a);
        raiz2 = (-b - sqrt(delta)) / (2*a);
        printf("A equação possui duas raízes reais: x1 = %.2f e x2 = %.2f\n", raiz1, raiz2);
    }

    return 0;
}