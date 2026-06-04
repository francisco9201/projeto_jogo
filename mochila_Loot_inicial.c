#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a quantidade máxima de itens que a mochila pode armazenar
#define MAX_ITENS 10

// ======================================
// Estrutura que representa um item da mochila
// ======================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ======================================
// Função responsável por cadastrar um novo item
// ======================================
void inserirItem(Item mochila[], int *totalItens) {

    // Verifica se ainda há espaço disponível na mochila
    if (*totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Limite de %d itens.\n", MAX_ITENS);
        return;
    }

    printf("\n=== CADASTRAR ITEM ===\n");

    printf("Nome: ");
    fgets(mochila[*totalItens].nome, 30, stdin);

    // Remove o caractere '\n' deixado pelo fgets
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*totalItens].tipo, 20, stdin);

    // Remove o '\n' da string do tipo
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    // Limpa o buffer do teclado
    getchar();

    // Incrementa a quantidade total de itens cadastrados
    (*totalItens)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// ======================================
// Exibe todos os itens cadastrados
// ======================================
void listarItens(Item mochila[], int totalItens) {

    printf("\n========== INVENTÁRIO ==========\n");

    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    // Percorre o vetor exibindo cada item
    for (int i = 0; i < totalItens; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }

    printf("\n================================\n");
}

// ======================================
// Busca sequencial pelo nome do item
// ======================================
int buscarItem(Item mochila[], int totalItens, char nomeBusca[]) {

    // Percorre todos os elementos do vetor
    for (int i = 0; i < totalItens; i++) {

        // Compara o nome procurado com o nome armazenado
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            // Retorna a posição onde o item foi encontrado
            return i;
        }
    }

    printf("\nItem não encontrado.\n");

    // Retorna -1 caso não encontre o item
    return -1;
}

// ======================================
// Remove um item da mochila
// ======================================
void removerItem(Item mochila[], int *totalItens) {

    char nomeBusca[30];

    printf("\nNome do item que deseja remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int posicao = -1;

    // Procura o item informado pelo usuário
    for (int i = 0; i < *totalItens; i++) {

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            posicao = i;
            break;
        }
    }

    // Caso não encontre o item
    if (posicao == -1) {

        printf("\nItem não encontrado.\n");
        return;
    }

    // Desloca os elementos para preencher o espaço removido
    for (int i = posicao; i < *totalItens - 1; i++) {

        mochila[i] = mochila[i + 1];
    }

    // Atualiza a quantidade total de itens
    (*totalItens)--;

    printf("\nItem removido com sucesso!\n");
}

// ======================================
// Função principal do programa
// ======================================
int main() {

    // Vetor que armazenará até 10 itens
    Item mochila[MAX_ITENS];

    // Controla a quantidade de itens cadastrados
    int totalItens = 0;

    int opcao;

    do {

        // Menu principal do sistema
        printf("\n===== MOCHILA DO JOGADOR =====\n");
        printf("1 - Cadastrar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Buscar Item\n");
        printf("4 - Listar Itens\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        getchar();

        switch(opcao) {

            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3: {

                char nomeBusca[30];

                printf("\nDigite o nome do item: ");
                fgets(nomeBusca, 30, stdin);

                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                buscarItem(mochila, totalItens, nomeBusca);

                listarItens(mochila, totalItens);

                break;
            }

            case 4:
                listarItens(mochila, totalItens);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0); // Repete até o usuário escolher sair

    return 0;
}