// bibliotecas/keyboard.c
// Implementação para Linux/WSL

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h> 

// Variável global para armazenar as configurações originais do terminal
static struct termios original_terminal_settings;
static bool terminal_mode_set = false;

// Função para restaurar as configurações originais do terminal no final do programa
void reset_terminal_mode() {
    if (terminal_mode_set) {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
    }
}

// Função para configurar o terminal para modo "raw" (sem buffer)
void set_terminal_mode() {
    if (terminal_mode_set) return;

    struct termios new_settings;
    
    tcgetattr(STDIN_FILENO, &original_terminal_settings);
    atexit(reset_terminal_mode);
    
    new_settings = original_terminal_settings;
    
    // Desliga o modo canonical (espera por ENTER) e o ECHO (eco de caracteres)
    new_settings.c_lflag &= ~(ICANON | ECHO);
    
    // Define MIN = 1 (mínimo de 1 caractere a ser lido) e TIME = 0 (sem timeout)
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    terminal_mode_set = true;
}

/**
 * @brief Lê um caractere do teclado sem precisar de ENTER.
 * @return O código ASCII do caractere lido.
 */
int Keyboard_readChar() {
    set_terminal_mode(); 
    // Como o loop principal agora usa fgets/ENTER, podemos manter este getchar()
    // para o prompt final 'Pressione qualquer tecla para sair...'
    return getchar(); 
}

// Funções de compatibilidade (não usadas no main.c)
int Keyboard_read() { return Keyboard_readChar(); }
bool Keyboard_hit() { return false; }