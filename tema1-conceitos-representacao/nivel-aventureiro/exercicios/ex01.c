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
#define MAX_EMPRESTIMOS 100 // Definimos uma capacidade para empréstimos
#define TAM_STRING 100

// --- Definição da estrutura (struct) ---
// Struct livro agora tem um campo ''disponivel'para controlar o status
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;  // 1 para sim e 0 para não
};

// Nova struct para armazenar informações do empréstimo.
struct Emprestimo {
    int indiceLivro; // Para saber qual livro do array 'biblioteca' foi removido
    char nomeUsuario[TAM_STRING];
};


// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {

    // 1.ALOCAÇÃO DINÂMICA DE MEMÓRIA
    // Agora, em vez de arrays estáticos, usamos ponteiros.

    struct Livro *biblioteca;
    struct Emprestimo *emprestimo;

    // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_de_cada_elemento)
    // Vantagem: inicializa tada a memória com zeros. Isso significa que 'disponivel' já começa com zero
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    //Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
    emprestimo = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // VERIFICAÇÃO: É crucial verificar se a alocação de memória deu certo.
    if (biblioteca == NULL || emprestimo == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;
    

    // --- Laço Principal do Menu ---
    do {

        // Exibe o menu de opções.
        printf("=======================================\n");
        printf("      BIBLIOTECA - PARTE 2\n");
        printf("=======================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");  
        printf("4 - Listar empréstimo\n");  
        printf("0 - Sair\n");
        printf("---------------------------------------\n");
        printf("Escolha uma opção: ");

        // Lê a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf
            opcao = -1;
        }
        limparBufferEntrada();

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

                    biblioteca[totalLivros].disponivel = 1;

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

            case 3: // REALIZAR EMPRÉSTIMO
                printf("--- Realizar ---\n\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de empréstimos atingido!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel){
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis ==0){
                        printf("Nenhum livro disponivel para emprestimo. \n");
                    } else {
                        printf("\nDigite o numero do livro que deseja emprestar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBufferEntrada();

                        int indice = numLivro -1; // Converte para o indice do array (0 a N-1).

                        // Validação da escolha do usuário.
                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimo[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);

                            emprestimo[totalEmprestimos].nomeUsuario[
                                strcspn(emprestimo[totalEmprestimos].nomeUsuario, "\n")
                            ] = '\0';

                            //Registra o emprestimo
                            emprestimo[totalEmprestimos].indiceLivro = indice;

                            //Atualiza o status do livro para indisponivel.
                            biblioteca[indice].disponivel =0;

                            totalEmprestimos++;
                            printf("\nEmprestimo realizado com sucesso!\n");


                        } else {
                            printf("\nNumero de livro invalido ou livro indisponivel.\n");
                        }
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 4: // LISTAR EMPRÉSTIMOS
                printf("--- Lista de Emprestimos ---\n\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo realizado.\n");
                } else{
                    for (int i = 0; i < totalEmprestimos; i++) {
                        // Usa o indice armazenado no emprestimo para buscar o nome do livro.
                        int indiceLivro = emprestimo[i].indiceLivro;
                        printf("----------------------------------------------\n");
                        printf("EMPRESTIMO %d\n", i + 1);
                        printf("LIVRO: %s\n", biblioteca[indiceLivro].nome);
                        printf("USUARIO: %s\n", emprestimo[i].nomeUsuario);
                    }
                    printf("-----------------------------------------------\n");
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

    // Liberação de memoria
    // Antes de terminar, é essencial liberar a memoria que foi alocada dinamicamente.
    // Isso evita "memory leaks" (vazamentos de  memória).

    free(biblioteca);
    free(emprestimo);

    printf("Memória liberada com sucesso.\n");


    return 0; // Fim do Programa
}