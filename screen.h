#ifndef SCREEN_H
#define SCREEN_H

// Códigos de Cores ANSI
#define COLOR_BLACK 30
#define COLOR_RED 31
#define COLOR_GREEN 32
#define COLOR_YELLOW 33
#define COLOR_BLUE 34
#define COLOR_MAGENTA 35
#define COLOR_CYAN 36
#define COLOR_WHITE 37

void Screen_clear();
void Screen_goto(int row, int col);
void Screen_fgcolor(int color);
void Screen_resetcolor();

#endif