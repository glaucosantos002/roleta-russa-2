// bibliotecas/timer.c
// Implementação para Linux/WSL

#include <time.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Pausa a execução do programa pelo tempo especificado.
 * @param milisegundos O tempo de pausa em milissegundos.
 */
void Timer_sleep(int milisegundos) {
    if (milisegundos <= 0) {
        return;
    }

    struct timespec ts;
    // Converte milissegundos para segundos e nanossegundos
    ts.tv_sec = milisegundos / 1000;
    ts.tv_nsec = (milisegundos % 1000) * 1000000; // 1 ms = 1,000,000 ns

    // A função nanosleep pausa o processo
    nanosleep(&ts, NULL);
}