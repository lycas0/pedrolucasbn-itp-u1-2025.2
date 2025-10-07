#include <stdio.h>
#include <math.h>

int main() {
    float posicao_x, posicao_y, coordenada_x, coordenada_y, comprimento_teia;
    int n_de_alvos = 0;
    int sucesso_total = 1; // Váriável para controlar se todos os alvos foram atingidos
    printf("Ajude o Homem-Aranha!\n");

    // Solicita ao usuário as coordenadas do ponto (x, y), o comprimento da teia e o n de alvos
    printf("Digite as coordenadas do Homem-Aranha(x y): ");
    scanf ("%f %f", &posicao_x, &posicao_y);
    printf("Digite o comprimento máximo da teia: ");
    scanf("%f", &comprimento_teia);
    printf("Digite a quantidade de alvos: ");
    scanf("%d", &n_de_alvos);

    printf("\nProcessando os alvos...\n");

    // Loop que vai ler as coordenadas dos alvos
    for (int i = 0; i < n_de_alvos; i++) {
        if (sucesso_total == 0) {
            break;
        }

        // Entrada das cordenadas do alvo
        printf("Digite as coordenadas do alvo %d (x y): ", i + 1);
        scanf("%f %f", &coordenada_x, &coordenada_y);

        // Cálculo da distância Euclidiana
        float dist_x = coordenada_x - posicao_x;
        float dist_y = coordenada_y - posicao_y;
        float distancia = sqrt((dist_x * dist_x) + (dist_y * dist_y));
        printf("A distância até o alvo %d é: %.2f\n", i + 1, distancia);

        if(distancia <= comprimento_teia) {
            printf("Alvo %d atingido!\n", i + 1);
            // Atualiza a posição do Homem-Aranha para a posição do alvo
            // Fórmula de reflexão: (x', y') = 2*ax - x, y
            float nova_x = 2 * coordenada_x - posicao_x;
            posicao_x = nova_x;
            // A posição y permanece a mesma
            printf("Sucesso! Nova posição do Homem-Aranha: (%.2f, %.2f)\n", posicao_x, posicao_y);
        } else {
                printf("Alvo %d não atingido. O Homem-Aranha caiu porque a teia é curta demais.\n", i + 1);
                sucesso_total = 0; // Marca que o Homem-Aranha falhou
        }
    }

    if (sucesso_total == 1) {
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}