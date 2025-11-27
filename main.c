// main.c
// Jogo Roleta Russa - Versão Estável Retornada

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <string.h>

// Headers do Projeto
#include "jogador.h"
#include "partida.h"

// UI Headers (bibliotecas)
#include "bibliotecas/screen.h"
#include "bibliotecas/keyboard.h"
#include "bibliotecas/timer.h"

// =========================================================
// CONSTANTES E ESTRUTURAS AUXILIARES
// =========================================================
#define PAINEL_ALTURA 10
#define PAINEL_LARGURA 80
#define ARQUIVO_PLACAR "top_scores.dat" // Nome do arquivo

// Estrutura para salvar/ler o placar
typedef struct {
    char nome[MAX_NOME];
    int vitorias;
} PlacarRecord;

// Variável Global para o Painel (Requisito MATRIZES)
char painel_tela[PAINEL_ALTURA][PAINEL_LARGURA];

// =========================================================
// FUNÇÕES DE UI E ANIMAÇÃO
// =========================================================

void desenharBoneco(int col, bool is_alive) {
    int row = 2; 
    if (is_alive) {
        painel_tela[row][col]      = 'O';
        painel_tela[row + 1][col] = '|';
        painel_tela[row + 2][col - 1] = '/';
        painel_tela[row + 2][col + 1] = '\\';
        painel_tela[row + 3][col - 1] = '/';
        painel_tela[row + 3][col + 1] = '\\';
    } else {
        painel_tela[row][col]      = 'X'; 
        painel_tela[row + 1][col - 1] = '/';
        painel_tela[row + 1][col + 1] = '\\';
        painel_tela[row + 2][col] = '_'; 
        painel_tela[row + 3][col] = '~'; 
    }
}

void construirPainel(JOGADOR *p1, JOGADOR *p2) {
    for (int i = 0; i < PAINEL_ALTURA; i++) {
        for (int j = 0; j < PAINEL_LARGURA; j++) {
            painel_tela[i][j] = ' ';
        }
    }
    for (int j = 0; j < PAINEL_LARGURA; j++) {
        painel_tela[0][j] = '=';
        painel_tela[PAINEL_ALTURA - 1][j] = '=';
    }
    
    char info_p1[80]; 
    char info_p2[80]; 
    
    // As strings foram ajustadas para caberem em 80 caracteres.
    sprintf(info_p1, "JOGADOR 1: %s | Vidas: %d", p1->nome, p1->vidas);
    sprintf(info_p2, "JOGADOR 2: %s | Vidas: %d", p2->nome, p2->vidas);

    strncpy(&painel_tela[1][2], info_p1, strlen(info_p1));
    strncpy(&painel_tela[1][PAINEL_LARGURA / 2 + 5], info_p2, strlen(info_p2));

    desenharBoneco(20, p1->vidas > 0); 
    desenharBoneco(60, p2->vidas > 0); 
}

void imprimirPainel() {
    Screen_clear();
    Screen_goto(1, 1);
    
    for (int i = 0; i < PAINEL_ALTURA; i++) {
        for (int j = 0; j < PAINEL_LARGURA; j++) {
            putchar(painel_tela[i][j]);
        }
        printf("\n");
    }
    fflush(stdout);
}

void pedirNomeJogador(int numero, char *nome_buffer) {
    Screen_clear();
    Screen_goto(5, 5);
    Screen_fgcolor(COLOR_YELLOW);
    printf("SHOOT 2 KILL - Roleta Russa");
    Screen_resetcolor();
    
    Screen_goto(8, 5);
    printf("Jogador %d, digite seu nome (máx. %d caracteres): ", numero, MAX_NOME - 1);
    
    fflush(stdin); // Limpeza de buffer (Versão que funcionou para você)
    if (fgets(nome_buffer, MAX_NOME, stdin) != NULL) {
        size_t len = strlen(nome_buffer);
        if (len > 0 && nome_buffer[len-1] == '\n') {
            nome_buffer[len-1] = '\0';
        }
    }
    fflush(stdout);
}

// MODO ESTÁVEL: Requer ENTER
int pedirDecisaoJogador(JOGADOR *atual, JOGADOR *oponente) {
    char input_buffer[10];
    int decisao_int = 0;

    Screen_goto(PAINEL_ALTURA + 2, 1);
    Screen_fgcolor(COLOR_WHITE);
    printf("É a vez de %s. Escolha o alvo:\n", atual->nome);
    Screen_fgcolor(COLOR_YELLOW);
    printf("   [1] Atirar em SI (Pode ganhar a vez)\n");
    printf("   [2] Atirar em %s (Pode matá-lo)\n", oponente->nome);
    Screen_resetcolor();
    printf("   Digite '1' ou '2' e pressione ENTER: ");
    
    fflush(stdout); 
    
    do {
        fflush(stdin); // Limpeza de buffer (Versão que funcionou para você)

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            continue; 
        }

        if (sscanf(input_buffer, "%d", &decisao_int) == 1) {
            if (decisao_int == 1 || decisao_int == 2) {
                break; 
            }
        }
        
        Screen_goto(PAINEL_ALTURA + 6, 1);
        Screen_fgcolor(COLOR_RED);
        printf("ERRO: Escolha inválida. Digite '1' ou '2'.");
        Screen_goto(PAINEL_ALTURA + 5, 36); 
        Screen_fgcolor(COLOR_WHITE);
    } while (true);

    Screen_goto(PAINEL_ALTURA + 6, 1);
    printf("                                              ");
    
    fflush(stdout); 

    return (decisao_int == 1) ? 0 : 1; 
}

void exibirMensagem(const char *msg, int cor) {
    Screen_goto(PAINEL_ALTURA + 4, 1);
    Screen_fgcolor(cor);
    printf("STATUS: %s", msg);
    fflush(stdout); 
    Timer_sleep(3000); 
    
    Screen_goto(PAINEL_ALTURA + 4, 1);
    printf("                                                                            "); 
    Screen_resetcolor();
}

// =========================================================
// FUNÇÕES DE E/S DE ARQUIVO (PLACAR)
// =========================================================

void salvarPlacar(JOGADOR *vencedor) {
    FILE *file = fopen(ARQUIVO_PLACAR, "ab"); 
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de placar para escrita.\n");
        return;
    }
    
    PlacarRecord record;
    strncpy(record.nome, vencedor->nome, MAX_NOME);
    record.vitorias = vencedor->vitorias + 1;
    
    fwrite(&record, sizeof(PlacarRecord), 1, file);
    
    fclose(file);
}

void exibirPlacar() {
    FILE *file = fopen(ARQUIVO_PLACAR, "rb"); 
    if (file == NULL) {
        Screen_goto(PAINEL_ALTURA + 10, 1);
        printf("Nenhum placar encontrado. Jogue uma partida para criar um.\n");
        return;
    }
    
    PlacarRecord record;
    Screen_goto(PAINEL_ALTURA + 10, 1);
    Screen_fgcolor(COLOR_CYAN);
    printf("===== TOP SCORES ENCONTRADOS =====\n");
    int count = 0;

    while (fread(&record, sizeof(PlacarRecord), 1, file) == 1) {
        printf("   %s - %d vitórias\n", record.nome, record.vitorias);
        count++;
    }
    
    if (count == 0) {
        printf("   (Nenhum registro no arquivo)\n");
    }
    
    fclose(file);
    Screen_resetcolor();
}


// =========================================================
// LOOP PRINCIPAL E EXECUÇÃO
// =========================================================

int main() {
    char nome_p1[MAX_NOME];
    char nome_p2[MAX_NOME];
    JOGADOR jogador1;
    JOGADOR jogador2;
    PARTIDA partida;
    JOGADOR *jogador_atual;
    JOGADOR *jogador_oponente;
    int decisao;
    bool tiro_fatal;

    // --- 1. ENTRADA DE DADOS ---
    pedirNomeJogador(1, nome_p1);
    pedirNomeJogador(2, nome_p2);

    // --- 2. INICIALIZAÇÃO ---
    inicializarJogador(&jogador1, nome_p1);
    inicializarJogador(&jogador2, nome_p2);
    inicializarPartida(&partida, &jogador1, &jogador2);
    
    // --- 3. LOOP PRINCIPAL DO JOGO ---
    while (jogador1.vidas > 0 && jogador2.vidas > 0) {
        
        jogador_atual = partida.jogador_atual_ptr;
        jogador_oponente = (jogador_atual == &jogador1) ? &jogador2 : &jogador1;

        construirPainel(&jogador1, &jogador2);
        imprimirPainel();
        
        decisao = pedirDecisaoJogador(jogador_atual, jogador_oponente);
        tiro_fatal = checarTiro(&partida); 
        
        if (decisao == 0) { // Atirar em si mesmo (Decisao == 0 => 1)
            if (tiro_fatal) {
                perderVida(jogador_atual);
                construirPainel(&jogador1, &jogador2);
                imprimirPainel();
                exibirMensagem("BOOM! Você levou um tiro!", COLOR_RED);
            } else {
                exibirMensagem("CLIQUE SECO! Sua vez continua.", COLOR_GREEN);
                continue; 
            }
        } else { // Atirar no oponente (Decisao == 1 => 2)
            if (tiro_fatal) {
                perderVida(jogador_oponente);
                construirPainel(&jogador1, &jogador2);
                imprimirPainel();
                exibirMensagem("BANG! Oponente levou um tiro!", COLOR_RED);
            } else {
                exibirMensagem("CLIQUE SECO! A vez passa.", COLOR_GREEN);
            }
        }
        
        partida.jogador_atual_ptr = jogador_oponente;
        partida.rodada_atual++;
    }

    // --- 4. FIM DE JOGO ---
    JOGADOR *vencedor = (jogador1.vidas > 0) ? &jogador1 : &jogador2;
    
    ganharVitoria(vencedor);
    salvarPlacar(vencedor);
    finalizarPartida(&partida, vencedor); 

    construirPainel(&jogador1, &jogador2);
    imprimirPainel();
    Screen_goto(PAINEL_ALTURA + 6, 1);
    Screen_fgcolor(COLOR_YELLOW);
    printf("FIM DE JOGO! O VENCEDOR É: %s!\n", vencedor->nome);
    Screen_resetcolor();
    
    exibirPlacar();
    
    Screen_goto(PAINEL_ALTURA + 15, 1);
    printf("Pressione qualquer tecla para sair...");
    fflush(stdin); // Limpa o buffer antes de ler a tecla final
    Keyboard_readChar(); 
    
    Screen_clear();
    return 0;
}