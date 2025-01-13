#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para armazenar uma jogada
typedef struct {
    int linha;
    int coluna;
    char jogador;
} Jogada;

// Função para alocar o tabuleiro dinamicamente
char** alocarTabuleiro() {
    char** tabuleiro = (char**)malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) {
        tabuleiro[i] = (char*)malloc(3 * sizeof(char));
    }
    return tabuleiro;
}

// Função para alocar o vetor de jogadas
Jogada* alocarHistorico(int tamanho) {
    return (Jogada*)malloc(tamanho * sizeof(Jogada));
}

// Função para liberar a memória do tabuleiro
void liberarTabuleiro(char** tabuleiro) {
    for (int i = 0; i < 3; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void gerarTabuleiro(char** tabuleiro) {
    int contador = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = '0' + contador;
            contador++;
        }
    }
}

void exibirTabuleiro(char** tabuleiro) {
    printf("Tabuleiro 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para mostrar o histórico de jogadas
void mostrarHistorico(Jogada* historico, int numJogadas) {
    printf("\nHistórico de jogadas:\n");
    for (int i = 0; i < numJogadas; i++) {
        printf("Jogada %d: Jogador %c na posição (%d,%d)\n", 
               i + 1, 
               historico[i].jogador, 
               historico[i].linha + 1, 
               historico[i].coluna + 1);
    }
}

int verificarVitoria(char** tabuleiro, char jogador) {
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

void jogar(char** tabuleiro, Jogada* historico, int* numJogadas) {
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
                // Registrar a jogada no histórico
                historico[*numJogadas].linha = linha;
                historico[*numJogadas].coluna = coluna;
                historico[*numJogadas].jogador = 'X';
                (*numJogadas)++;
                break;
            } else {
                printf("Posição já ocupada! Tente novamente.\n");
            }
        } else {
            printf("Posição inválida! Tente novamente.\n");
        }
    }
}

void jogarComputador(char** tabuleiro, Jogada* historico, int* numJogadas) {
    int posicao;
    int linha, coluna;
    while (1) {
        posicao = rand() % 9;
        linha = posicao / 3;
        coluna = posicao % 3;
        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O';
            // Registrar a jogada no histórico
            historico[*numJogadas].linha = linha;
            historico[*numJogadas].coluna = coluna;
            historico[*numJogadas].jogador = 'O';
            (*numJogadas)++;
            break;
        }
    }
}

int main() {
    char** tabuleiro = alocarTabuleiro();
    Jogada* historico = alocarHistorico(9); // Máximo de 9 jogadas possíveis
    int numJogadas = 0;
    
    gerarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro);
    
    srand(time(NULL));
    
    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            jogar(tabuleiro, historico, &numJogadas);
        } else {
            jogarComputador(tabuleiro, historico, &numJogadas);
        }
        exibirTabuleiro(tabuleiro);
        mostrarHistorico(historico, numJogadas);
        
        if (verificarVitoria(tabuleiro, 'X')) {
            printf("Jogador X venceu!\n");
            liberarTabuleiro(tabuleiro);
            free(historico);
            return 0;
        } else if (verificarVitoria(tabuleiro, 'O')) {
            printf("Computador O venceu!\n");
            liberarTabuleiro(tabuleiro);
            free(historico);
            return 0;
        }
    }
    
    printf("Deu velha!\n");
    liberarTabuleiro(tabuleiro);
    free(historico);
    return 0;
}
