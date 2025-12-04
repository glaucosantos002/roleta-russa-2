#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[50];
    int vidas;
    int vitorias;
} JOGADOR;

void inicializarJogador(JOGADOR *jogador, const char *nome);
void perderVida(JOGADOR *jogador);
void ganharVitoria(JOGADOR *jogador);

#endif