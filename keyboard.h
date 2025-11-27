// keyboard.h

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

/**
 * Protótipos das funções, com nomes EXATAMENTE iguais aos de keyboard.c
 * Note o 'C' maiúsculo em 'readChar' e 'H' em 'hit'.
 */
int Keyboard_readChar();
int Keyboard_read();
bool Keyboard_hit();

#endif // KEYBOARD_H