#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

char **tabuleiro; 
int i, j;

void gerarTabuleiro() {
    tabuleiro = malloc(3 * sizeof(char*)); 
    for (i = 0; i < 3; i++) {
        tabuleiro[i] = malloc(3 * sizeof(char)); 
    }

    int contador = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tabuleiro[i][j] = '0' + contador; 
            contador++;
        }
    }
}

void exibirTabuleiro() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
}

int entradaValida(char *entrada) {
    
    if (strlen(entrada) == 1 && isdigit(entrada[0])) {
        int posicao = entrada[0] - '0'; 
        return (posicao >= 1 && posicao <= 9); 
    }
    return 0; 
}

void jogarX(char **tabuleiro) {
    char entrada[10];

    while (1) {
        printf("Escolha uma posição para colocar o X (1-9): ");
        fgets(entrada, sizeof(entrada), stdin); 
        
        entrada[strcspn(entrada, "\n")] = 0;

        if (entradaValida(entrada)) {
            int posicao = entrada[0] - '0' - 1; 
            int linha = posicao / 3;
            int coluna = posicao % 3;

            if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
                tabuleiro[linha][coluna] = 'X'; 
                break;
            } else {
                printf("Posição já ocupada! Tente novamente.\n");
            }
        } else {
            printf("Entrada inválida! Tente novamente.\n");
        }
    }
}

void jogarO(char **tabuleiro) {
    int posicao;
    int linha, coluna;
    while (1) {
        posicao = rand() % 9;
        linha = posicao / 3;
        coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O';
            printf("O jogador O marcou a posição %d\n", posicao + 1); 
            break;
        }
    }
}

int verificarVitoria(char **tabuleiro, char jogador) {
    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1;
        }
    }
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1;
    }
    return 0;
}

int verificarEmpate(char **tabuleiro) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                return 0; 
            }
        }
    }
    return 1; 
}

void liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); 
    }
    free(tabuleiro); 
}

int main() {
    srand(time(NULL)); 
    gerarTabuleiro(); 
    printf("Boas vindas ao Jogo da Velha! Você é o jogador X!\n");
    exibirTabuleiro();

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            jogarX(tabuleiro);
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'X')) {
                printf("Jogador X venceu!\n");
                liberarTabuleiro();
                return 0;
            }
        } else {
            jogarO(tabuleiro );
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'O')) {
                printf("Jogador O venceu!\n");
                liberarTabuleiro();
                return 0;
            }
        }
        if (verificarEmpate(tabuleiro)) {
            printf("Empate!\n");
            liberarTabuleiro();
            return 0;
        }
    }
    liberarTabuleiro();
    return 0;
}
