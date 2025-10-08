#include <stdio.h>

int main() {
    float p; // Preço de venda (Receita)
    float q; // Preço de produção (Custo)
    
    float maior_razao = 0.0;
    int melhor_x = 0;
    int melhor_y = 0;
    
    printf("Buscador de Melhor Promoção (Max X/Y)\n");
    printf("Digite o preço de venda (p): ");
    scanf("%f", &p);
    printf("Digite o preço de produção (q): ");
    scanf("%f", &q);

    // Loop externo: X (total de itens levados)
    // X deve ir de 2 a 10 (minimo X=2, pois X > Y e Y>=1)
    for (int x = 2; x <= 10; x++) { 
        
        // Loop interno: Y (total de itens pagos)
        // Y deve ir de 1 ate X-1 (pois a promocao exige X > Y e Y >= 1)
        for (int y = 1; y < x; y++) {
            
            // Calculo da condicao de nao ter prejuizo: Receita >= Custo
            // (Y * P) >= (X * Q)
            if ((y * p) >= (x * q)) {
                
                // Calcula a razao X/Y
                float razao_atual = (float)x / y;
                
                // Verifica se esta e a melhor promocao ate agora
                if (razao_atual > maior_razao) {
                    maior_razao = razao_atual;
                    melhor_x = x;
                    melhor_y = y;
                }
            }
        }
    }

    printf("\n");
    if (melhor_x > 0) {
        printf("A melhor promoção é: leve %d pague %d\n", melhor_x, melhor_y);
            // Mostra a razão
        printf("(Razão X/Y: %.3f)", maior_razao);
    } else {
        printf("Não foi encontrada nenhuma promoção viável sem prejuízos com o limite de 10 itens.\n");
    }

    return 0;
}