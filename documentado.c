
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char **tabuleiro;  // Declara um ponteiro para um ponteiro de char, que será usado para representar o tabuleiro
int i, j;             // Declara variáveis globais para iteração


// Função para gerar o tabuleiro inicial
void gerarTabuleiro() {
    tabuleiro = malloc(3 * sizeof(char*)); // Aloca memória para 3 linhas
    for (i = 0; i < 3; i++) {
        tabuleiro[i] = malloc(3 * sizeof(char)); // Aloca memória para 3 colunas em cada linha
    }

    int contador = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tabuleiro[i][j] = '0' + contador; // Preenche o tabuleiro com números de 1 a 9
            contador++;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]); // Exibe cada posição do tabuleiro
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
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
    return 0; // Retorna 0 se não houve vitória
}

// Função para verificar se o jogador pode vencer na próxima jogada
int podeVencer(char **tabuleiro, char jogador) {
    for (int posicao = 0; posicao < 9; posicao++) {
        int linha = posicao / 3;
        int coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = jogador; // Tenta a jogada
            if (verificarVitoria(tabuleiro, jogador)) {
                return posicao; // Retorna a posição onde pode vencer
            }
            tabuleiro[linha][coluna] = '0' + posicao + 1; // Desfaz a jogada
        }
    }
    return -1; // Retorna -1 se não pode vencer
}

// Função para o jogador X fazer sua jogada
void jogarX(char **tabuleiro) {
    int posicao;
    while (1) {
        printf("Escolha uma posição para colocar o X (1-9): ");
        if (scanf("%d", &posicao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer se a entrada não for um número
            printf("Entrada inválida! Tente novamente.\n");
            continue; // Retorna ao início do loop
        }

        if (posicao < 1 || posicao > 9) {
            printf("Posição inválida! Tente novamente.\n");
            continue; // Retorna ao início do loop
        }

        posicao--; // Ajusta para índice 0
        int linha = posicao / 3;
        int coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'X'; 
            return; // Retorna indicando que a jogada foi feita
        } else {
            printf("Posição já ocupada! Tente novamente.\n");
        }
    }
}

// Função para o jogador O fazer sua jogada
void jogarO(char **tabuleiro) {
 int posicao;

    posicao = podeVencer(tabuleiro, 'O'); // Verifica se O pode vencer
    if (posicao != -1) {
        tabuleiro[posicao / 3][posicao % 3] = 'O'; // Marca a posição para O
        printf("O jogador O marcou a posição %d\n", posicao + 1); 
        return;
    }

    posicao = podeVencer(tabuleiro, 'X'); // Verifica se precisa bloquear X
    if (posicao != -1) {
        tabuleiro[posicao / 3][posicao % 3] = 'O'; // Marca a posição para O
        printf("O jogador O bloqueou a posição %d\n", posicao + 1); 
        return;
    }

    while (1) {
        posicao = rand() % 9; // Escolhe uma posição aleatória
        int linha = posicao / 3;
        int coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O'; // Marca a posição para O
            printf("O jogador O marcou a posição %d\n", posicao + 1); 
            break; // Sai do loop
        }
    }
}

// Função para verificar se houve empate
int verificarEmpate(char **tabuleiro) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                return 0; // Retorna 0 se ainda há posições disponíveis
            }
        }
    }
    return 1; // Retorna 1 se não há mais posições disponíveis
}

// Função para liberar a memória do tabuleiro
void liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); // Libera cada linha
    }
    free(tabuleiro); // Libera o ponteiro do tabuleiro
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    gerarTabuleiro(); // Gera o tabuleiro inicial
    printf("Boas vindas ao Jogo da Velha! Você é o jogador X!\n");
    exibirTabuleiro(); // Exibe o tabuleiro

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            jogarX(tabuleiro); // Jogada do jogador X
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'X')) {
                printf("Jogador X venceu!\n");
                liberarTabuleiro(); // Libera a memória
                return 0; // Encerra o programa
            }
        } else {
            jogarO(tabuleiro); // Jogada do jogador O
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'O')) {
                printf("Jogador O venceu!\n");
                liberarTabuleiro(); // Libera a memória
                return 0; // Encerra o programa
            }
        }
        if (verificarEmpate(tabuleiro)) {
            exibirTabuleiro();
            printf("Deu velha!\n");
            liberarTabuleiro(); // Libera a memória
            return 0; // Encerra o programa
        }
    }

    liberarTabuleiro(); // Libera a memória
    return 0; // Encerra o programa
}
