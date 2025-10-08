#include <stdio.h>

int main() {
    float comprimento_folha, largura_folha, comprimento_bolso;
    int dobras_folha;
    int contador_dobras = 0;

    // Solicita ao usuário o comprimento, largura da folha e o comprimento do bolso
    printf("Digite o comprimento da folha (em metros): ");
    if (scanf("%f", &comprimento_folha) != 1 || comprimento_folha <= 0) {
        printf("Entrada inválida. Por favor, insira um comprimento válido.\n");
        return 1;
    }
    
    printf("Digite a largura da folha (em metros): ");
    if (scanf("%f", &largura_folha) != 1 || largura_folha <= 0) {
        printf("Entrada inválida. Por favor, insira uma largura válida.\n");
        return 1;
    }

    printf("Digite o número do comprimento do bolso: ");
    if (scanf("%f", &comprimento_bolso) != 1 || comprimento_bolso <= 0) {
        printf("Entrada inválida. Por favor, insira um comprimento de bolso válido.\n");
        return 1;
    }

    // Calcula o número de dobras necessárias
    while (comprimento_folha > comprimento_bolso && largura_folha > comprimento_bolso) {
        if (comprimento_folha >= largura_folha) {
            comprimento_folha /= 2.0; 
            printf("Dobra %d (Comprimento): %.2f x %.2f\n", contador_dobras + 1, comprimento_folha, largura_folha);
        } else {
            // Dobra na largura (o maior lado)
            largura_folha /= 2.0;
            printf("Dobra %d (Largura): %.2f x %.2f\n", contador_dobras + 1, comprimento_folha, largura_folha);
        }
        
        // 4. Incrementa o contador de dobras
        contador_dobras++;
    }
    
    if (contador_dobras == 0) {
        printf("A folha já cabe no bolso (%.2f x %.2f) sem nenhuma dobra.\n", comprimento_folha, largura_folha);
    } else {
        printf("Total de dobras necessárias: %d\n", contador_dobras);
        printf("Após %d dobras, a folha tem %.2f x %.2f e cabe no bolso.\n", 
               contador_dobras, comprimento_folha, largura_folha);
    }

    return 0;
}