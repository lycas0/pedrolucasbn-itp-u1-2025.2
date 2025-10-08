#include <stdio.h>

#define MAX_N 30 // Limite máximo para o número de terrenos (n <= 30)

int main() {
    int n; // Número de terrenos
    int alturas[MAX_N]; // Array para armazenar as alturas
    int i; // Contador de loop
    int altura_maxima;
    int indice_primeiro_max;
    int indice_ultimo_max;
    int comprimento_ponte;
    
    // O loop while(scanf(...) == 1) permite processar múltiplas entradas de teste
    while (scanf("%d", &n) == 1) {
        
        // Leitura das alturas
        altura_maxima = -1; // Inicializa com um valor impossível, já que alturas são > 0
        
        for (i = 0; i < n; i++) {
            scanf("%d", &alturas[i]);
            
            // Encontra a altura máxima
            if (alturas[i] > altura_maxima) {
                altura_maxima = alturas[i];
            }
        }
        
        // Encontrar os índices do primeiro e último ponto com a altura máxima
        
        // Encontrar o índice do PRIMEIRO ponto máximo (varre da esquerda para a direita)
        indice_primeiro_max = -1;
        for (i = 0; i < n; i++) {
            if (alturas[i] == altura_maxima) {
                indice_primeiro_max = i;
                break; // Encontrado o primeiro, para o loop
            }
        }
        
        // Encontrar o índice do ÚLTIMO ponto máximo (varre da direita para a esquerda)
        // O problema garante que SEMPRE haverá duas ocorrências.
        indice_ultimo_max = -1;
        for (i = n - 1; i >= 0; i--) {
            if (alturas[i] == altura_maxima) {
                indice_ultimo_max = i;
                break; // Encontrado o último, para o loop
            }
        }
        
        // Calcular o comprimento da ponte
        // O comprimento é a diferença entre os índices (posições)
        comprimento_ponte = indice_ultimo_max - indice_primeiro_max;
        
        // Resultado
        printf("%d\n", comprimento_ponte);
    }

    return 0;
}