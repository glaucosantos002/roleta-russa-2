# 🔫 SHOOT 2 KILL - Roleta Russa em C

Um jogo de Roleta Russa implementado em linguagem C, projetado para rodar em terminais compatíveis com ANSI/POSIX (como Linux, macOS ou **WSL/Ubuntu no Windows**). O jogo utiliza a interface de linha de comando para exibir painéis, animações e o placar.

---

aluno: Glauco santos

slide:https://www.canva.com/design/DAG2R9ArVmk/GserO1H4skGnq3TMgfBArA/edit?utm_content=DAG2R9ArVmk&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton

## 🎲 Sobre o Jogo

**SHOOT 2 KILL** é uma adaptação em texto do clássico jogo de Roleta Russa para dois jogadores.

* **Objetivo:** Sobreviver ao seu oponente.
* **Mecânica:** Os jogadores se revezam com uma espingarda, carregada com um número aleatório de cartuchos (balas VAZIAS ou FATAIS).
* **Decisão:** Em seu turno, o jogador deve escolher:
    1.  **Atirar em SI:** Se for um CLIQUE SECO, a vez continua com o mesmo jogador. Se for um TIRO FATAL, ele perde uma vida e a vez passa.
    2.  **Atirar no Oponente:** Se for um CLIQUE SECO, a vez passa para o oponente. Se for um TIRO FATAL, o oponente perde uma vida.
* **Vidas:** Cada jogador começa com 3 vidas. O último a ter vidas restantes vence.
* **Placar:** O jogo salva o placar dos vencedores em um arquivo (`top_scores.dat`).

---

## 💻 Como Compilar e Executar (Usando GCC no WSL)

### Pré-requisitos

Você precisa ter o **GCC** (GNU Compiler Collection) instalado no seu ambiente Linux (WSL, Ubuntu, etc.).

### 1. Compilar

No terminal, navegue até a pasta raiz do projeto (`/jogo`) e use o seguinte comando de compilação. Ele junta todos os arquivos (`.c`) do projeto em um único executável chamado `jogo`:

```bash
gcc main.c jogador.c partida.c bibliotecas/screen.c bibliotecas/keyboard.c bibliotecas/timer.c -o jogo -lm

link:https://youtu.be/QazTcCGRn9g
