#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "ai.h"

int aiPlace (int ans){ // will return the position of the piece chosen by the player
    int tmp, pos; 
    int testArr[16][4];
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j];
        }
    }
    for (int i = 0; i < 16; i++){
        tmp = ans;
        for (int j = 0; j < 4; j++){
            testArr[i][3-j] = tmp % 2;
            tmp = tmp/2;
        }
        if (winCheck(testArr)== 4 && slots[i] == -1){
            return i; 
        } else {
            for (int j = 0; j < 4; j++){
                testArr[i][j] = binarySlots[i][j];
            }
        }        
    }
    pos = rand() % 16;
    while (slots[pos] != -1){
        pos = rand() % 16;
    }
    return pos;
}

int aiChooseNumber() { // will return a new piece for the player to choose the position
    
    int tmp, possible, used; 
    int counter = 0;
    int testArr[16][4];
    int possibleArr[16];
    int num = -1;
    for (int i = 0; i < 16; i++){
        possibleArr[i] = -1;
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j];
        }
    }

    for (int i = 0; i < 16; i++){
        possible = 1;
        used = 0;
        for (int j = 0; j < 16; j++){
            if (i == slots[j]) {
                used = 1;
            }
        }
        if (used == 0) {
            for (int j = 0; j < 16; j++){
                if (slots[j] == -1){
                    tmp = i;
                    for (int k = 0; k < 4; k++){
                        testArr[j][3-k] = tmp % 2;
                        tmp = tmp/2;
                    }
                    if (winCheck(testArr) == 4){
                        possible = 0;
                    }
                    for (int k = 0; k < 4; k++){
                        testArr[j][k] = binarySlots[j][k];
                    }

                }
            }
            if (possible == 1){
                possibleArr[counter] = i;
                counter++;
            }
        }
    }
    int randIndex = rand() % (counter);
    if (possibleArr[0] == -1){
        used = 1;
        while (used == 1){
            used = 0;
            num = rand() % 16;
            for (int j = 0; j < 16; j++){
                if (num == slots[j]) {
                    used = 1;
                }
            }
        }
    } else {
        num = possibleArr[randIndex];
    }
    return num;
}

int aiPlaySecond() { // main function to play the game against AI (player goes first)
    int pos, ans;
    printf("- Player:\n");
    printf("Choose the number: ");
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
            printf(" ------------------------ The AI won! ------------------------\n");
            system("pause");
            return 0;
        }
        ans = aiChooseNumber();
        printf("\n");
        printf("- Player:\n");
        printf("\nChoose a position for the number %X: ", ans);
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
        printf("Choose the next number: ");
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
        printf(" ------------------------ The AI won! ------------------------\n");
        system("pause");
        return 0;
    }
    ans = aiChooseNumber();
        printf("\n");
        printf("- Player:\n");
        printf("\nChoose a position for the number %X: ", ans);
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
        } else {
            printf(" ------------------------ It's a Tie! ------------------------\n");
            system("pause");
            return 0;
        }
}

int aiPlayFirst() { // main function to play the game against AI (AI goes first)
    int pos, ans;
    ans = aiChooseNumber();
    for (int i = 0; i < 7; i++){
        printf("\n");
        printf("- Player:\n");
        printf("\nChoose a position for the number %X: ", ans);
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
        printf("Choose the next number: ");
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
            printf(" ------------------------ The AI won! ------------------------\n");
            system("pause");
            return 0;
        }
        ans = aiChooseNumber();
    }
    printf("\n");
    printf("- Player:\n");
    printf("\nChoose a position for the number %X: ", ans);
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
    printf("Choose the next number: ");
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
        printf(" ------------------------ The AI won! ------------------------\n");
        system("pause");
        return 0;
    } else {
        printf(" ------------------------ The AI won! ------------------------\n");
        system("pause");
        return 0;
    }
}