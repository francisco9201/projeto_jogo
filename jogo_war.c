#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ======================================
// Estrutura do território
// ======================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ======================================
// Função para cadastrar territórios
// ======================================
void cadastrarTerritorios(Territorio* mapa, int quantidade) {

    for(int i = 0; i < quantidade; i++) {

        printf("\n=== TERRITÓRIO %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &(mapa + i)->tropas);

        getchar(); // limpa buffer
    }
}

// ======================================
// Função para exibir territórios
// ======================================
void exibirTerritorios(Territorio* mapa, int quantidade) {

    printf("\n========== MAPA ==========\n");

    for(int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", (mapa + i)->nome);
        printf("Cor: %s\n", (mapa + i)->cor);
        printf("Tropas: %d\n", (mapa + i)->tropas);
    }

    printf("\n==========================\n");
}

// ======================================
// Função de ataque
// ======================================
void atacar(Territorio* atacante, Territorio* defensor) {

    // Validação de cores
    if(strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar um território da mesma cor!\n");
        return;
    }

    // Verifica tropas mínimas
    if(atacante->tropas <= 1) {
        printf("\nO atacante não possui tropas suficientes!\n");
        return;
    }

    // Dados aleatórios
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n===== BATALHA =====\n");
    printf("Dado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);

    // Vitória do atacante
    if(dadoAtaque > dadoDefesa) {

        printf("\nO atacante venceu!\n");

        // Transfere cor
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante vai para o defensor
        int tropasTransferidas = atacante->tropas / 2;

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas;

    } else {

        printf("\nO defensor venceu!\n");

        // atacante perde uma tropa
        atacante->tropas--;

    }
}

// ======================================
// Liberação da memória
// ======================================
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ======================================
// Programa principal
// ======================================
int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);

    getchar();

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    // Verifica falha na alocação
    if(mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, quantidade);

    // Exibição inicial
    exibirTerritorios(mapa, quantidade);

    int atacanteIndex;
    int defensorIndex;

    printf("\n===== ATAQUE =====\n");

    printf("Escolha o território atacante (1 a %d): ", quantidade);
    scanf("%d", &atacanteIndex);

    printf("Escolha o território defensor (1 a %d): ", quantidade);
    scanf("%d", &defensorIndex);

    // Ajusta índices
    atacanteIndex--;
    defensorIndex--;

    // Validação
    if(atacanteIndex < 0 || atacanteIndex >= quantidade ||
       defensorIndex < 0 || defensorIndex >= quantidade) {

        printf("\nÍndices inválidos!\n");

    } else {

        atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);

        // Exibição após ataque
        exibirTerritorios(mapa, quantidade);
    }

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}