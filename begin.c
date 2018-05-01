#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "ai.h"

void boardTypeCheck(){  // confere o tipo de tabuleiro a ser jogado
    char board[255];
    printf("Bem-vindo ao jogo Quarto!\n\nEscolha o seu tabuleiro:\n[h] Preenche o tabuleiro com numeros hexadecimais -- [b] Preenche o tabuleiro com numeros binarios\n\n" );
    scanf("%s", board);
    for(;;){
        if ((board[0] == 72 || board[0] == 104) && strlen(board)==1){ // se a entrada for 'H' ou 'h'
            boardType = HEXADECIMAL;
            break;
        } else if ((board[0] == 66 || board[0] == 98) && strlen(board)==1){ // se a entrada for 'B' ou 'b'
            boardType = BINARY;
            break;
        } else {
            printf("Por favor tente de novo usando a letra \"h\" ou a letra \"b\"\n");
            scanf("%s", board);
        }
    }
}

int gameTypeCheck(){  // verifica se o jogador quer ir contra a IA (indo primeiro ou segundo) ou se ele quer jogar contra outra pessoa (multiplayer)
    char type[255];
    printf("\nEscolha o seu modo de jogo:\n[1] Multiplayer -- [2] vs. IA (IA joga primeiro) -- [3] vs. IA (Voce joga primero)\n\n" );
    scanf("%s", type);
    for(;;){
        if ((type[0] == 49) && strlen(type)==1){
            return 1;
            break;
        } else if ((type[0] == 50) && strlen(type)==1){
            return 2;
            break;
        } else if ((type[0] == 51) && strlen(type)==1){
            return 3;
            break;
        } else {
            printf("Por favor tente de novo usando o numero \"1\", \"2\" ou \"3\".\n");
            scanf("%s", type);
        }
    }
}

void initializeSlots(){  // inicializa o vetor das respostas
    for (int i = 0; i < 16; i++){
        slots[i] = EMPTY;
        binarySlots[i][0] = EMPTY;
    }
}

void binaryArray (int position, int number) { // pega os valores em hexadecimal e os converte para um vetor de numeros binarios
    for (int i = 0; i < 4; i++){
        binarySlots[position][3-i] = (number % 2);
        number = number / 2;
    }
}


void printHexBoard(int position, int number){ // mostra o tabuleiro (hexadecimal) e preenche o array de respostas após receber o número e sua posição
    slots[position] = number;
    int counter = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (slots[counter] == EMPTY) {
                printf("| |");
            }  else {
                printf("|%X|",slots[counter]);
            }

                counter++;
        }
        printf("\n");
    }
    printf("\n");
}

void printBinaryBoard(int position, int number){ // mostra o tabuleiro (binário) e preenche o array de respostas após receber o número e sua posição
    slots[position] = number;
    int counter = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (slots[counter] == EMPTY) {
                printf("|    |");
            }  else {
                printf("|");
                for (int i = 0; i < 4; i++){
                    printf("%d",binarySlots[counter][i]);
                }
                printf("|");
            }

                counter++;
        }
        printf("\n");
    }
    printf("\n");
}

int numberChecker(){  // funçao para conferir se o numero é válido e, se não for, pedir outro numero
    char readUser[255];
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%s", readUser);
        required = strtoul(readUser,0,16);
        for (int i = 0; i < 16; i++){
            if (required == slots[i]) {
                used = 1;
            }
        }
        if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 0 && strlen(readUser)==1){ // checks if input is a hexadecimal number
            break;
        } else if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 1 && strlen(readUser)==1){
            printf("Esse numero ja foi usado. Por favor escolha outro: ");
        } else {
            printf("Tente de novo usando um numero entre 0 e F (hex): ");
        }
    }
    return required;
}

int positionChecker(){  // funçao para conferir se a posição é válida e, se não for, pedir outra posição
    char readUser[255];
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%s", readUser);
        required = strtoul(readUser,0,16);
        if (slots[required] != EMPTY) {
            used = 1;
        }
        if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 0 && strlen(readUser)==1){ // checks if input is a hexadecimal number
            break;
        } else if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 1 && strlen(readUser)==1){
            printf("Essa posicao ja foi usada. Por favor escolha outra: ");
        } else {
            printf("Tente de novo usando um numero entre 0 e F (hex): ");
        }
    }
    return required;
}

int winCheck(int arr[16][4]) { // função para conferir se há a vitória
    int won = 0;
    int slot, bit, line, column;
    for (line = 0; line < 16; line = line+4){  // confere se há vitória nas linhas
        for (bit = 0; bit < 4; bit++) {
            for (slot = line; slot < line+4; slot++){
                if (arr[slot][bit] == arr[slot+1][bit] && arr[slot][0] != -1 && slot == line){
                    won++;
                    slot++;
                }
                if (arr[slot][bit] == arr[slot-1][bit] && arr[slot][0] != -1){
                    won++;
                } else {
                    won = 0;
                }
            }
            if (won == 4){
                return won;
            } else {
                won = 0;
            }
        }
    }
    for (column = 0; column < 4; column++){  // confere se há vitória nas colunas
        for (bit = 0; bit < 4; bit++) {
            for (slot = column; slot < column+13; slot = slot+4){
                if (arr[slot][bit] == arr[slot+4][bit] && arr[slot][0] != -1 && slot == column){
                    won++;
                    slot=slot+4;
                }
                if (arr[slot][bit] == arr[slot-4][bit] && arr[slot][0] != -1){
                    won++;
                } else {
                    won = 0;
                }
            }
            if (won == 4){
                return won;
            } else {
                won = 0;
            }
        }
    }
    for (bit = 0; bit < 4; bit++) {   // confere se há vitória na primeira diagonal (0, 5, A e F)
        for (slot = 0; slot < 16; slot = slot+5){
            if (arr[slot][bit] == arr[slot+5][bit] && arr[slot][0] != -1 && slot == 0){
                won++;
                slot=slot+5;
            }
            if (arr[slot][bit] == arr[slot-5][bit] && arr[slot][0] != -1){
                    won++;
            } else {
                won = 0;
            }
        }
        if (won == 4){
            return won;
        } else {
            won = 0;
        }
    }
    for (bit = 0; bit < 4; bit++) {   // confere se há vitória na primeira diagonal (3, 6, 9 e C)
        for (slot = 3; slot < 13; slot = slot+3){
            if (arr[slot][bit] == arr[slot+3][bit] && arr[slot][0] != -1 && slot == 3){
                    won++;
                    slot=slot+3;
            }
            if (arr[slot][bit] == arr[slot-3][bit] && arr[slot][0] != -1){
                won++;
            } else {
                won = 0;
            }
        }
        if (won == 4){
            return won;
        } else {
            won = 0;
        }
    }
    return won;
}

int multiplayer() { // função principal para jogar o jogo sem a IA
    int pos, ans, pNumber;
    printf("\n- Jogador 1:\n");
    printf("Escolha um numero: ");
    ans = numberChecker();
    printf("\n");
    for (int i = 0; i < 15; i++){
        if (i % 2 != 0) {  // dá um número para o jogador (Jogador 1 / Jogador 2)
            pNumber = 1;
            printf("- Jogador %d:", pNumber);
        } else {
            pNumber = 2;
            printf("- Jogador %d:", pNumber);
        }
        printf("\nEscolha uma posicao para numero %X: ", ans);
        pos = positionChecker();
        binaryArray(pos,ans);
        printf("\n");
	    if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }
        
        if (winCheck(binarySlots)==4){
            printf(" ------------------------ Jogador %d won! ------------------------\n", pNumber);
            system("pause");
            return 0;
        }

        printf("Escolha um numero: ");
        ans = numberChecker();
        printf("\n");

    }
    printf("- Jogador 2:\n");
    printf("\nEscolha uma posicao para numero %X: ", ans);
    pos = positionChecker();
    binaryArray(pos,ans);
    printf("\n");
    if (boardType == HEXADECIMAL) {
        printHexBoard(pos, ans);
    } else if (boardType == BINARY) {
        printBinaryBoard(pos, ans);
    }

    if (winCheck(binarySlots)==4){
        printf(" ------------------------ Jogador %d won! ------------------------\n", pNumber);
        system("pause");
        return 0;
    } else {
    	printf(" ------------------------ Empate! ------------------------\n");
    	system("pause");
        return 0;
    }
}

