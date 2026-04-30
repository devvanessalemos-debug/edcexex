//==========================================================
// PRÁTICA SISTEMA DE BIBLIOTECA PARTE 2
//
// OBJETIVO DESTA PARTE:
// Adicionar a funcionalidade de emprestimo e introduzir alocação dinâmica.
// - Os arrays de livros e empréstimos são alocados com malloc/calloc.
// - Nova struct para empréstimo.
// - Liberação de memoria com free.
//
//==========================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// --- Definição da estrutura (struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {

    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // --- Laço Principal do Menu ---
    do {

        // Exibe o menu de opções.
        printf("=======================================\n");
        printf("      BIBLIOTECA - PARTE 1\n");
        printf("=======================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("---------------------------------------\n");
        printf("Escolha uma opção: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf

        // --- Processamento da opção ---
        switch (opcao) {

            case 1: // Cadastro de livro
                printf(" --- Cadastro de Novo Livro ---\n\n");

                if (totalLivros < MAX_LIVROS) {

                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o Autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a Editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edição: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    totalLivros++; // totalLivros + 1;

                    printf("\nLivro cadastrado com sucesso!\n");

                } else {
                    printf("Biblioteca cheia! Não é possivel cadastrar mais livros.\n");
                }

                printf("\nPressione Enter para Continuar...");
                getchar(); // Pausa

                break;

            case 2: // LISTAGEM DE LIVROS
                printf(" --- Lista de Livros Cadastrados ---\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda!\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("-----------------------------\n");
                        printf("Livro %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                    }
                    printf("------------------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();

                break;

            case 0: // SAIR
                printf("\nSaindo do sistema...\n");
                break;

            default: // OPÇÃO INVÁLIDA
                printf("\nOpção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0; // Fim do Programa
}