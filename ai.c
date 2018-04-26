#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "ai.h"

void test(){
    
    printf("\n\n%d\n\n\n", possibleAnswers[15][2]);
}

void innitPossible() {
    int number;
    for (int i = 0; i < 16; i++){
        number = i;
        for (int j = 0; j < 4; j++){
            possibleAnswers[i][3-j] = (number % 2);
            number = number / 2;
        }
    }
}

int aiPlace (int ans){ // will return the position of the piece chosen by the player
    int tmp, pos, used; 
    int testArr[16][4];
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j];
        }
    }
    for (int i = 0; i < 16; i++){
        used = 0;
        tmp = ans;
        for (int j = 0; j < 4; j++){
            testArr[i][3-j] = tmp % 2;
            tmp = tmp/2;
        }
        for (int j = 0; j < 16; j++){
            if (i == slots[j]) {
                used = 1;
            }
        }
        if (winCheck(testArr)== 4 && used == 0){
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

int aiChoose() { // will return a new piece for the player to choose the position
    
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
    int randIndex = rand() % (counter+1);
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

int aiPlay() {
    int pos, ans, pNumber;
    printf("- Player:\n");
    printf("Choose the number: ");
    ans = numberChecker();
    printf("\n");
    for (int i = 0; i < 15; i++){
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
        ans = aiChoose();
        printf("\n");
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
}