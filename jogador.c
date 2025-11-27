#include "jogador.h"
#include <string.h>
#include <stdio.h>

/**
 * Inicializa um jogador.
 * * REQUISITO: PONTEIROS (Modifica o struct via ponteiro).
 */
void inicializarJogador(JOGADOR *jogador, const char *nome) {
    strncpy(jogador->nome, nome, MAX_NOME - 1);
    jogador->nome[MAX_NOME - 1] = '\0';
    
    jogador->vidas = VIDAS_INICIAIS;
    jogador->vitorias = 0;
}

/**
 * Decrementa a vida do jogador.
 * * REQUISITO: PONTEIROS (Modifica o struct via ponteiro).
 */
void perderVida(JOGADOR *jogador) {
    if (jogador->vidas > 0) {
        jogador->vidas--;
    }
}

/**
 * Incrementa o placar de vitórias do jogador.
 */
void ganharVitoria(JOGADOR *jogador) {
    jogador->vitorias++;
}