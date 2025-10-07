#include <stdio.h>
#include <math.h>   // Necessário para sin() e cos()
#include <stdbool.h> // Necessário para o tipo bool (true/false)

// Define o raio de offset da sonda
#define OFFSET_SONDA 0.2
// Define o offset dos vizinhos
#define OFFSET_VIZINHO 2.0
// Define os limites de altura segura
#define ALTURA_MINIMA 0.0
#define ALTURA_MAXIMA 2.0

/**
 * @brief Calcula a altura do terreno na coordenada (x, y).
 * f(x,y) = sin(cos(y) + x) + cos(y + sin(x))
 * @param x Coordenada x (float).
 * @param y Coordenada y (float).
 * @return A altura f(x,y) (float).
 */
float calcular_altura(float x, float y) {
    // Usamos as funções sin() e cos() da biblioteca math.h
    return sin(cos(y) + x) + cos(y + sin(x));
}

/**
 * @brief Verifica se um único ponto está dentro do intervalo seguro [0, 2].
 * @param altura O valor da altura a ser verificado (float).
 * @return true se a altura for segura, false caso contrário.
 */
bool altura_segura(float altura) {
    return (altura >= ALTURA_MINIMA && altura <= ALTURA_MAXIMA);
}

/**
 * @brief Verifica se a coordenada p=(x,y) é um ponto de pouso seguro.
 * Um ponto é seguro se o centro (x,y) e os 4 cantos da sonda 
 * (±0.2, ±0.2) estiverem em uma altura segura.
 * @param x Coordenada x do centro (float).
 * @param y Coordenada y do centro (float).
 * @return true se o ponto for seguro para a sonda, false caso contrário.
 */
bool ponto_de_pouso_seguro(float x, float y) {
    // Lista dos 5 pontos a serem verificados (centro + 4 cantos)
    
    // Ponto central P=(x, y)
    if (!altura_segura(calcular_altura(x, y))) {
        return false;
    }

    // Canto superior direito (x + 0.2, y + 0.2)
    if (!altura_segura(calcular_altura(x + OFFSET_SONDA, y + OFFSET_SONDA))) {
        return false;
    }

    // Canto inferior esquerdo (x - 0.2, y - 0.2)
    if (!altura_segura(calcular_altura(x - OFFSET_SONDA, y - OFFSET_SONDA))) {
        return false;
    }

    // Canto superior esquerdo (x - 0.2, y + 0.2)
    if (!altura_segura(calcular_altura(x - OFFSET_SONDA, y + OFFSET_SONDA))) {
        return false;
    }
    
    // Canto inferior direito (x + 0.2, y - 0.2)
    if (!altura_segura(calcular_altura(x + OFFSET_SONDA, y - OFFSET_SONDA))) {
        return false;
    }

    // Se todos os 5 pontos passaram na verificação
    return true;
}


int main() {
    float x_pouso, y_pouso;
    
    // Lista de offsets para os 4 vizinhos (x+2, y), (x-2, y), (x, y-2), (x, y+2)
    // O array armazena pares de (delta_x, delta_y)
    float vizinhos_offsets[4][2] = {
        {OFFSET_VIZINHO, 0.0},      // (x+2, y)
        {-OFFSET_VIZINHO, 0.0},     // (x-2, y)
        {0.0, -OFFSET_VIZINHO},     // (x, y-2)
        {0.0, OFFSET_VIZINHO}       // (x, y+2)
    };
    
    // Leitura da coordenada de pouso
    while (scanf("%f %f", &x_pouso, &y_pouso) == 2) {
        
        // VERIFICA O PONTO DE POUSO (x_pouso, y_pouso)
        if (!ponto_de_pouso_seguro(x_pouso, y_pouso)) {
            // Regra 1: Se o ponto principal não for seguro
            printf("troque de coordenada\n");
            continue; // Pula para a próxima entrada
        }
        
        // VERIFICA OS 4 PONTOS VIZINHOS
        int vizinhos_seguros = 0;
        
        for (int i = 0; i < 4; i++) {
            float x_vizinho = x_pouso + vizinhos_offsets[i][0];
            float y_vizinho = y_pouso + vizinhos_offsets[i][1];
            
            if (ponto_de_pouso_seguro(x_vizinho, y_vizinho)) {
                vizinhos_seguros++;
            }
        }
        
        // CLASSIFICAÇÃO FINAL
        // (O ponto central já sabemos que é seguro)
        
        if (vizinhos_seguros == 4) {
            // Regra 2.d: 4 pontos vizinhos seguros
            printf("seguro\n");
        } else if (vizinhos_seguros == 2 || vizinhos_seguros == 3) {
            // Regra 2.c: 2 ou 3 pontos vizinhos seguros
            printf("relativamente seguro\n");
        } else { // vizinhos_seguros é 0 ou 1
            // Regra 2.b: 0 ou 1 ponto vizinho seguro
            printf("inseguro\n");
        }
    }

    return 0;
}