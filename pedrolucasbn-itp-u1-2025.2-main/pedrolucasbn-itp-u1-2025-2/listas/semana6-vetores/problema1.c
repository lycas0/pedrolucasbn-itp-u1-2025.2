#include <stdio.h>
#include <stdlib.h> // Necessário para malloc/free se n fosse dinâmico, mas aqui só usamos para clareza

int main() {
    int n; // Número de questões
    int i; // Contador de loop
    int acertos = 0;
    
    // Leitura do número de questões (n)
    // O loop while(scanf(...) == 1) permite processar múltiplas entradas de teste
    while (scanf("%d", &n) == 1) {
        
        // O limite é n <= 20, então podemos usar arrays estáticos de tamanho 20
        // Para garantir que o código funcione para n=20, declaramos um tamanho fixo suficiente
        int gabarito[20]; 
        int aluno[20];
        
        // Resetar o contador de acertos para cada novo caso de teste
        acertos = 0; 
        
        // Leitura das n respostas do gabarito
        for (i = 0; i < n; i++) {
            scanf("%d", &gabarito[i]);
        }
        
        // Leitura das n respostas do aluno e contagem de acertos
        for (i = 0; i < n; i++) {
            scanf("%d", &aluno[i]);
            
            // Compara a resposta do aluno com a resposta do gabarito para a mesma questão (índice i)
            if (aluno[i] == gabarito[i]) {
                acertos++;
            }
        }
        
        // Impressão da Saída
        printf("%d acerto", acertos);
        
        // Adiciona o 's' se houver 0 ou mais de 1 acerto
        if (acertos != 1) {
            printf("s");
        }
        printf("\n");
    }

    return 0;
}