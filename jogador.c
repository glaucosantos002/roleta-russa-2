#include "jogador.h"
#include <string.h>

void inicializarJogador(JOGADOR *jogador, const char *nome) {
    strncpy(jogador->nome, nome, 49);
    jogador->nome[49] = '\0';
    jogador->vidas = 3;
    jogador->vitorias = 0;
}

void perderVida(JOGADOR *jogador) {
    if (jogador->vidas > 0) {
        jogador->vidas--;
    }
}

void ganharVitoria(JOGADOR *jogador) {
    jogador->vitorias++;
}