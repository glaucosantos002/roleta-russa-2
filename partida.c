#include "partida.h"
#include <stdlib.h> 
#include <time.h>   
#include <stdio.h>  
#include <stdbool.h>
#include <string.h>

#define TAMBOR_MIN 4
#define TAMBOR_MAX 8

// =========================================================
// FUNÇÕES DO HISTÓRICO (LISTA ENCADEADA)
// =========================================================

/**
 * Adiciona um novo nó ao histórico de partidas (Cabeça da lista).
 * REQUISITO: LISTAS ENCADEADAS (malloc e manipulação de ponteiros).
 */
void adicionarHistorico(PARTIDA *partida, JOGADOR *vencedor, int total_rodadas) {
    // 1. Alocação Dinâmica para o novo nó
    HistoricoNode *novo_no = (HistoricoNode*)malloc(sizeof(HistoricoNode));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o histórico.\n");
        return;
    }
    
    // 2. Preenchimento dos dados
    strncpy(novo_no->vencedor, vencedor->nome, MAX_NOME - 1);
    novo_no->vencedor[MAX_NOME - 1] = '\0';
    novo_no->rodadas = total_rodadas;
    
    // 3. Conexão na lista (Insere na cabeça)
    novo_no->proximo = partida->historico;
    partida->historico = novo_no;
}

/**
 * Libera a memória de todos os nós do histórico.
 * REQUISITO: LIBERAÇÃO DE MEMÓRIA (free).
 */
void liberarHistorico(HistoricoNode *historico) {
    HistoricoNode *atual = historico;
    HistoricoNode *proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// =========================================================
// FUNÇÕES DA PARTIDA
// =========================================================

void inicializarPartida(PARTIDA *partida, JOGADOR *p1, JOGADOR *p2) {
    srand(time(NULL));
    
    partida->rodada_atual = 1;
    partida->jogador_atual_idx = rand() % 2; 
    partida->jogador_atual_ptr = (partida->jogador_atual_idx == 0) ? p1 : p2;
    partida->historico = NULL; 
    partida->tambor = NULL;    
    
    rolarTambor(partida);
}

void rolarTambor(PARTIDA *partida) {
    if (partida->tambor != NULL) {
        free(partida->tambor); 
        partida->tambor = NULL;
    }
    
    partida->max_balas = (rand() % (TAMBOR_MAX - TAMBOR_MIN + 1)) + TAMBOR_MIN;
    
    partida->tambor = (int*)malloc(partida->max_balas * sizeof(int));
    if (partida->tambor == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o tambor.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < partida->max_balas; i++) {
        partida->tambor[i] = 0; 
    }
    
    int pos_bala = rand() % partida->max_balas;
    partida->tambor[pos_bala] = 1;
    
    if (rand() % 2 == 0 && partida->max_balas > 1) {
         int pos_bala2;
         do {
            pos_bala2 = rand() % partida->max_balas;
         } while (pos_bala2 == pos_bala);
         partida->tambor[pos_bala2] = 1;
    }

    partida->bala_atual_idx = 0;
}

bool checarTiro(PARTIDA *partida) {
    if (partida->bala_atual_idx >= partida->max_balas) {
        rolarTambor(partida); 
        partida->bala_atual_idx = 0;
    }
    
    bool bala_encontrada = (partida->tambor[partida->bala_atual_idx] == 1);
    
    partida->bala_atual_idx++;
    
    return bala_encontrada;
}

void executarTurno(PARTIDA *partida, JOGADOR *p1, JOGADOR *p2) {
    /* Esta função foi movida para main.c para facilitar a integração com a UI. */
}

void finalizarPartida(PARTIDA *partida, JOGADOR *vencedor) { 
    // Salva o resultado no histórico (Lista Encadeada)
    adicionarHistorico(partida, vencedor, partida->rodada_atual); 

    // Libera a memória alocada dinamicamente
    if (partida->tambor != NULL) {
        free(partida->tambor);
        partida->tambor = NULL;
    }
    // Libera a memória da lista encadeada (Obrigatório!)
    liberarHistorico(partida->historico); 
}