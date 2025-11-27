#ifndef JOGADOR_H
#define JOGADOR_H

#define MAX_NOME 50
#define VIDAS_INICIAIS 3

typedef struct {
    char nome[MAX_NOME];
    int vidas;
    int vitorias;
} JOGADOR;

// Funções do Jogador
void inicializarJogador(JOGADOR *jogador, const char *nome);
void perderVida(JOGADOR *jogador);
void ganharVitoria(JOGADOR *jogador);

#endif