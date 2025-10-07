#include <stdio.h>
#include <math.h>

// Função auxiliar para verificar se um número é primo
int e_primo(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    
    // Apenas precisamos testar divisores até a raiz quadrada de n. Se n % i, n não é primo
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    int a, b;

    printf("Verificador de Números Primos entre A e B\n");

    // Loop de validação de entrada (A > B)
    do {
        printf("Digite o primeiro número (A): ");
        if (scanf("%d", &a) != 1) {
            printf("Entrada inválida. Por favor, digite um número inteiro.\n");
            // Limpa o buffer de entrada para evitar loop infinito em caso de erro
            while(getchar() != '\n'); 
            continue;
        }

        printf("Digite o segundo número (B): ");
        if (scanf("%d", &b) != 1) {
            printf("Entrada inválida. Por favor, digite um número inteiro.\n");
            while(getchar() != '\n');
            continue;
        }

        if (a <= b) {
            printf("\nERRO: A deve ser estritamente maior que B (A > B). Tente novamente.\n\n");
        }
    } while (a <= b); // Repete o loop enquanto A não for maior que B

    // O programa prossegue aqui porque a > b.
    printf("\nNúmeros primos entre %d e %d (exclusivo):\n", b, a);
    
    // Loop principal para encontrar os primos
    int encontrou_primo = 0;

    // Se o problema pedir os primos *entre* A e B (exclusivamente):
    for (int i = b + 1; i < a; i++) {
        if (e_primo(i)) {
            printf("%d ", i);
            encontrou_primo = 1;
        }
    }

    if (!encontrou_primo) {
        printf("Nenhum número primo encontrado no intervalo.\n");
    } else {
        printf("\n");
    }

    return 0;
}