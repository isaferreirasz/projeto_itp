#include <stdio.h>
#include <stdlib.h>

char **tabuleiro; 
int i, j;

int gerarTabuleiro() {
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
    return 0;
}

int exibirTabuleiro() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
    return 0;
}

void jogar(char **tabuleiro) {
    int posicao;
    while (1) {
        printf("Escolha uma posição para colocar o X (1-9): ");
        scanf("%d", &posicao);
        posicao--;
        if (posicao >= 0 && posicao < 9) {
            int linha = posicao / 3;
            int coluna = posicao % 3;

            if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
                tabuleiro[linha][coluna] = 'X'; 
                break;
            } else {
                printf("Posição já ocupada! Tente novamente.\n");
            }
        } else {
            printf("Posição inválida! Tente novamente.\n");
        }
    }
}

int liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); 
    }
    free(tabuleiro); 
    return 0;
}

int main() {
    gerarTabuleiro(); 
    exibirTabuleiro(); 
    jogar(tabuleiro); 
    exibirTabuleiro(); 
    liberarTabuleiro(); 
    return 0;
}
