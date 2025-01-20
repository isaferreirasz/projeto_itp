#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>       
#include <ctype.h>      
#include <string.h>    

char **tabuleiro;      // Declara um ponteiro para um ponteiro de char, que será usado para representar o tabuleiro
int i, j;             // Declara variáveis globais para iteração

// Função para gerar o tabuleiro inicial
void gerarTabuleiro() {
    tabuleiro = malloc(3 * sizeof(char*)); // Aloca memória para 3 linhas do tabuleiro
    for (i = 0; i < 3; i++) {
        tabuleiro[i] = malloc(3 * sizeof(char)); // Aloca memória para 3 colunas em cada linha
    }

    int contador = 1; // Contador para preencher o tabuleiro
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
            printf("%c ", tabuleiro[i][j]); // Imprime cada elemento do tabuleiro
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

// Função para validar a entrada do usuário
int entradaValida(char *entrada) {
    // Verifica se a entrada tem comprimento 1 e é um dígito
    if (strlen(entrada) == 1 && isdigit(entrada[0])) {
        int posicao = entrada[0] - '0'; // Converte o caractere para um número
        return (posicao >= 1 && posicao <= 9); // Retorna 1 se a posição estiver entre 1 e 9
    }
    return 0; // Retorna 0 se a entrada não for válida
}

// Função para o jogador X fazer sua jogada
void jogarX(char **tabuleiro) {
    char entrada[10]; // Array para armazenar a entrada do usuário

    while (1) {
        printf("Escolha uma posição para colocar o X (1-9): ");
        fgets(entrada, sizeof(entrada), stdin); // Lê a entrada do usuário
        
        entrada[strcspn(entrada, "\n")] = 0; // Remove o caractere de nova linha

        if (entradaValida(entrada)) {
            int posicao = entrada[0] - '0' - 1; // Converte a entrada para índice (0-8)
            int linha = posicao / 3; // Calcula a linha correspondente
            int coluna = posicao % 3; // Calcula a coluna correspondente

            // Verifica se a posição está livre
            if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
                tabuleiro[linha][coluna] = 'X'; // Marca a posição com 'X'
                break; 
            } else {
                printf("Posição já ocupada! Tente novamente.\n"); 
            }
        } else {
            printf("Entrada inválida! Tente novamente.\n");
        }
    }
}

// Função para o jogador O fazer sua jogada
void jogarO(char **tabuleiro) {
    int posicao;
    int linha, coluna;
    while (1) {
        posicao = rand() % 9; // Gera uma posição aleatória entre 0 e 8
        linha = posicao / 3; // Calcula a linha correspondente
        coluna = posicao % 3; // Calcula a coluna correspondente

        // Verifica se a posição está livre
        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = 'O'; // Marca a posição com 'O'
            printf("O jogador O marcou a posição %d\n", posicao + 1); 
            break; 
        }
    }
}

// Função para verificar se um jogador venceu
int verificarVitoria(char **tabuleiro, char jogador) {
    // Verifica linhas e colunas
    for (int i = 0; i < 3; i++) {
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

// Função para verificar se houve empate
int verificarEmpate(char **tabuleiro) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Verifica se ainda há posições livres no tabuleiro
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                return 0; // Retorna 0 se ainda há jogadas possíveis
            }
        }
    }
    return 1; // Retorna 1 se não há mais jogadas possíveis, indicando empate
}

// Função para liberar a memória alocada para o tabuleiro
void liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); // Libera cada linha do tabuleiro
    }
    free(tabuleiro); // Libera o ponteiro do tabuleiro
}

// Função principal do jogo
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    gerarTabuleiro(); // Gera o tabuleiro inicial
    printf("Boas vindas ao Jogo da Velha! Você é o jogador X!\n");
    exibirTabuleiro(); // Exibe o tabuleiro inicial

    for (int i = 0; i < 9; i++) { // Loop para até 9 jogadas
        if (i % 2 == 0) { // Jogador X faz a jogada em posições pares
            jogarX(tabuleiro);
            exibirTabuleiro(); // Exibe o tabuleiro após a jogada de X
            if (verificarVitoria(tabuleiro, 'X')) { // Verifica se X venceu
                printf("Jogador X venceu!\n");
                liberarTabuleiro(); // Libera a memória antes de sair
                return 0; 
            }
        } else { // Jogador O faz a jogada em posições ímpares
            jogarO(tabuleiro);
            exibirTabuleiro(); // Exibe o tabuleiro após a jogada de O
            if (verificarVitoria(tabuleiro, 'O')) { // Verifica se O venceu
                printf("Jogador O venceu!\n");
                liberarTabuleiro(); // Libera a memória antes de sair
                return 0; 
            }
        }
        if (verificarEmpate(tabuleiro)) { // Verifica se houve empate
            printf("Empate!\n");
            liberarTabuleiro(); // Libera a memória antes de sair
            return 0; 
        }
    }
    liberarTabuleiro(); // Libera a memória no final do jogo
    return 0; 
}
