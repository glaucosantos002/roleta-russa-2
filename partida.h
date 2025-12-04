#ifndef PARTIDA_H
#define PARTIDA_H

#include "jogador.h"

typedef struct {
    JOGADOR *jogadorAtual;
    JOGADOR *jogadorOponente;
    int tambor[6];
    int posicaoTambor;
    int rodada;
} PARTIDA;

void inicializarPartida(PARTIDA *partida, JOGADOR *j1, JOGADOR *j2);
int checarTiro(PARTIDA *partida, int atirarEmSiMesmo);
void finalizarPartida(PARTIDA *partida);

#endif