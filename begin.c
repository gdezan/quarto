#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"

void boardTypeCheck (){  // checks what on type of board the user wants to play
    char board[255];
    printf("Welcome to Quarto!\n\nPlease choose your board type by entering the corresponding letter:\n[h] Fills the board with hexadecimal numbers -- [b] Fills the board with binary numbers\n" );
    scanf("%s", &board);
    for(;;){
        if ((board[0] == 72 || board[0] == 104) && strlen(board)==1){ // if the input is 'H' or 'h'
            boardType = HEXADECIMAL;
            break;
        } else if ((board[0] == 66 || board[0] == 98) && strlen(board)==1){ // if the input is 'B' or 'b'
            boardType = BINARY;
            break;
        } else {
            printf("Please try again typing the letter \"h\" or the letter \"b\"\n");
            scanf("%s", &board);
        }
    }
    printf("\n");
}

void initializeSlots(){  // initializes the answer array to print empty spaces on the board
    for (int i = 0; i < 16; i++){
        slots[i] = EMPTY;
        binarySlots[i][0] = EMPTY;
    }
}

void binaryArray (int position, int number) { // takes the hex inputs and puts them in a array of binary numbers
    for (int i = 0; i < 4; i++){
        binarySlots[position][3-i] = (number % 2);
        number = number / 2;
    }
}


void printHexBoard(int position, int number){ // prints the board after receiving the position and the number of the new answer (using hexadecimal numbers)
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


void printBinaryBoard(int position, int number){ // prints the board using binary numbers
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

int numberChecker(){  // uses a while loop to take and check the if the input is compatible and, if not, take the input again
    char readUser[255];
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%s",&readUser);
        required = strtoul(readUser,0,16);
        for (int i = 0; i < 16; i++){
            if (required == slots[i]) {
                used = 1;
            }
        }
        if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 0 && strlen(readUser)==1){ // checks if input is a hexadecimal number
            break;
        } else if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 1 && strlen(readUser)==1){
            printf("This number has already been used. Please choose another one: ");
        } else {
            printf("Please try again using a number between 0 and F (hex): ");
        }
    }
    return required;
}

int positionChecker(){  // uses a while loop to take and check the if the position is not taken and, if it is, take the position again
    char readUser[255];
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%s",&readUser);
        required = strtoul(readUser,0,16);
        if (slots[required] != EMPTY) {
            used = 1;
        }
        if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 0 && strlen(readUser)==1){ // checks if input is a hexadecimal number
            break;
        } else if (((readUser[0] <= 57 && readUser[0] >= 48) || (readUser[0] <= 70 && readUser[0] >= 65) || (readUser[0] <= 102 && readUser[0] >= 97)) && used == 1 && strlen(readUser)==1){
            printf("This position has already been used. Please choose another one: ");
        } else {
            printf("Please try again using a number between 0 and F (hex): ");
        }
    }
    return required;
}

int winCheck() { //function to check victory
    int won = 0;
    int slot, bit, line, column;
    for (line = 0; line < 16; line = line+4){  //checks if there is any alignments on the lines
        for (bit = 0; bit < 4; bit++) {
            for (slot = line; slot < line+4; slot++){
                if (binarySlots[slot][bit] == binarySlots[slot+1][bit] && binarySlots[slot][0] != -1 && slot == line){
                    won++;
                    slot++;
                }
                if (binarySlots[slot][bit] == binarySlots[slot-1][bit] && binarySlots[slot][0] != -1){
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
    for (column = 0; column < 4; column++){  //checks if there is any alignments on the columns
        for (bit = 0; bit < 4; bit++) {
            for (slot = column; slot < column+13; slot = slot+4){
                if (binarySlots[slot][bit] == binarySlots[slot+4][bit] && binarySlots[slot][0] != -1 && slot == column){
                    won++;
                    slot=slot+4;
                }
                if (binarySlots[slot][bit] == binarySlots[slot-4][bit] && binarySlots[slot][0] != -1){
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
    for (bit = 0; bit < 4; bit++) {   //checks if there is any alignments on the first diagonal (slots 0, 5, A and F)
        for (slot = 0; slot < 16; slot = slot+5){
            if (binarySlots[slot][bit] == binarySlots[slot+5][bit] && binarySlots[slot][0] != -1 && slot == 0){
                won++;
                slot=slot+5;
            }
            if (binarySlots[slot][bit] == binarySlots[slot-5][bit] && binarySlots[slot][0] != -1){
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
    for (bit = 0; bit < 4; bit++) {   //checks if there is any alignments on the second diagonal (slots 3, 6, 9 and C)
        for (slot = 3; slot < 13; slot = slot+3){
            if (binarySlots[slot][bit] == binarySlots[slot+3][bit] && binarySlots[slot][0] != -1 && slot == 3){
                    won++;
                    slot=slot+3;
            }
            if (binarySlots[slot][bit] == binarySlots[slot-3][bit] && binarySlots[slot][0] != -1){
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

int multiplayer() { // main function to play the game with no AI
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
