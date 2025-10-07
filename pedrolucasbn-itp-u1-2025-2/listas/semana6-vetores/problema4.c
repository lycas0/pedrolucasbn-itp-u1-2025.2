#include <stdio.h>
#include <stdbool.h>

#define NUM_ILHAS 10 // O número total de ilhas (0 a 9)

int main() {
    // O array 'sugestoes' armazena o mapa do tesouro. 
    // sugestoes[i] é a ilha para onde o nativo da ilha 'i' sugere ir.
    int sugestoes[NUM_ILHAS];
    int i; // Contador
    
    // O array 'visitadas' serve como um marcador (flag) para rastrear quais ilhas já foram visitadas.
    // visitadas[k] será true se a ilha 'k' já foi visitada antes.
    bool visitadas[NUM_ILHAS];
    
    // Leitura da entrada (10 sugestões, de 0 a 9)
    // O loop while(scanf(...) == NUM_ILHAS) permite processar múltiplas entradas de teste.
    if (scanf("%d %d %d %d %d %d %d %d %d %d", 
              &sugestoes[0], &sugestoes[1], &sugestoes[2], &sugestoes[3], &sugestoes[4],
              &sugestoes[5], &sugestoes[6], &sugestoes[7], &sugestoes[8], &sugestoes[9]) == NUM_ILHAS) {
        
        // Inicializa o array de ilhas visitadas como falso
        for (i = 0; i < NUM_ILHAS; i++) {
            visitadas[i] = false;
        }
        
        // Início da jornada
        int ilha_atual = 0; // Começa na ilha inicial (ilha 0)
        
        // Loop de busca pelo tesouro
        while (true) {
            // Marca a ilha atual como visitada
            visitadas[ilha_atual] = true;
            
            // Move para a próxima ilha, seguindo a sugestão do nativo
            int proxima_ilha = sugestoes[ilha_atual];
            
            // Verifica se a próxima ilha já foi visitada
            if (visitadas[proxima_ilha]) {
                // Se a próxima ilha já foi visitada, ela é a ilha que será visitada pela segunda vez
                // e é onde, segundo a crença, o tesouro está.
                printf("%d\n", proxima_ilha);
                break; // Encerra a busca
            }
            
            // Atualiza a ilha atual para a próxima ilha e continua o ciclo
            ilha_atual = proxima_ilha;
        }
    }

    return 0;
}