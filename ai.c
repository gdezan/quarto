#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "ai.h"

int aiPlace (int ans){ // retorna a posição da peça escolhida pelo jogador
    int tmp, pos; 
    int testArr[16][4]; // vetor de teste para conferir quais posições podem vencer
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j]; // copia o vetor original para iniciar os testes
        }
    }
    for (int i = 0; i < 16; i++){ // testa todas as posições possíveis no vetor de teste para ver quais geram vitória
        tmp = ans;
        for (int j = 0; j < 4; j++){
            testArr[i][3-j] = tmp % 2;
            tmp = tmp/2;
        }
        if (winCheck(testArr)== VICTORY && slots[i] == EMPTY){
            return i; 
        } else {
            for (int j = 0; j < 4; j++){
                testArr[i][j] = binarySlots[i][j]; // retorna o vetor de teste para suas condições originais para que ele possa testar outras posições
            }
        }        
    }
    pos = rand() % 16;
    while (slots[pos] != EMPTY){
        pos = rand() % 16;  // se não há nenhuma posição vitoriosa, a função retornará uma posição aleatória que esteja vazia
    }
    return pos;
}

int aiChooseNumber() { // retorna um número para o jogador posicionar
    
    int tmp, possible, used; 
    int counter = 0;
    int testArr[16][4]; // mesmo principio do vetor de mesmo nome na função aiPlace()
    int possibleArr[16]; // vetor que guarda os números que não darão uma vitória para o jogador
    int num = -1;
    for (int i = 0; i < 16; i++){
        possibleArr[i] = EMPTY;
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j];
        }
    }
    for (int i = 0; i < 16; i++){
        possible = 1;
        used = 0;
        for (int j = 0; j < 16; j++){
            if (i == slots[j]) {
                used = 1; // confere se o número já foi usado (1 = sim, 0 = não)
            }
        }
        if (used == 0) {
            for (int j = 0; j < 16; j++){                   // passa por todos os números e posições
                if (slots[j] == EMPTY){                     
                    tmp = i;
                    for (int k = 0; k < 4; k++){
                        testArr[j][3-k] = tmp % 2;
                        tmp = tmp/2;
                    }
                    if (winCheck(testArr) == VICTORY){      // se um número for capaz de dar a vitória pro
                        possible = 0;                       // jogador, ele é descartado
                    }
                    for (int k = 0; k < 4; k++){
                        testArr[j][k] = binarySlots[j][k];
                    }

                }
            }
            if (possible == 1){
                possibleArr[counter] = i; // adiciona as respostas possíveis no vetor
                counter++;
            }
        }
    }
    int randIndex = rand() % (counter);
    if (possibleArr[0] == -1){                  // Se essa condição ocorrer, significa que não há 
        used = 1;                               // nenhum número que não dê vitória para o jogador.
        while (used == 1){                      // A função então irá retornar um número qualquer
            used = 0;                           // que não tenha sido usado
            num = rand() % 16;
            for (int j = 0; j < 16; j++){
                if (num == slots[j]) {
                    used = 1;
                }
            }
        }
    } else {
        num = possibleArr[randIndex]; // retorna um número aleatório que não dará a vitória pro jogador
    }
    return num;
}

int aiPlaySecond() { // função principal para jogar o jogo contra a IA (IA joga primeiro)
    int pos, ans;
    printf("\n- Jogador:\n");
    printf("Escolha um numero: ");
    ans = numberChecker();
    printf("\n");
    for (int i = 0; i < 7; i++){
        pos = aiPlace(ans);
        binaryArray(pos,ans);
        if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }        
        if (winCheck(binarySlots)==4){
            printf(" ------------------------ A IA venceu! ------------------------\n");
            system("pause");
            return 0;
        }
        ans = aiChooseNumber();
        printf("\n");
        printf("- Jogador:\n");
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
            printf(" ------------------------ Voce venceu! ------------------------\n");
            system("pause");
            return 0;
        }
        printf("Escolha um numero: ");
        ans = numberChecker();
        printf("\n");

    }
    pos = aiPlace(ans);
    binaryArray(pos,ans);
    if (boardType == HEXADECIMAL) {
        printHexBoard(pos, ans);
    } else if (boardType == BINARY) {
        printBinaryBoard(pos, ans);
    }        
    if (winCheck(binarySlots)==4){
        printf(" ------------------------ A IA venceu! ------------------------\n");
        system("pause");
        return 0;
    }
    ans = aiChooseNumber();
        printf("\n");
        printf("- Jogador:\n");
        printf("\nEscolha uma posicao para o numero %X: ", ans);
        pos = positionChecker();
        binaryArray(pos,ans);
        printf("\n");
	    if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }
        if (winCheck(binarySlots)==4){
            printf(" ------------------------ Voce venceu! ------------------------\n");
            system("pause");
            return 0;
        } else {
            printf(" ------------------------ Empate! ------------------------\n");
            system("pause");
            return 0;
        }
}

int aiPlayFirst() { // função principal para jogar o jogo contra a IA (jogador joga primeiro)
    int pos, ans;
    ans = aiChooseNumber();
    for (int i = 0; i < 7; i++){
        printf("- Jogador:\n");
        printf("\nEscolha uma posicao para o numero %X: ", ans);
        pos = positionChecker();
        binaryArray(pos,ans);
        printf("\n");
	    if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }
        if (winCheck(binarySlots)==4){
            printf(" ------------------------ Voce venceu! ------------------------\n");
            system("pause");
            return 0;
        }
        printf("Escolha um numero: ");
        ans = numberChecker();
        printf("\n");
        pos = aiPlace(ans);
        binaryArray(pos,ans);
        if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }        
        if (winCheck(binarySlots)==4){
            printf(" ------------------------ A IA venceu! ------------------------\n");
            system("pause");
            return 0;
        }
        ans = aiChooseNumber();
    }
    printf("\n");
    printf("- Jogador:\n");
    printf("\nEscolha uma posicao para o numero %X: ", ans);
    pos = positionChecker();
    binaryArray(pos,ans);
    printf("\n");
    if (boardType == HEXADECIMAL) {
        printHexBoard(pos, ans);
    } else if (boardType == BINARY) {
        printBinaryBoard(pos, ans);
    }
    if (winCheck(binarySlots)==4){
        printf(" ------------------------ You won! ------------------------\n");
        system("pause");
        return 0;
    }
    printf("Escolha um numero: ");
    ans = numberChecker();
    printf("\n");
    pos = aiPlace(ans);
    binaryArray(pos,ans);
    if (boardType == HEXADECIMAL) {
        printHexBoard(pos, ans);
    } else if (boardType == BINARY) {
        printBinaryBoard(pos, ans);
    }        
    if (winCheck(binarySlots)==4){
        printf(" ------------------------ A IA venceu! ------------------------\n");
        system("pause");
        return 0;
    } else {
        printf(" ------------------------ Empate! ------------------------\n");
        system("pause");
        return 0;
    }
}