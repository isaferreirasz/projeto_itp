
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct { //o typedef é usado para definir um tipo de dados, logo Tabuleiro vai ser um tipo que tem tamanho e posicoes
    int tamanho; 
    int *posicoes;  // Ponteiro para um array de inteiros que representa as posições
} Tabuleiro;

//O asterisco (*) no nome da função Tabuleiro *criar_tabuleiro(int tamanho) indica que a função retorna um ponteiro para um tipo de dado específico, neste caso, um ponteiro para a estrutura Tabuleiro
Tabuleiro *criar_tabuleiro(int tamanho) { // Função do tipo Tabuleiro que recebe o tamanho como parâmetro
    Tabuleiro *tabuleiro = (Tabuleiro *)malloc(sizeof(Tabuleiro)); //No caso da expressão (Tabuleiro *), você está convertendo o resultado da função malloc, que é um ponteiro do tipo void *, para um ponteiro do tipo Tabuleiro *.
    tabuleiro->tamanho = tamanho; //passado pelo parâmetro
    tabuleiro->posicoes = (int *)malloc(tamanho * sizeof(int)); //alocar dinamicamte o tamanho vezes o tamanho de um inteiro
    for (int i = 0; i < tamanho; i++) {
        tabuleiro->posicoes[i] = -1; //para todas as posições alocadas (posicoes[i]), nenhuma tem rainha, por isso o -1
    }
    return tabuleiro; //retorna tabuleiro com todas as posições vazias
}

void liberar_tabuleiro(Tabuleiro *tabuleiro) { //libera memória alocada para o ponteiro tabuleiro do tipo Tabuleiro
    free(tabuleiro->posicoes); //libera posições
    free(tabuleiro); //libera tabuleiro
}

//Função do tipo booleano que recebe como parâmetro o ponteiro tabuleiro e as variáveis linha e coluna
bool e_seguro(Tabuleiro *tabuleiro, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        int coluna_atual = tabuleiro->posicoes[i];
        if (coluna_atual == coluna || // Se a coluna atual da rainha (coluna_atual) é igual à coluna onde você está tentando colocar a nova rainha, isso significa que as rainhas estão na mesma coluna, o que não é seguro.
            coluna_atual - i == coluna - linha || //i é o índice da linha da rainha já colocada. Essa expressão ( coluna_atual - i)calcula a diferença entre a coluna da rainha já colocada e sua linha. Isso representa a "inclinação" da diagonal principal. Esta expressão (coluna - linha)calcula a diferença entre a coluna onde você está tentando colocar a nova rainha e a linha atual. Se essas duas diferenças forem iguais, isso significa que a nova rainha está na mesma diagonal principal que a rainha já colocada.

            coluna_atual + i == coluna + linha) { //coluna_atual + i: Aqui, i é novamente o índice da linha da rainha já colocada. Essa expressão calcula a soma da coluna da rainha já colocada e sua linha.
           // coluna + linha: Esta expressão calcula a soma da coluna onde você está tentando colocar a nova rainha e a linha atual. Se essas duas somas forem iguais, isso significa que a nova rainha está na mesma diagonal secundária que a rainha já colocada.
            return false;
        }
    }
    return true;
}
//Função do tipo booleano que recebe como parâmetro o ponteiro tabuleiro e a variável linha
bool resolver(Tabuleiro *tabuleiro, int linha) {
    if (linha == tabuleiro->tamanho) { // verifica se todas as rainhas foram colocadas (ou seja, se você chegou à linha que excede o tamanho do tabuleiro). Se sim, retorna true, indicando que uma solução foi encontrada.
        return true;
    }
    for (int coluna = 0; coluna < tabuleiro->tamanho; coluna++) { //para a linha passada como parâmetro, percorre todas as colunas do tabuleiro
        if (e_seguro(tabuleiro, linha, coluna)) { //para cada coordenada, chama a funçãõ e_seguro para verificar se é seguro colocar uma rainha nessa posição. 
            tabuleiro->posicoes[linha] = coluna; //se for seguro, na posicao referente a linha, atribui o valor da coluna na posição, assim não será mais uma posição com -1 (vazia)
            if (resolver(tabuleiro, linha + 1)) { //verifica a próxima linha, chamando a função resolver recursivamente. 
                return true;
            }
            tabuleiro->posicoes[linha] = -1; //se não for seguro, retorna -1 para a posição da rainha (não coloca nenhuma rainha na posição)
        }
    }
    return false;
}

void exibir_tabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->tamanho; i++) {
        for (int j = 0; j < tabuleiro->tamanho; j++) {
            if (tabuleiro->posicoes[i] == j) { //Onde na posição, tiver o valor da coluna, coloca um Q
                printf("Q ");
            } else { //Onde tiver -1, coloca um .
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    int tamanho;

    printf("Digite o tamanho do tabuleiro (N): ");
    scanf("%d", &tamanho);

    if (tamanho < 1) {
        printf("Tamanho inválido!\n");
        return 1;
    }

    Tabuleiro *tabuleiro = criar_tabuleiro(tamanho);

    if (resolver(tabuleiro, 0)) {
        printf("Solução encontrada:\n");
        exibir_tabuleiro(tabuleiro);
    } else {
        printf("Nenhuma solução encontrada para o tabuleiro de tamanho %d.\n", tamanho);
    }

    liberar_tabuleiro(tabuleiro);
    return 0;
}
