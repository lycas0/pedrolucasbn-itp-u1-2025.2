#include <stdio.h>
#include <string.h>
#include <ctype.h> // Necessário para as funções isupper e isdigit

// Função que verifica o Padrão Brasileiro: LLL-AAAA
// Formato esperado: XXXXXXX (7 caracteres de entrada)
// A função deve verificar se o formato é LLL AAAA, com a quebra no índice 3.
int is_brasileiro(const char *placa) {
    //  O comprimento deve ser 7 (LLL AAAA)
    if (strlen(placa) != 7) {
        return 0; // Falso
    }

    // Posições 0, 1, 2 devem ser Letras Maiúsculas (L)
    if (!isupper(placa[0]) || !isupper(placa[1]) || !isupper(placa[2])) {
        return 0; // Falso
    }

    // Posições 3, 4, 5, 6 devem ser Dígitos (A)
    if (!isdigit(placa[3]) || !isdigit(placa[4]) || !isdigit(placa[5]) || !isdigit(placa[6])) {
        return 0; // Falso
    }

    // Se passou por todas as verificações, é brasileiro (formato LLLAAAA, que representa LLL-AAAA)
    return 1; // Verdadeiro
}

// Função que verifica o Padrão Mercosul: LLLALAA
int is_mercosul(const char *placa) {
    // O comprimento deve ser 7
    if (strlen(placa) != 7) {
        return 0; // Falso
    }

    // Padrão: L L L A L A A
    // Posições: 0 1 2 3 4 5 6

    // Posições de Letras (L): 0, 1, 2 e 4 devem ser Maiúsculas
    if (!isupper(placa[0]) || !isupper(placa[1]) || !isupper(placa[2]) || !isupper(placa[4])) {
        return 0; // Falso
    }

    // Posições de Algarismos (A): 3, 5 e 6 devem ser Dígitos
    if (!isdigit(placa[3]) || !isdigit(placa[5]) || !isdigit(placa[6])) {
        return 0; // Falso
    }

    // Se passou por todas as verificações, é Mercosul
    return 1; // Verdadeiro
}


int main() {
    // A entrada diz "palavra (sem espaços) de até 10 caracteres",
    // mas o padrão de placas é 7. Usaremos 11 para garantir espaço e o \0.
    char placa[11];

    printf("Digite a placa (ate 10 caracteres): ");
    // Lê a string. O modificador %10s garante o limite de 10 caracteres.
    if (scanf("%10s", placa) != 1) {
        fprintf(stderr, "Erro ao ler a placa.\n");
        return 1;
    }

    // Pega o tamanho da placa lida. Se não for 7, já é inválida por tamanho.
    int tamanho = strlen(placa);
    if (tamanho != 7) {
        printf("invalido\n");
        return 0;
    }
    
    // Converte a placa para MAIÚSCULAS para simplificar a verificação,
    // garantindo que QWE-3232 e QwE-3232 sejam tratadas igualmente.
    // O exercício QwE-3232 -> inválido sugere que a maiúscula é estrita,
    // mas placas oficiais usam apenas maiúsculas, e `isupper()` só testa maiúsculas.
    // Para aderir estritamente ao exemplo QwE-3232 -> inválido:
    
    // --- Lógica de Detecção ---
    if (is_brasileiro(placa)) {
        printf("brasileiro.\n");
    } else if (is_mercosul(placa)) {
        printf("mercosul.\n");
    } else {
        printf("invalido.\n");
    }

    return 0;
}