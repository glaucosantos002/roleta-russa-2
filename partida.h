// partida.h

#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdbool.h>
#include "jogador.h" // Necessário para referenciar a struct JOGADOR

// =========================================================
// ESTRUTURAS (Requisito Structs e Listas Encadeadas)
// =========================================================

// Estrutura para a Lista Encadeada (Histórico)
typedef struct HistoricoNode {
    char vencedor[MAX_NOME];
    int rodadas;
    struct HistoricoNode *proximo;
} HistoricoNode;

// Estrutura Principal da Partida
typedef struct {
    int rodada_atual;
    int jogador_atual_idx; // 0 ou 1
    JOGADOR *jogador_atual_ptr; // Ponteiro para o jogador atual (Requisito Ponteiros)
    
    // Para Alocação Dinâmica do Tambor (Requisito Alocação Dinâmica)
    int *tambor;        // Array dinâmico de 0s e 1s (balas)
    int max_balas;      // Tamanho atual do tambor
    int bala_atual_idx; // <<-- ESTE CAMPO É O QUE ESTAVA FALTANDO/ERRADO!
    
    HistoricoNode *historico; // Cabeça da Lista Encadeada
} PARTIDA;

// =========================================================
// PROTÓTIPOS DE FUNÇÃO
// =========================================================

void inicializarPartida(PARTIDA *partida, JOGADOR *p1, JOGADOR *p2);
void rolarTambor(PARTIDA *partida);
bool checarTiro(PARTIDA *partida); 
void executarTurno(PARTIDA *partida, JOGADOR *p1, JOGADOR *p2);
void finalizarPartida(PARTIDA *partida, JOGADOR *vencedor);

// Funções do Histórico (Lista Encadeada)
void adicionarHistorico(PARTIDA *partida, JOGADOR *vencedor, int total_rodadas);
void liberarHistorico(HistoricoNode *historico);

#endif // PARTIDA_H