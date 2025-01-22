#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **tabuleiro; //declara um ponteiro para ponteiro de char, que será utilizado para representar o tabuleiro. Isso significa que tabuleiro é um ponteiro que aponta para outro ponteiro que, por sua vez, aponta para um tipo char
int i, j; // variáveis globais para iteração

//Função void pois não retorna valor
void gerarTabuleiro() {
    tabuleiro = malloc(3 * sizeof(char*)); //O malloc está alocando espaço para 3 ponteiros de char, que representarão as 3 linhas do tabuleiro. Cada elemento de tabuleiro será um ponteiro que apontará para uma linha do tabuleiro.
    for (i = 0; i < 3; i++) {
        tabuleiro[i] = malloc(3 * sizeof(char)); //para cada linha (tabuleiro[i]), o malloc está alocando espaço para 3 elementos de char, ou seja, três posições por linha.
    }
    int contador = 1; //será utilizado para preencher o tabuleiro com números de 1 a 9.
    for (i = 0; i < 3; i++) { // O loop externo itera sobre as linhas (i), e o loop interno itera sobre as colunas (j).
        for (j = 0; j < 3; j++) {
            tabuleiro[i][j] = '0' + contador;  //A expressão '0' + contador converte o número inteiro contador em seu equivalente de caractere. Em C, os caracteres são representados por seus códigos numéricos na tabela ASCII. Quando você escreve '0', o compilador interpreta isso como o valor numérico 48 (o código ASCII para o caractere '0').
            contador++; // incrementa contador para que o próximo número seja usado na próxima iteração.
        }
    }
}
//Função void pois não retorna valor
void exibirTabuleiro() {
    for (i = 0; i < 3; i++) { //Este loop itera sobre as linhas do tabuleiro. A variável i começa em 0 e vai até 2 (totalizando 3 iterações, uma para cada linha do tabuleiro).
        for (j = 0; j < 3; j++) { //Este loop aninhado itera sobre as colunas do tabuleiro. A variável j também começa em 0 e vai até 2 (totalizando 3 iterações, uma para cada coluna da linha atual).
            printf("%c ", tabuleiro[i][j]); //Dentro do loop interno, esta linha imprime o caractere que está na posição [i][j] do tabuleiro. O %c é um especificador de formato que indica que você está imprimindo um caractere. 
        }
        printf("\n"); 
    }
}

//int indica que a função retornará um valor inteiro. Neste caso, a função retorna 1 se o jogador ganhou e 0 se não ganhou.
int verificarVitoria(char **tabuleiro, char jogador) { //recebe um ponteiro para ponteiro de char, que representa o tabuleiro 3x3. recebe também um caractere que representa o jogador que está sendo verificado (0 ou X)
    for (int i = 0; i < 3; i++) { //O loop for itera sobre os índices de 0 a 2, que representam as linhas e colunas do tabuleiro.
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) || //A primeira parte da condição verifica se todas as três células da linha i contêm o caractere do jogador. Se todas as três células da linha forem iguais ao jogador, isso significa que o jogador ganhou naquela linha.
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) { // A segunda parte da condição verifica se todas as três células da coluna i contêm o caractere do jogador. Se todas as três células da coluna forem iguais ao jogador, isso significa que o jogador ganhou naquela coluna.
            return 1; //Se qualquer uma das condições for verdadeira (ou seja, o jogador ganhou em uma linha ou coluna), a função retorna 1. 
        }
    }

    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) || //A primeira parte da condição verifica se as células da diagonal principal contêm o caractere do jogador.
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) { // A segunda parte da condição verifica se as células da diagonal secundária contêm o caractere do jogador.
        return 1; //Se qualquer uma das condições for verdadeira (ou seja, o jogador ganhou em uma das diagonais), a função retorna 1.
    }
    return 0; //Se jogador não ganhou em nenhuma das condições acima, a função retorna 0.
}

//int indica que a função retornará um valor inteiro. O valor retornado pode ser a posição onde o jogador pode vencer ou -1 se não houver uma jogada que leve à vitória.
int podeVencer(char **tabuleiro, char jogador) { //recebe o tabuleiro e um caractere que indique o jogador que está sendo verificado.
    for (int posicao = 0; posicao < 9; posicao++) { //O loop for itera sobre as posições de 0 a 8, que representam as 9 células do tabuleiro (3x3).
        int linha = posicao / 3; //A linha é calculada dividindo a posição por 3. Para posicao de 0 a 2, a linha será 0; para 3 a 5, a linha será 1; e para 6 a 8, a linha será 2.
        int coluna = posicao % 3; //A coluna é calculada usando o operador módulo. Isso dá o resto da divisão da posição por 3, resultando em 0, 1 ou 2.

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') { //Esta condição verifica se a célula atual (tabuleiro[linha][coluna]) está vazia (ou seja, não contém 'X' ou 'O'). Se a célula estiver vazia, o jogador pode tentar jogar nessa posição.
            tabuleiro[linha][coluna] = jogador; //Aqui, a função simula a jogada do jogador, colocando o caractere do jogador na posição atual do tabuleiro.
            if (verificarVitoria(tabuleiro, jogador)) {
                return posicao; //A função chama verificarVitoria para verificar se a jogada resultou em uma vitória. Se a função retornar true (ou seja, o jogador ganhou), a função podeVencer retorna a posição onde a jogada foi feita (posicao).

            }
            tabuleiro[linha][coluna] = '0' + posicao + 1; //Se a jogada não resultou em vitória, a função reverte a jogada, colocando o número correspondente à posição de volta na célula. Isso é feito para manter o tabuleiro em seu estado original para a próxima iteração do loop. '0' representa 48, posicao é um número inteiro que varia de 0 a 8 e o +1 serve para ficar o número original que estava na posição(1-9).
        }
    }
    return -1; //Se o loop terminar e nenhuma jogada levar à vitória, a função retorna -1. Este valor indica que não há uma jogada que permita ao jogador vencer na próxima jogada.
}

void jogarX(char **tabuleiro) {
    int posicao;
    while (1) { //Este é um loop infinito que continuará até que o jogador coloque um 'X' em uma posição válida. O loop só será interrompido quando uma jogada válida for feita.
        printf("Escolha uma posição para colocar o X (1-9): "); //A função pede ao jogador para escolher uma posição entre 1 e 9.
        if (scanf("%d", &posicao) != 1) { // tenta ler um número inteiro da entrada padrão e armazená-lo na variável posicao. Se scanf não conseguir ler um número (ou seja, se a entrada não for um número inteiro), ele retorna um valor diferente de 1.
            while (getchar() != '\n'); //O loop é usado para limpar o buffer de entrada, descartando qualquer caractere até encontrar uma nova linha.  Isso significa que ele vai ler e descartar todos os caracteres que foram digitados pelo usuário até que o usuário pressione "Enter".
            printf("Entrada inválida! Tente novamente.\n"); //informa a entrada inválida
            continue; //Quando o continue é encontrado, o controle do programa volta ao início do loop while (1), pulando qualquer código que venha após o continue na iteração atual.
        }

        if (posicao < 1 || posicao > 9) { //Esta condição verifica se a posição escolhida está fora do intervalo permitido (1 a 9). Se a posição não estiver dentro desse intervalo, a função informa ao jogador e continua para a próxima iteração do loop.
            printf("Posição inválida! Tente novamente.\n");
            continue; 
        }

        posicao--; //é usado para converter a posição de 1-9 para 0-8, que é o índice usado nas arrays em C.
        int linha = posicao / 3;
        int coluna = posicao % 3; //O operador módulo (%) é usado para obter o resto da divisão da posição por 3, o que resulta no índice da coluna correta.

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') { // A condição verifica se a posição escolhida está vazia (ou seja, não contém 'X' ou 'O').
            tabuleiro[linha][coluna] = 'X'; 
            return; //Se a posição estiver vazia, a função coloca um 'X' na posição correspondente do tabuleiro e usa return para sair da função, encerrando a jogada.
        } else {
            printf("Posição já ocupada! Tente novamente.\n"); //Se a posição já estiver ocupada, a função informa ao jogador e continua para a próxima iteração do loop, permitindo que o jogador escolha outra posição.
        }
    }
}
//A função jogarO implementa a lógica para o jogador 'O' fazer uma jogada, priorizando a vitória ou o bloqueio do jogador 'X', e, se não houver jogadas estratégicas, escolhendo aleatoriamente uma posição vazia.
void jogarO(char **tabuleiro) {
 int posicao;
    posicao = podeVencer(tabuleiro, 'O'); //A função podeVencer é chamada para verificar se o jogador 'O' pode vencer na próxima jogada.
    if (posicao != -1) { // Se podeVencer retornar uma posição válida (ou seja, diferente de -1), isso significa que 'O' pode vencer.
        tabuleiro[posicao / 3][posicao % 3] = 'O'; 
        printf("O jogador O marcou a posição %d\n", posicao + 1); 
        return; //Se 'O' pode vencer, a posição correspondente no tabuleiro é marcada com 'O', e uma mensagem é impressa informando que 'O' marcou essa posição. A função então usa return para sair, pois a jogada foi feita.
    }
    
    posicao = podeVencer(tabuleiro, 'X'); // A função podeVencer é chamada novamente, mas desta vez para verificar se o jogador 'X' pode vencer na próxima jogada. Se 'X' pode vencer, a posição correspondente é marcada com 'O' para bloquear a vitória de 'X'.
    if (posicao != -1) {
        tabuleiro[posicao / 3][posicao % 3] = 'O'; 
        printf("O jogador O bloqueou a posição %d\n", posicao + 1); 
        return;
    }

    while (1) { //Um loop while (1) é iniciado, que continuará até que uma jogada válida seja feita.
        posicao = rand() % 9; // gera um número aleatório entre 0 e 8, representando uma posição no tabuleiro.
        int linha = posicao / 3;
        int coluna = posicao % 3;

        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') { //verifica se a posição escolhida está vazia. Se a posição estiver vazia, a jogada é válida.
            tabuleiro[linha][coluna] = 'O'; 
            printf("O jogador O marcou a posição %d\n", posicao + 1); 
            break; // Se a posição estiver vazia, ela é marcada com 'O', e uma mensagem é impressa informando que 'O' marcou essa posição. O break é usado para sair do loop, pois a jogada foi feita
        }
    }
}
//int indica que a função retornará um valor inteiro. Neste caso, a função retornará 1 se o jogo terminar em empate e 0 se ainda houver posições disponíveis.
int verificarEmpate(char **tabuleiro) { //A função verifica se todas as posições do tabuleiro estão ocupadas por 'X' ou 'O'. Se todas as posições estiverem ocupadas e não houver mais espaços vazios, isso indica que o jogo terminou em empate.
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') { //A condição verifica se a célula atual (tabuleiro[i][j]) não contém 'X' e não contém 'O'. Se encontrar uma célula que não está ocupada (ou seja, ainda contém um número ou está vazia), isso significa que o jogo ainda não terminou e há posições disponíveis para jogar.
                return 0; //Se a condição for verdadeira (ou seja, há pelo menos uma posição vazia), a função retorna 0, indicando que o jogo não terminou em empate.
            }
        }
    }
    return 1; //Se o loop terminar e não encontrar nenhuma posição vazia (ou seja, todas as células estão ocupadas por 'X' ou 'O'), a função retorna 1, indicando que o jogo terminou em empate.
}
//responsável por liberar a memória que foi alocada dinamicamente para o tabuleiro
void liberarTabuleiro() {
    for (i = 0; i < 3; i++) {
        free(tabuleiro[i]); //A função free(tabuleiro[i]); é chamada para liberar a memória alocada para cada linha do tabuleiro. Cada tabuleiro[i] é um ponteiro que aponta para um array de caracteres (uma linha do tabuleiro). Ao chamar free, você está liberando a memória que foi alocada para essas linhas.
    }
    free(tabuleiro); //Após liberar a memória de cada linha, a função free(tabuleiro); é chamada para liberar a memória alocada para o ponteiro que contém os ponteiros para as linhas. Isso libera a memória que foi alocada para o array de ponteiros que representa o tabuleiro em si.
}

int main() {
    srand(time(NULL)); //inicializa o gerador de números aleatórios com a hora atual. Isso garante que os números aleatórios gerados pela função rand() sejam diferentes a cada execução do programa.
    gerarTabuleiro(); //A função gerarTabuleiro() é chamada para alocar memória e inicializar o tabuleiro 3x3. O tabuleiro será preenchido com números de 1 a 9, representando as posições disponíveis.
    printf("Boas vindas ao Jogo da Velha! Você é o jogador X!\n");
    exibirTabuleiro(); //A função exibirTabuleiro() é chamada para mostrar o estado inicial do tabuleiro.
    for (int i = 0; i < 9; i++) { //O loop for permite até 9 jogadas (o número total de células em um tabuleiro 3x3). O índice i é usado para alternar entre os jogadores.
        if (i % 2 == 0) { //Se i for par (0, 2, 4, 6, 8), o jogador 'X' faz sua jogada chamando jogarX(tabuleiro). Após a jogada, o tabuleiro é exibido e a função verificarVitoria(tabuleiro, 'X') é chamada para verificar se 'X' venceu. Se 'X' vencer, uma mensagem é impressa, a memória do tabuleiro é liberada e o programa termina com return 0.
            jogarX(tabuleiro); 
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'X')) {
                printf("Jogador X venceu!\n");
                liberarTabuleiro(); 
                return 0; 
            }
        } else { //Se i for ímpar (1, 3, 5, 7), o jogador 'O' faz sua jogada chamando jogarO(tabuleiro). O tabuleiro é exibido, a vitória é verificada, e se 'O' vencer, uma mensagem é impressa, a memória é liberada, e o programa termina.
            jogarO(tabuleiro); 
            exibirTabuleiro(); 
            if (verificarVitoria(tabuleiro, 'O')) {
                printf("Jogador O venceu!\n");
                liberarTabuleiro(); 
                return 0; 
            }
        }
        //Após cada jogada, a função verificarEmpate(tabuleiro) é chamada para verificar se o jogo terminou em empate. Se todas as posições estiverem ocupadas e não houver vencedor, o tabuleiro é exibido, uma mensagem de empate é impressa, a memória é liberada, e o programa termina.
        if (verificarEmpate(tabuleiro)) {
            exibirTabuleiro();
            printf("Deu velha!\n");
            liberarTabuleiro(); 
            return 0; 
        }
    }

    liberarTabuleiro(); 
    return 0; 
}
