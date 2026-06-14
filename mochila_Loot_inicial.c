/*
=========================================================
PROJETO: SISTEMA DE MOCHILA DO JOGADOR

Objetivo:
Comparar o desempenho de Vetor e Lista Encadeada
nas operações de inserção, remoção, listagem
e busca de itens.
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Quantidade máxima de itens armazenados no vetor */
#define MAX_ITENS 100

/*
=========================================================
ESTRUTURA ITEM

Armazena as informações de cada item da mochila.
=========================================================
*/
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/*
=========================================================
ESTRUTURA NÓ

Cada nó da lista encadeada armazena:
- Um item
- Um ponteiro para o próximo nó
=========================================================
*/
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

/*
=========================================================
CONTADORES DE COMPARAÇÕES

Utilizados para analisar o desempenho das buscas.
=========================================================
*/
int compSeqVetor = 0;
int compBinVetor = 0;
int compSeqLista = 0;

/*
=========================================================
FUNÇÃO: INSERIR ITEM NO VETOR

Adiciona um novo item na próxima posição livre
do vetor.
=========================================================
*/
void inserirItemVetor(Item mochila[], int *totalItens)
{
    /* Verifica se existe espaço disponível */
    if (*totalItens >= MAX_ITENS)
    {
        printf("\nVetor cheio!\n");
        return;
    }

    /* Recebe o nome do item */
    printf("\nNome: ");
    fgets(mochila[*totalItens].nome, 30, stdin);

    /* Remove o caractere '\n' */
    mochila[*totalItens].nome[
        strcspn(mochila[*totalItens].nome, "\n")
    ] = '\0';

    /* Recebe o tipo do item */
    printf("Tipo: ");
    fgets(mochila[*totalItens].tipo, 20, stdin);

    /* Remove o '\n' */
    mochila[*totalItens].tipo[
        strcspn(mochila[*totalItens].tipo, "\n")
    ] = '\0';

    /* Recebe a quantidade */
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    getchar();

    /* Atualiza o total de itens */
    (*totalItens)++;

    printf("\nItem inserido com sucesso!\n");
}

/*
=========================================================
FUNÇÃO: LISTAR ITENS DO VETOR

Percorre todo o vetor exibindo os itens
cadastrados.
=========================================================
*/
void listarItensVetor(Item mochila[], int totalItens)
{
    /* Verifica se o vetor está vazio */
    if(totalItens == 0)
    {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    printf("\n===== ITENS DO VETOR =====\n");

    /* Percorre todas as posições ocupadas */
    for(int i = 0; i < totalItens; i++)
    {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n",
               mochila[i].quantidade);
    }
}

/*
=========================================================
FUNÇÃO: BUSCA SEQUENCIAL NO VETOR

Percorre o vetor posição por posição
até encontrar o item.

Complexidade: O(n)
=========================================================
*/
int buscarSequencialVetor(Item mochila[],
                          int totalItens,
                          char nome[])
{
    /* Reinicia o contador */
    compSeqVetor = 0;

    /* Percorre todos os elementos */
    for(int i = 0; i < totalItens; i++)
    {
        /* Conta uma comparação */
        compSeqVetor++;

        /* Verifica se encontrou o item */
        if(strcmp(mochila[i].nome, nome) == 0)
        {
            printf("\nItem encontrado!");
            printf("\nComparacoes: %d\n",
                   compSeqVetor);

            return i;
        }
    }

    printf("\nItem nao encontrado.");
    printf("\nComparacoes: %d\n",
           compSeqVetor);

    return -1;
}

/*
=========================================================
FUNÇÃO: ORDENAR VETOR

Utiliza o algoritmo Bubble Sort para ordenar
os itens em ordem alfabética pelo nome.

A ordenação é necessária para permitir
a busca binária.
=========================================================
*/
void ordenarVetor(Item mochila[],
                  int totalItens)
{
    Item aux;

    /* Controle das passagens */
    for(int i = 0; i < totalItens - 1; i++)
    {
        /* Compara elementos adjacentes */
        for(int j = 0;
            j < totalItens - i - 1;
            j++)
        {
            if(strcmp(mochila[j].nome,
                      mochila[j + 1].nome) > 0)
            {
                /* Troca os elementos */
                aux = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = aux;
            }
        }
    }

    printf("\nVetor ordenado com sucesso!\n");
}

/*
=========================================================
FUNÇÃO: BUSCA BINÁRIA

Procura um item em um vetor já ordenado.

Complexidade: O(log n)

Mais eficiente que a busca sequencial.
=========================================================
*/
int buscarBinariaVetor(Item mochila[],
                       int totalItens,
                       char nome[])
{
    int inicio = 0;
    int fim = totalItens - 1;

    compBinVetor = 0;

    while(inicio <= fim)
    {
        /* Calcula a posição central */
        int meio = (inicio + fim) / 2;

        compBinVetor++;

        int resultado =
            strcmp(mochila[meio].nome, nome);

        if(resultado == 0)
        {
            printf("\nItem encontrado!");
            printf("\nComparacoes: %d\n",
                   compBinVetor);

            return meio;
        }

        /* Decide qual metade continuar */
        if(resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem nao encontrado.");
    printf("\nComparacoes: %d\n",
           compBinVetor);

    return -1;
}

/*
=========================================================
FUNÇÃO: INSERIR ITEM NA LISTA

Cria um novo nó e o adiciona ao final
da lista encadeada.
=========================================================
*/
void inserirItemLista(No **inicio,
                      Item item)
{
    /* Aloca memória para o novo nó */
    No *novo =
        (No*) malloc(sizeof(No));

    novo->dados = item;
    novo->proximo = NULL;

    /* Caso a lista esteja vazia */
    if(*inicio == NULL)
    {
        *inicio = novo;
        return;
    }

    /* Percorre até o último nó */
    No *atual = *inicio;

    while(atual->proximo != NULL)
        atual = atual->proximo;

    /* Conecta o novo nó ao final */
    atual->proximo = novo;
}/*
=========================================================
FUNÇÃO: REMOVER ITEM DO VETOR

Localiza o item pelo nome e remove-o
deslocando os elementos seguintes.

Complexidade: O(n)
=========================================================
*/
void removerItemVetor(Item mochila[],
                      int *totalItens,
                      char nome[])
{
    int posicao = -1;

    /* Procura o item */
    for(int i = 0; i < *totalItens; i++)
    {
        if(strcmp(mochila[i].nome, nome) == 0)
        {
            posicao = i;
            break;
        }
    }

    /* Item não encontrado */
    if(posicao == -1)
    {
        printf("\nItem nao encontrado.\n");
        return;
    }

    /* Desloca os elementos */
    for(int i = posicao;
        i < *totalItens - 1;
        i++)
    {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--;

    printf("\nItem removido do vetor com sucesso!\n");
}



/*
=========================================================
FUNÇÃO: LISTAR LISTA

Percorre todos os nós da lista
encadeada exibindo seus dados.
=========================================================
*/
void listarLista(No *inicio)
{
    if(inicio == NULL)
    {
        printf("\nLista vazia.\n");
        return;
    }

    while(inicio != NULL)
    {
        printf("\nNome: %s",
               inicio->dados.nome);

        printf("\nTipo: %s",
               inicio->dados.tipo);

        printf("\nQuantidade: %d\n",
               inicio->dados.quantidade);

        inicio = inicio->proximo;
    }
}

/*
=========================================================
FUNÇÃO: BUSCA SEQUENCIAL NA LISTA

Percorre cada nó até encontrar
o item desejado.

Complexidade: O(n)
=========================================================
*/
No* buscarLista(No *inicio,
                char nome[])
{
    compSeqLista = 0;

    while(inicio != NULL)
    {
        compSeqLista++;

        if(strcmp(inicio->dados.nome,
                  nome) == 0)
        {
            printf("\nItem encontrado!");
            printf("\nComparacoes: %d\n",
                   compSeqLista);

            return inicio;
        }

        inicio = inicio->proximo;
    }

    printf("\nItem nao encontrado.");
    printf("\nComparacoes: %d\n",
           compSeqLista);

    return NULL;
}

/*
=========================================================
FUNÇÃO PRINCIPAL

Responsável pelo menu e pelo controle
geral do sistema.
=========================================================
*/
int main()
{
    /* Vetor para armazenamento sequencial */
    Item mochila[MAX_ITENS];

    /* Quantidade atual de itens */
    int totalItens = 0;

    /* Ponteiro inicial da lista */
    No *lista = NULL;

    int opcao;

    /* Menu principal */
    do
    {
        printf("\n===== MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA =====\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Item\n");
        printf("4 - Buscar Item\n");
        printf("5 - Ordenar Item\n");
        printf("6 - Busca Binaria\n");
        printf("7 - Inserir Lista\n");
        printf("8 - Listar Lista\n");
        printf("9 - Buscar Lista\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        /* Processa a opção escolhida */
        switch(opcao)
        {
            /* Implementações das opções */
        }

    } while(opcao != 0);

    return 0;
}