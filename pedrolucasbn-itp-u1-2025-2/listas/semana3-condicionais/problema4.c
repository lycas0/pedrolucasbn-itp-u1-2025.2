#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main () {
    char jogada1, jogada2;

    printf("Bem-vindo ao jogo Pedra, Papel e Tesoura!\n");
    
    // Solicita a escolha dos jogadores
    printf("Jogador 1, escolha (P para pedra, A para papel e T para tesoura): ");
    scanf(" %c", &jogada1);
    printf("Jogador 2, escolha (P para pedra, A para papel e T para tesoura): ");
    scanf(" %c", &jogada2);

    // Determina o vencedor, considerando letras maiúsculas e minúsculas
    if (jogada1 == jogada2) {
        printf("Empate!\n");
    } else if (
        (jogada1 == 'P' && jogada2 == 'T')
        ||(jogada1 == 'p' && jogada2 == 't')
        || (jogada1 == 'A' && jogada2 == 'P')
        || (jogada1 == 'a' && jogada2 == 'p')
        || (jogada1 == 'T' && jogada2 == 'A')
        || (jogada1 == 't' && jogada2 == 'a')
    ) {
        printf("Jogador 1 vence!\n");
    } else if (
        (jogada1 == 'P' && jogada2 == 'A')
        ||(jogada1 == 'p' && jogada2 == 'a')
        || (jogada1 == 'A' && jogada2 == 'T')
        || (jogada1 == 'a' && jogada2 == 't')
        || (jogada1 == 'T' && jogada2 == 'P')
        || (jogada1 == 't' && jogada2 == 'p')
    ) {
        printf ("Jogador 2 vence!\n");
    } else {
        printf("Jogada inválida. Use P, A ou T.\n");
    }

    return 0;
}