#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "ai.h"

int aiPlace (int ans){ // will return the position of the piece chosen by the player
    int tmp, pos; 
    int testArr[16][4]; // test array to check what positions are able to win
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j]; // copies the original array to begin the tests
        }
    }
    for (int i = 0; i < 16; i++){ // adds every possible position in the test array and checks if it is a winner position or not
        tmp = ans;
        for (int j = 0; j < 4; j++){
            testArr[i][3-j] = tmp % 2;
            tmp = tmp/2;
        }
        if (winCheck(testArr)== VICTORY && slots[i] == EMPTY){
            return i; 
        } else {
            for (int j = 0; j < 4; j++){
                testArr[i][j] = binarySlots[i][j]; // returns the test array to the original condition so it can test other positions
            }
        }        
    }
    pos = rand() % 16;
    while (slots[pos] != EMPTY){
        pos = rand() % 16;  // if there is no winning position, the function will return a random position (that is empty)
    }
    return pos;
}

int aiChooseNumber() { // will return a new piece for the player to choose the position
    
    int tmp, possible, used; 
    int counter = 0;
    int testArr[16][4]; // same principle as the test array from aiPlace()
    int possibleArr[16]; // array that stores numbers that will not give a win to the player
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
                used = 1; // checks if the number has already been used (1 means yes, 0 means no)
            }
        }
        if (used == 0) {
            for (int j = 0; j < 16; j++){                   // goes through all positions and numbers
                if (slots[j] == EMPTY){                     
                    tmp = i;
                    for (int k = 0; k < 4; k++){
                        testArr[j][3-k] = tmp % 2;
                        tmp = tmp/2;
                    }
                    if (winCheck(testArr) == VICTORY){      // if a number can give the victory to the player,
                        possible = 0;                       // it will be discarded
                    }
                    for (int k = 0; k < 4; k++){
                        testArr[j][k] = binarySlots[j][k];
                    }

                }
            }
            if (possible == 1){
                possibleArr[counter] = i; // adds the possible answers in the array
                counter++;
            }
        }
    }
    int randIndex = rand() % (counter);
    if (possibleArr[0] == -1){                  // if this condition is met, it means that there 
        used = 1;                               // is no number that can't give a win to the player.
        while (used == 1){                      // The function will then return a random 
            used = 0;                           // number that hasn't been used
            num = rand() % 16;
            for (int j = 0; j < 16; j++){
                if (num == slots[j]) {
                    used = 1;
                }
            }
        }
    } else {
        num = possibleArr[randIndex]; // returns a random number that won't give a win to the player
    }
    return num;
}

int aiPlaySecond() { // main function to play the game against AI (player goes first)
    int pos, ans;
    printf("\n- Player:\n");
    printf("Choose a number: ");
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
        printf("Choose a number: ");
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
        printf("\n- Player:\n");
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
        printf("Choose a number: ");
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
    printf("Choose a number: ");
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