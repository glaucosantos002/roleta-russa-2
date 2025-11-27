// bibliotecas/screen.c
// Implementação Otimizada FINAL para Linux/WSL

#include <stdio.h>
#include "screen.h"

void Screen_clear() {
    // Comando ANSI padrão: Reseta cor, limpa tela e move cursor para (1, 1).
    // Usamos fflush(stdout) para garantir que a instrução de limpeza seja executada imediatamente.
    printf("\033[0m\033[2J\033[H"); 
    fflush(stdout);
}

void Screen_goto(int row, int col) {
    // Comando ANSI para mover cursor.
    printf("\033[%d;%dH", row + 1, col + 1);
}

void Screen_fgcolor(int color) {
    // Define a cor de primeiro plano (foreground).
    printf("\033[%dm", color);
}

void Screen_resetcolor() {
    // Reseta cor para o padrão do terminal.
    printf("\033[0m"); 
}