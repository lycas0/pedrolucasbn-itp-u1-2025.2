#include <stdio.h>
#include <math.h>

int main() {
    float média, nota1, nota2, nota3, prova_final, média_final;

    // Solicita as notas do aluno
    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);
    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);
    printf("Digite a terceiea nota: ");
    scanf("%f", &nota3);
    
    // Calcula a média das três notas
    média = (nota1 + nota2 + nota3) / 3.0;
    printf("A média das três notas é: %.2f\n", média);

    // Verifica se a média é maior que 7.0
    if (média >= 7.0) {
        printf("Aprovado.\n");
    } else {
        printf ("O aluno precisa fazer a prova final.\n");
    }

    // Solicita a nota da prova final
    printf("Digite a nota da prova final: ");
    scanf("%f", &prova_final);

    // Calcula a média final
    média_final = (média + prova_final) / 2.0;
    printf("A média final é: %.2f\n", média_final);

    // Verifica se o aluno foi aprovado
    if (média_final >= 5.0) {
        printf("Aprovado.\n");
    } else {
        printf("Reprovado.\n");
    }
    return 0;
}