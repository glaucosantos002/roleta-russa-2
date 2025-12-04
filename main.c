#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "jogador.h"
#include "partida.h"

typedef struct NODE_HISTORICO {
    int rodada;
    char vencedor[50];
    struct NODE_HISTORICO *proximo;
} NODE_HISTORICO;

NODE_HISTORICO *historicoHead = NULL;

void desenharBoneco(int x, int y, int vidas) {
    if (vidas <= 0) {
        screenGotoxy(x, y);
        printf("💥");
        screenGotoxy(x, y + 1);
        printf("💀");
        screenGotoxy(x, y + 2);
        printf("   ");
    } else {
        screenGotoxy(x, y);
        printf(" O ");
        screenGotoxy(x, y + 1);
        printf("/|\\");
        screenGotoxy(x, y + 2);
        printf("/ \\");
    }
}

void desenharPainel(JOGADOR *j1, JOGADOR *j2, PARTIDA *partida) {
    screenClear();
    screenGotoxy(0, 0);
    printf("=== SHOOT 2 KILL - ROLETA RUSSA ===");
    screenGotoxy(2, 2);
    printf("%s: %d vidas", j1->nome, j1->vidas);
    screenGotoxy(42, 2);
    printf("%s: %d vidas", j2->nome, j2->vidas);
    desenharBoneco(5, 4, j1->vidas);
    desenharBoneco(45, 4, j2->vidas);
    screenGotoxy(2, 8);
    printf("Rodada %d - Vez de %s", partida->rodada, partida->jogadorAtual->nome);
    screenGotoxy(2, 10);
    printf("[1] Atirar em si mesmo");
    screenGotoxy(2, 11);
    printf("[2] Atirar no oponente");
    screenGotoxy(2, 13);
    printf("Escolha sua ação (1 ou 2): ");
    screenUpdate();
}

void salvarPlacar(const char *vencedor) {
    FILE *fp = fopen("top_scores.dat", "ab");
    if (!fp) return;
    char nome[50];
    strncpy(nome, vencedor, 49);
    nome[49] = '\0';
    fwrite(nome, 1, 50, fp);
    fclose(fp);
}

void adicionarHistorico(NODE_HISTORICO **head, int rodada, const char *vencedor) {
    NODE_HISTORICO *novo = (NODE_HISTORICO*)malloc(sizeof(NODE_HISTORICO));
    novo->rodada = rodada;
    strncpy(novo->vencedor, vencedor, 49);
    novo->vencedor[49] = '\0';
    novo->proximo = *head;
    *head = novo;
}

void exibirHistorico(NODE_HISTORICO *head) {
    NODE_HISTORICO *current = head;
    int count = 1;
    while (current) {
        printf("%d. Rodada %d - Vencedor: %s\n", count++, current->rodada, current->vencedor);
        current = current->proximo;
    }
}

int main() {
    screenInit(1);
    keyboardInit();

    JOGADOR *j1 = (JOGADOR*)malloc(sizeof(JOGADOR));
    JOGADOR *j2 = (JOGADOR*)malloc(sizeof(JOGADOR));

    printf("Digite o nome do Jogador 1: ");
    scanf("%49s", j1->nome);
    printf("Digite o nome do Jogador 2: ");
    scanf("%49s", j2->nome);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    inicializarJogador(j1, j1->nome);
    inicializarJogador(j2, j2->nome);

    PARTIDA partida;
    inicializarPartida(&partida, j1, j2);

    while (j1->vidas > 0 && j2->vidas > 0) {
        desenharPainel(j1, j2, &partida);

        int escolha;
        do {
            escolha = readch();
        } while (escolha != '1' && escolha != '2');

        while (keyhit()) {
            readch();
        }

        int atirarEmSiMesmo = (escolha == '1');
        const char *alvo_nome = atirarEmSiMesmo ?
            partida.jogadorAtual->nome :
            partida.jogadorOponente->nome;

        int tiroFatal = checarTiro(&partida, atirarEmSiMesmo);

        screenGotoxy(2, 15);
        printf("Você escolheu: [%c]", escolha);
        screenUpdate();
        timerSleep(400);

        desenharPainel(j1, j2, &partida);

        if (tiroFatal) {
            screenGotoxy(2, 17);
            printf("💥 %s PERDEU UMA VIDA! 💥", alvo_nome);
            screenUpdate();
            timerSleep(600);
        }
    }

    JOGADOR *vencedor = (j1->vidas > 0) ? j1 : j2;
    screenClear();
    screenGotoxy(10, 5);
    printf("🎉 %s VENCEU! 🎉", vencedor->nome);
    ganharVitoria(vencedor);

    adicionarHistorico(&historicoHead, partida.rodada, vencedor->nome);
    salvarPlacar(vencedor->nome);

    screenGotoxy(10, 8);
    printf("Pressione qualquer tecla para sair...");
    readch();

    screenGotoxy(10, 10);
    printf("=== HISTÓRICO ===");
    exibirHistorico(historicoHead);

    free(j1);
    free(j2);
    NODE_HISTORICO *current = historicoHead;
    while (current) {
        NODE_HISTORICO *next = current->proximo;
        free(current);
        current = next;
    }

    screenDestroy();
    keyboardDestroy();
    return 0;
}