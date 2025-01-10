#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* A função gerarTabuleiro recebe como parâmetro a matriz 3x3 denominada como tabuleiro.
   Um contador é inicializado com o valor 1. Esse contador será usado para preencher a matriz com os números de 1 a 9.
   Os dois laços de repetição são utilizados para percorrer cada elemento da matriz. 
   O primeiro loop (i) percorre as linhas da matriz, enquanto o segundo loop (j) percorre as colunas. 
   A cada elemento[i][j], é atribuído um valor de 1 a 9 de acordo com o contador. 
   A expressão '0' + contador converte o número inteiro contador em seu correspondente caractere ASCII.
*/
void gerarTabuleiro(char tabuleiro[3][3]) {
    int contador = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = 0 + contador; 
            contador++;
        }
    }
}

void exibirTabuleiro(char tabuleiro[3][3]) {
    printf("Tabuleiro 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int verificarVitoria(char tabuleiro[3][3], char jogador) {
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

void jogar(char tabuleiro[3][3]) {
    int posicao;
    while (1) {
        printf("Escolha uma posição para colocar o X:");
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

void jogarComputador(char tabuleiro[3][3]) {
    int posicao;
    int linha, coluna;


    while (1) {
        posicao = rand() % 9;
        linha = posicao / 3;
        coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O';
            break;
        }
    }
}

int main() {
    char tabuleiro[3][3];
    gerarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro);

    srand(time(NULL));

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            jogar(tabuleiro);
        } else {
            jogarComputador(tabuleiro);
        }
        exibirTabuleiro(tabuleiro);

        if (verificarVitoria(tabuleiro, 'X')) {
            printf("Jogador X venceu!\n");
            return 0;
        } else if (verificarVitoria(tabuleiro, 'O')) {
            printf("Computador O venceu!\n");
            return 0;
        }
    }

    printf("Deu velha!\n");
    return 0;
}
