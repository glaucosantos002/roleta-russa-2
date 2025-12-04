#include "partida.h"
#include <stdlib.h>
#include <time.h>

void inicializarPartida(PARTIDA *partida, JOGADOR *j1, JOGADOR *j2) {
    partida->jogadorAtual = j1;
    partida->jogadorOponente = j2;
    partida->rodada = 1;

    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        partida->tambor[i] = 0;
    }
    int balaPos = rand() % 6;
    partida->tambor[balaPos] = 1;
    partida->posicaoTambor = 0;
}

int checarTiro(PARTIDA *partida, int atirarEmSiMesmo) {
    int tiroFatal = partida->tambor[partida->posicaoTambor];
    partida->posicaoTambor = (partida->posicaoTambor + 1) % 6;

    if (tiroFatal) {
        if (atirarEmSiMesmo) {
            perderVida(partida->jogadorAtual);
        } else {
            perderVida(partida->jogadorOponente);
        }
        JOGADOR *temp = partida->jogadorAtual;
        partida->jogadorAtual = partida->jogadorOponente;
        partida->jogadorOponente = temp;
        return 1;
    } else {
        if (!atirarEmSiMesmo) {
            JOGADOR *temp = partida->jogadorAtual;
            partida->jogadorAtual = partida->jogadorOponente;
            partida->jogadorOponente = temp;
        }
        return 0;
    }
}

void finalizarPartida(PARTIDA *partida) {
}