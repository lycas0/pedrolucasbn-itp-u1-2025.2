#include <stdio.h>

// Função para normalizar horas e minutos
// Recebe ponteiros para modificar as variáveis originais
void normaliza_tempo(int *h, int *m) {
    // Transfere horas dos minutos e mantém o resto dos minutos (0-59)
    *h += *m / 60;
    *m %= 60;

    // Garante que a hora esteja entre 0 e 23 (lidando com a passagem de dias)
    *h %= 24;
}

// Função para imprimir o horário no formato 24h ou 12h
void imprime_horario(int hora, int minuto, int formato) {
    if (formato == 0) {
        // Formato 24h: HH:MM. %02d garante o zero à esquerda.
        printf("%02d:%02d\n", hora, minuto);
    } else {
        // Formato 12h: HH:MM AA
        int hora_12h;
        char *am_pm;

        // Determina AM/PM
        am_pm = (hora >= 12) ? "PM" : "AM";

        // Converte a hora 24h para 12h
        if (hora == 0 || hora == 12) {
            // Meia-noite (00:xx) e Meio-dia (12:xx) são 12
            hora_12h = 12;
        } else if (hora > 12) {
            // Horas da tarde/noite (13:xx a 23:xx)
            hora_12h = hora - 12;
        } else {
            // Horas da manhã (01:xx a 11:xx)
            hora_12h = hora;
        }

        // Imprime o resultado
        printf("%02d:%02d %s\n", hora_12h, minuto, am_pm);
    }
}

int main() {
    int H_inicial, M_inicial, F;
    int H_ronda, M_ronda;

    // Vetores de acréscimos (Horas e Minutos)
    int acrescimos_h[] = {0, 1, 2, 4, 12};
    int acrescimos_m[] = {0, 0, 10, 40, 5};

    // Lê a entrada (Hora, Minuto e Formato)
    while (scanf("%d %d %d", &H_inicial, &M_inicial, &F) == 3) {

        // Itera sobre os 5 acréscimos
        for (int i = 0; i < 5; i++) {
            // Calcula a soma total de horas e minutos
            H_ronda = H_inicial + acrescimos_h[i];
            M_ronda = M_inicial + acrescimos_m[i];

            // Normaliza o horário (corrigindo minutos > 59 e horas >= 24)
            normaliza_tempo(&H_ronda, &M_ronda);

            // Imprime no formato solicitado
            imprime_horario(H_ronda, M_ronda, F);
        }
    }

    return 0;
}