/*
=========================================================
PROJETO: SISTEMA DE MOCHILA DO JOGADOR
Comparação entre Vetor e Lista Encadeada
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 100

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

int compSeqVetor = 0;
int compBinVetor = 0;
int compSeqLista = 0;

/* ---------- VETOR ---------- */

void inserirItemVetor(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\nVetor cheio!\n");
        return;
    }

    printf("Nome: ");
    fgets(mochila[*totalItens].nome, 30, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*totalItens].tipo, 20, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    getchar();

    (*totalItens)++;
}

void listarItensVetor(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nVetor vazio.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("\n[%d] %s | %s | %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

void removerItemVetor(Item mochila[], int *totalItens, char nome[]) {
    int pos = -1;

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    for (int i = pos; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--;
    printf("\nItem removido.\n");
}

int buscarSequencialVetor(Item mochila[], int totalItens, char nome[]) {
    compSeqVetor = 0;

    for (int i = 0; i < totalItens; i++) {
        compSeqVetor++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nEncontrado. Comparacoes: %d\n", compSeqVetor);
            return i;
        }
    }

    printf("\nNao encontrado. Comparacoes: %d\n", compSeqVetor);
    return -1;
}

void ordenarVetor(Item mochila[], int totalItens) {
    Item aux;

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                aux = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = aux;
            }
        }
    }

    printf("\nVetor ordenado.\n");
}

int buscarBinariaVetor(Item mochila[], int totalItens, char nome[]) {
    int inicio = 0, fim = totalItens - 1;
    compBinVetor = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        compBinVetor++;

        int r = strcmp(mochila[meio].nome, nome);

        if (r == 0) {
            printf("\nEncontrado. Comparacoes: %d\n", compBinVetor);
            return meio;
        }

        if (r < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nNao encontrado. Comparacoes: %d\n", compBinVetor);
    return -1;
}

/* ---------- LISTA ---------- */

void inserirItemLista(No **inicio, Item item) {
    No *novo = (No *)malloc(sizeof(No));

    novo->dados = item;
    novo->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    No *atual = *inicio;

    while (atual->proximo != NULL)
        atual = atual->proximo;

    atual->proximo = novo;
}

void listarLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia.\n");
        return;
    }

    while (inicio != NULL) {
        printf("\n%s | %s | %d\n",
               inicio->dados.nome,
               inicio->dados.tipo,
               inicio->dados.quantidade);

        inicio = inicio->proximo;
    }
}

No *buscarLista(No *inicio, char nome[]) {
    compSeqLista = 0;

    while (inicio != NULL) {
        compSeqLista++;

        if (strcmp(inicio->dados.nome, nome) == 0) {
            printf("\nEncontrado. Comparacoes: %d\n", compSeqLista);
            return inicio;
        }

        inicio = inicio->proximo;
    }

    printf("\nNao encontrado. Comparacoes: %d\n", compSeqLista);
    return NULL;
}

void removerItemLista(No **inicio, char nome[]) {
    No *atual = *inicio;
    No *anterior = NULL;

    while (atual != NULL &&
           strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);

    printf("\nItem removido.\n");
}

void liberarLista(No *inicio) {
    No *aux;

    while (inicio != NULL) {
        aux = inicio;
        inicio = inicio->proximo;
        free(aux);
    }
}

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    No *lista = NULL;

    int opcao;
    char nome[30];

    do {
        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("\n--- VETOR ---\n");
        printf("1 Inserir\n2 Remover\n3 Listar\n4 Buscar Sequencial\n5 Ordenar\n6 Busca Binaria\n");
        printf("\n--- LISTA ---\n");
        printf("7 Inserir\n8 Remover\n9 Listar\n10 Buscar\n");
        printf("\n0 Sair\nOpcao: ");

        scanf("%d", &opcao);
        getchar();

        clock_t inicio = clock();

        switch(opcao) {
            case 1:
                inserirItemVetor(mochila, &totalItens);
                break;

            case 2:
                printf("Nome: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome,"\n")] = '\0';
                removerItemVetor(mochila, &totalItens, nome);
                break;

            case 3:
                listarItensVetor(mochila, totalItens);
                break;

            case 4:
                printf("Nome: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome,"\n")] = '\0';
                buscarSequencialVetor(mochila, totalItens, nome);
                break;

            case 5:
                ordenarVetor(mochila, totalItens);
                break;

            case 6:
                printf("Nome: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome,"\n")] = '\0';
                buscarBinariaVetor(mochila, totalItens, nome);
                break;

            case 7: {
                Item item;

                printf("Nome: ");
                fgets(item.nome,30,stdin);
                item.nome[strcspn(item.nome,"\n")] = '\0';

                printf("Tipo: ");
                fgets(item.tipo,20,stdin);
                item.tipo[strcspn(item.tipo,"\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d",&item.quantidade);
                getchar();

                inserirItemLista(&lista,item);
                break;
            }

            case 8:
                printf("Nome: ");
                fgets(nome,30,stdin);
                nome[strcspn(nome,"\n")] = '\0';
                removerItemLista(&lista,nome);
                break;

            case 9:
                listarLista(lista);
                break;

            case 10:
                printf("Nome: ");
                fgets(nome,30,stdin);
                nome[strcspn(nome,"\n")] = '\0';
                buscarLista(lista,nome);
                break;
        }

        if(opcao != 0) {
            double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo da operacao: %.6f segundos\n", tempo);
        }

    } while(opcao != 0);

    liberarLista(lista);
    return 0;
}
