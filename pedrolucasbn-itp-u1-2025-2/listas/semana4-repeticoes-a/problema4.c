#include <stdio.h>
#include <math.h>

// Função para calcular a distância euclidiana de um ponto (x,y) até a origem (0, 0)
float calcular_distancia_origem(float x, float y) {
    // D = sqrt(x^2 + y^2)
    return sqrt(x * x + y * y);
}

// Função para calcular a pontuação principal (CORRIGIDA)
int calcular_pontuacao_principal(float distancia) {
    if (distancia <= 1.0) {
        return 10;
    } else if (distancia <= 2.0) {
        return 6;
    } else if (distancia <= 3.0) {
        return 4; // <-- CORREÇÃO: PONTUAÇÃO DE 4 PONTOS
    } else {
        return 0;
    }
}

int main() {
    float x_atual, y_atual; 
    float x_anterior = 0.0; 
    float y_anterior = 0.0;
    float dist_principal;
    float dist_bonus;
    int pontuacao_principal;
    int pontuacao_bonus;
    int pontuacao_total = 0; 

    // CORREÇÃO: Uso de \n para nova linha
    printf("Jogo de Dardos Inovador.\n");

    // Loop para ler e processar os 10 lançamentos
    for (int i = 1; i <= 10; i++) {
        printf("\nLancamento %d:\n", i);
        
        // Leitura das coordenadas
        printf("Digite as coordenadas (x y): ");
        scanf("%f %f", &x_atual, &y_atual);

        // Cálculo da Pontuação Principal
        dist_principal = calcular_distancia_origem(x_atual, y_atual);
        pontuacao_principal = calcular_pontuacao_principal(dist_principal);
        
        printf("  Distância do centro: %.2f (Pontos: %d)\n", dist_principal, pontuacao_principal);
        
        // Cálculo da Pontuação Bônus (Apenas a partir do 2o lançamento)
        pontuacao_bonus = 0;
        
        if (i > 1) {
            // Distância euclidiana ate o lançamento anterior
            float dx = x_atual - x_anterior;
            float dy = y_atual - y_anterior;
            dist_bonus = sqrt(dx * dx + dy * dy);

            // Tabela de Bônus: 5, 3, 2, 0
            if (dist_bonus <= 1.0) {
                pontuacao_bonus = 5;
            } else if (dist_bonus <= 2.0) {
                pontuacao_bonus = 3;
            } else if (dist_bonus <= 3.0) {
                pontuacao_bonus = 2;
            } 
            
            printf("  Distância ao anterior: %.2f (Bonus: +%d pts)\n", dist_bonus, pontuacao_bonus);
        } else {
            printf("  Sem bônus para o primeiro lançamento.\n");
        }
        
        // Acúmulo e Atualização
        pontuacao_total += pontuacao_principal + pontuacao_bonus;
        
        // Atualiza a posição anterior para o próximo loop
        x_anterior = x_atual;
        y_anterior = y_atual;
        
        printf("  Pontuação acumulada: %d\n", pontuacao_total);
    }

    printf("\n===================================\n");
    printf("PONTUAÇÃO TOTAL FINAL: %d pontos\n", pontuacao_total);
    printf("===================================\n");

    return 0;
}