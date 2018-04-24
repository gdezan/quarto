#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "victory.h"
#include "checks.h"

int multiplayer() {
    int pos, ans, pNumber;
    printf("- Player 1:\n");
    printf("Choose the number: ");
    ans = numberChecker();
    printf("\n");
    for (int i = 0; i < 15; i++){
        if (i % 2 != 0) {  // attributes a number to the player (player 1 / player 2)
            pNumber = 1;
            printf("- Player %d:", pNumber);
        } else {
            pNumber = 2;
            printf("- Player %d:", pNumber);
        }
        printf("\nChoose a position for the number: ");
        pos = positionChecker();
        binaryArray(pos,ans);
        printf("\n");
	    if (boardType == HEXADECIMAL) {
	        printHexBoard(pos, ans);
	    } else if (boardType == BINARY) {
	        printBinaryBoard(pos, ans);
	    }
        
        if (winCheck()==4){
            printf(" ------------------------ Player %d won! ------------------------\n", pNumber);
            system("pause");
            return 0;
        }

        printf("Choose the next number: ");
        ans = numberChecker();
        printf("\n");

    }
    printf("- Player 2:\n");
    printf("\nChoose a position for the number: ");
    pos = positionChecker();
    binaryArray(pos,ans);
    printf("\n");
    if (boardType == HEXADECIMAL) {
        printHexBoard(pos, ans);
    } else if (boardType == BINARY) {
        printBinaryBoard(pos, ans);
    }

    if (winCheck()==4){
        printf(" ------------------------ Player %d won! ------------------------\n", pNumber);
        system("pause");
        return 0;
    } else {
    	printf(" ------------------------ It's a Tie! ------------------------\n");
    	system("pause");
    }
}