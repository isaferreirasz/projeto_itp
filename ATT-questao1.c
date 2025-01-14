#include <stdio.h>
#include <stdlib.h>

int **tabuleiro, i, j;
int gerarTabuleiro() {

  int contador = 1;
  tabuleiro = malloc(3 * sizeof(int*));

  for (i = 0; i < 3; i++) {
    tabuleiro[i] = malloc(3 * sizeof(int));
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tabuleiro[i][j] = 0 + contador;
      contador++;
    }
  }
  return 0;
}

int exibirTabuleiro() {
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      printf("%d ", tabuleiro[i][j]);
    }
    printf("\n");
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
  liberarTabuleiro();
  return 0;
}
