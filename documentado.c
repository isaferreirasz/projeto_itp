#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

// Declaração do tabuleiro como um ponteiro para ponteiros de caracteres
char **tabuleiro; 
int i, j;

// Função para gerar o tabuleiro inicial
void gerarTabuleiro() {
    // Aloca memória para 3 linhas do tabuleiro
    tabuleiro = malloc(3 * sizeof(char*)); 
    for (i = 0; i < 3; i++) {
        // Aloca memória para 3 colunas em cada linha
        tabuleiro[i] = malloc(3 * sizeof(char)); 
    }

    // Inicializa o tabuleiro com números de 1 a 9
    int contador = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tabuleiro[i][j] = '0' + contador; 
            contador++;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
}

// Função para a jogada do jogador X
void jogarX(char **tabuleiro) {
    int posicao;
    while (1) {
        printf("Escolha uma posição para colocar o X: ");
        scanf("%d", &posicao);
        posicao--; // Ajusta a posição para o índice do array (0-8)
        if (posicao >= 0 && posicao < 9) {
            int linha = posicao / 3; // Calcula a linha
            int coluna = posicao % 3; // Calcula a coluna

            // Verifica se a posição está livre
            if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
                tabuleiro[linha][coluna] = 'X'; // Marca a posição com X
                break;
            } else {
                printf("Posição já ocupada! Tente novamente.\n");
            }
        } else {
            printf("Posição inválida! Tente novamente.\n");
        }
    }
}

// Função para a jogada do computador O
void jogar0(char **tabuleiro) {
    int posicao;
    int linha, coluna;
    while (1) {
        posicao = rand() % 9; // Gera uma posição aleatória de 0 a 8
        linha = posicao / 3; // Calcula a linha
        coluna = posicao % 3; // Calcula a coluna

        // Verifica se a posição está livre
        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O'; // Marca a posição com O
            printf("O jogador O marcou a posição %d\n", posicao + 1); 
            break;
        }
    }
}

// Função para verificar se um jogador venceu
int verificarVitoria(char **tabuleiro, char jogador) {
    for (int i = 0; i < 3; i++) {
        // Verifica linhas e colunas
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1; // Retorna 1 se o jogador venceu
        }
    }
    // Verifica diagonais
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1; // Retorna 1 se o jogador venceu
    }
    return 0; // Retorna 0 se não houver vitória
}

// Função para verificar se o jogo terminou em empate
int verificarEmpate(char **tabuleiro) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Se encontrar uma posição vazia, não é empate
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                return 0; 
            }
        }
    }
    return 1; // Retorna 1 se todas as posições estão ocupadas, indicando empate
}

// Função para liberar a memória alocada para o tabuleiro
int liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); // Libera cada linha do tabuleiro
    }
    free(tabuleiro); // Libera o ponteiro do tabuleiro
    return 0;
}

// Função principal do jogo
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    gerarTabuleiro(); // Gera o tabuleiro inicial
    printf("Boas vindas ao Jogo da Velha! Você é o jogador X!\n");
    exibirTabuleiro(); // Exibe o tabuleiro inicial

    // Loop principal do jogo, que permite até 9 jogadas
    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            jogarX(tabuleiro); // Jogada do jogador X
            exibirTabuleiro(); // Exibe o tabuleiro após a jogada
            if (verificarVitoria(tabuleiro, 'X')) {
                printf("Jogador X venceu!\n"); // Mensagem de vitória
                liberarTabuleiro(); // Libera a memória
                return 0; // Encerra o programa
            }
        } else {
            jogar0(tabuleiro); // Jogada do jogador O
            exibirTabuleiro(); // Exibe o tabuleiro após a jogada
            if (verificarVitoria(tabuleiro, 'O')) {
                printf("Jogador O venceu!\n"); // Mensagem de vitória
                liberarTabuleiro(); // Libera a memória
                return 0; // Encerra o programa
            }
        }
        if (verificarEmpate(tabuleiro)) {
            exibirTabuleiro(); // Exibe o tabuleiro final
            printf("Deu velha!\n"); // Mensagem de empate
            liberarTabuleiro(); // Libera a memória
            return 0; // Encerra o programa
        }
    }

    liberarTabuleiro(); // Libera a memória no final do jogo
    return 0; // Encerra o programa
}
