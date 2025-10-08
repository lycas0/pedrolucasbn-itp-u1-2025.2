#include <stdio.h>
#include <math.h>

// Usei 2 'for' pra ser mais rápido e eficiente

int main() {
    int a, b;
    double c_double; // Necessário para o resultado da raiz quadrada
    int c;
    int c_max = 1000;
    int contador = 0;

    printf("Trios Pitágóricos (a^2 + b^2 = c^2) onde c < 1000\n");
    
    // O maior valor possível para 'a' é pouco menos de c_max / sqrt(2)
    for (a = 1; a < c_max / 1.414; a++) { 

        // 'b' deve ser maior que 'a' e limitado pelo 'c_max'
        for (b = a + 1; b < c_max; b++) {
            
            long a_quadrado = (long)a * a;
            long b_quadrado = (long)b * b;

            // Calcula o valor de c
            c_double = sqrt(a_quadrado + b_quadrado);
            c = (int)c_double;

            // Verifica se c é um número inteiro (c_double == c)
            // Usamos uma pequena tolerância (epsilon) para comparação de float
            if (fabs(c_double - c) < 0.000001) {

                // Verifica se c é menor que o limite
                if (c < c_max) {
                    printf("(%d, %d, %d)\n", a, b, c);
                    contador++;
                } else {
                    break; // se c já ultrapassou o limite de a, não há necessidade de continuar.
                }
            }
        }
    }

    printf("\nTotal de trios encontrados: %d\n", contador);
    return 0;
}