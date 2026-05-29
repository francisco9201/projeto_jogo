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
// Cadastro dos territórios
// ======================================
void cadastrarTerritorios(Territorio* mapa, int quantidade) {

    for(int i = 0; i < quantidade; i++) {

        printf("\n=== TERRITÓRIO %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        getchar();
    }
}

// ======================================
// Exibe o mapa
// ======================================
void exibirMapa(Territorio* mapa, int quantidade) {

    printf("\n========== MAPA ==========\n");

    for(int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n==========================\n");
}

// ======================================
// Sorteia missão
// ======================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {

    int indice = rand() % totalMissoes;

    strcpy(destino, missoes[indice]);
}

// ======================================
// Exibe missão
// ======================================
void exibirMissao(char* missao) {

    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
    printf("======================\n");
}

// ======================================
// Função de ataque
// ======================================
void atacar(Territorio* atacante, Territorio* defensor) {

    // Não pode atacar mesma cor
    if(strcmp(atacante->cor, defensor->cor) == 0) {

        printf("\nVocê não pode atacar um território aliado!\n");
        return;
    }

    // Precisa ter tropas suficientes
    if(atacante->tropas <= 1) {

        printf("\nTropas insuficientes para atacar!\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n===== BATALHA =====\n");
    printf("Dado atacante: %d\n", dadoAtaque);
    printf("Dado defensor: %d\n", dadoDefesa);

    // Vitória atacante
    if(dadoAtaque > dadoDefesa) {

        printf("\nO atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas;

    } else {

        printf("\nO defensor venceu!\n");

        atacante->tropas--;
    }
}

// ======================================
// Verifica missão
// ======================================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Missão: dominar 3 territórios azuis
    if(strcmp(missao, "Conquistar 3 territorios azuis") == 0) {

        int contador = 0;

        for(int i = 0; i < tamanho; i++) {

            if(strcmp(mapa[i].cor, "Azul") == 0) {
                contador++;
            }
        }

        return contador >= 3;
    }

    // Missão: dominar 2 territórios vermelhos
    if(strcmp(missao, "Conquistar 2 territorios vermelhos") == 0) {

        int contador = 0;

        for(int i = 0; i < tamanho; i++) {

            if(strcmp(mapa[i].cor, "Vermelho") == 0) {
                contador++;
            }
        }

        return contador >= 2;
    }

    // Missão: possuir 15 tropas
    if(strcmp(missao, "Possuir ao menos 15 tropas") == 0) {

        int total = 0;

        for(int i = 0; i < tamanho; i++) {

            total += mapa[i].tropas;
        }

        return total >= 15;
    }

    // Missão: conquistar metade do mapa
    if(strcmp(missao, "Conquistar metade dos territorios") == 0) {

        int contador = 0;

        for(int i = 0; i < tamanho; i++) {

            if(strcmp(mapa[i].cor, "Azul") == 0) {
                contador++;
            }
        }

        return contador >= tamanho / 2;
    }

    // Missão: eliminar tropas verdes
    if(strcmp(missao, "Eliminar territorios verdes") == 0) {

        for(int i = 0; i < tamanho; i++) {

            if(strcmp(mapa[i].cor, "Verde") == 0) {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

// ======================================
// Liberação de memória
// ======================================
void liberarMemoria(Territorio* mapa, char* missaoJogador) {

    free(mapa);
    free(missaoJogador);
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

    // Validação
    if(quantidade <= 0) {

        printf("Quantidade inválida!\n");
        return 1;
    }

    // Alocação dinâmica do mapa
    Territorio* mapa =
        (Territorio*) calloc(quantidade, sizeof(Territorio));

    if(mapa == NULL) {

        printf("Erro de memória!\n");
        return 1;
    }

    // Vetor de missões
    char* missoes[] = {

        "Conquistar 3 territorios azuis",
        "Conquistar 2 territorios vermelhos",
        "Possuir ao menos 15 tropas",
        "Conquistar metade dos territorios",
        "Eliminar territorios verdes"
    };

    int totalMissoes = 5;

    // Missão do jogador (alocação dinâmica)
    char* missaoJogador =
        (char*) malloc(100 * sizeof(char));

    if(missaoJogador == NULL) {

        printf("Erro ao alocar missão!\n");

        free(mapa);
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, quantidade);

    // Sorteia missão
    atribuirMissao(
        missaoJogador,
        missoes,
        totalMissoes
    );

    // Exibe missão apenas uma vez
    exibirMissao(missaoJogador);

    // Exibe mapa
    exibirMapa(mapa, quantidade);

    int atacanteIndex;
    int defensorIndex;

    printf("\n===== ATAQUE =====\n");

    printf("Escolha o território atacante (1 a %d): ",
           quantidade);

    scanf("%d", &atacanteIndex);

    printf("Escolha o território defensor (1 a %d): ",
           quantidade);

    scanf("%d", &defensorIndex);

    atacanteIndex--;
    defensorIndex--;

    // Validação
    if(atacanteIndex < 0 || atacanteIndex >= quantidade ||
       defensorIndex < 0 || defensorIndex >= quantidade ||
       atacanteIndex == defensorIndex) {

        printf("\nÍndices inválidos!\n");

    } else {

        atacar(
            &mapa[atacanteIndex],
            &mapa[defensorIndex]
        );

        exibirMapa(mapa, quantidade);

        // Verificação automática da missão
        if(verificarMissao(
            missaoJogador,
            mapa,
            quantidade)) {

            printf("\n========================\n");
            printf("MISSÃO CUMPRIDA!\n");
            printf("VOCÊ VENCEU O JOGO!\n");
            printf("========================\n");

        } else {

            printf("\nMissão ainda não concluída.\n");
        }
    }

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}