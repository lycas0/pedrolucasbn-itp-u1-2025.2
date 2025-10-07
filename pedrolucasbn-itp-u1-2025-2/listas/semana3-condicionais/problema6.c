#include <stdio.h>

int main() {
    char febre, dor_cabeca, dor_corpo, tosse;

    printf("Essa ferramenta ajudará com o seu diagnóstico!\n");
    printf("Responda as perguntas com S para sim e N para não.\n");

    //Perguntas
    printf("Você tem febre?(S/N): ");
    scanf(" %c", &febre);
    printf("Você tem dor de cabeça?(S/N): ");
    scanf(" %c", &dor_cabeca);
    printf("Você tem dores no corpo?(S/N): ");
    scanf(" %c", &dor_corpo);
    printf("Você tem tosse?(S/N): ");
    scanf(" %c", &tosse);

    //Diagnóstico
    if (febre == 'S' && dor_cabeca == 'S' && dor_corpo == 'S') {
        printf("Possível gripe.");
    } else if (febre == 'S' && tosse == 'S') {
        printf("Possível resfriado.");
    } else if (dor_cabeca == 'S') {
        printf("Possível enxaqueca.");
    } else if (febre == 'S') {
        printf("Consulte um médico.");
    } else if (febre == 'N' && dor_cabeca == 'N' && dor_corpo == 'N' && tosse == 'N') {
        printf("Você parece estar bem.");
    } else {
        printf("Consulte um médico para avaliação.");
    }

    return 0;
}