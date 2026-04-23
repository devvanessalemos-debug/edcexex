#include <stdio.h>
#include <string.h>

// 📦 Definição da estrutura Territorio
// A struct funciona como um "modelo" que agrupa dados relacionados
// Aqui estamos criando um tipo que representa um território no jogo war
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Programa principal
int main() {

    // Criando um array para armazenar 5 territórios
    struct Territorio territorios[5];

    printf("====================================\n\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n\n");

    // Entrada de dados
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, 30, stdin);

        // remove o '\n' que o fgets captura
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // limpa o caracter que ficou no buffer
        getchar();
    }

    // Exibição dos dados
    for (int i = 0; i < 5; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
