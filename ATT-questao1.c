#include <stdio.h>
#include <stdlib.h>

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

void jogar(char **tabuleiro) {
    int posicao;
    while (1) {
        printf("Escolha uma posição para colocar o X: ");
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

void jogarComputador(char **tabuleiro){
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
  for (int i = 0; i < 9; i++) {
          if (i % 2 == 0) {
              jogar(tabuleiro);
          } else {
              jogarComputador(tabuleiro);
              exibirTabuleiro();
          }
         

          if (verificarVitoria(tabuleiro, 'X')) {
              exibirTabuleiro();  
              printf("Jogador X venceu!\n");
              return 0;
          } else if (verificarVitoria(tabuleiro, 'O')) {
              exibirTabuleiro();
              printf("Jogador 0 venceu!\n");
              
              return 0;
          }
      }

      printf("Deu velha!\n");
      liberarTabuleiro();
  return 0;
  
  }
