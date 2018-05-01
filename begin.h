#ifndef begin_H_
#define begin_H_

#define HEXADECIMAL 1
#define BINARY 2
#define EMPTY -1
#define VICTORY 4

int slots[16];
int binarySlots[16][4];
int boardType;

void boardTypeCheck ();                            // confere o tipo de tabuleiro a ser jogado
void initializeSlots();                            // inicializa o vetor das respostas
void binaryArray (int position, int number);       // pega os valores em hexadecimal e os converte para um vetor de numeros binarios
void printHexBoard(int position, int number);      // mostra o tabuleiro (hexadecimal) e preenche o array de respostas após receber o número e sua posição
void printBinaryBoard(int position, int number);   // mostra o tabuleiro (binário) e preenche o array de respostas após receber o número e sua posição
int gameTypeCheck();                               // verifica se o jogador quer ir contra a IA (indo primeiro ou segundo) ou se ele quer jogar contra outra pessoa (multiplayer)
int multiplayer();                                 // função principal para jogar o jogo sem a IA
int numberChecker();                               // funçao para conferir se o numero é válido e, se não for, pedir outro numero
int positionChecker();                             // funçao para conferir se a posição é válida e, se não for, pedir outra posição
int winCheck();                                    // função para conferir se há a vitória


#endif