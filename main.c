#include <stdio.h>
#include <stdlib.h>

int slots[16];
int binarySlots[16][4];

void initializeSlots(){  // initializes the answer array to print empty spaces on the board
    for (int i = 0; i < 16; i++){
        slots[i] = -1;
        binarySlots[i][0] = -1;
    }
}

void printBoard(int position, int number){ // prints the board after receiving the position and the number of the new answer
    slots[position] = number;
    int counter = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (slots[counter] == -1) {
                printf("| |");
            }  else {
                printf("|%x|",slots[counter]);
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
            if (slots[counter] == -1) {
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
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%x",&required);
        for (int i = 0; i < 16; i++){
            if (required == slots[i]) {
                used = 1;
            }
        }
        if (required <= 15 && required >= 0 && used == 0){
            break;
        } else if (required <= 15 && required >= 0 && used == 1){
            printf("This number has already been used. Please choose another one: ");
        } else {
            printf("Please try again using a number between 0 and F (hex): ");
        }
    }
    return required;
}

int positionChecker(){  // uses a while loop to take and check the if the position is not taken and, if not, take the position again
    int required;
    int used;
    for (;;) {
        used = 0;
        scanf("%x",&required);
        if (slots[required] != -1) {
            used = 1;
        }
        if (required <= 15 && required >= 0 && used == 0){
            break;
        } else if (required <= 15 && required >= 0 && used == 1){
            printf("This position has already been used. Please choose another one: ");
        } else {
            printf("Please try again using a number between 0 and F (hex): ");
        }
    }
    return required;
}

void binaryArray (int position, int number) { // takes the hex inputs and puts them in a array of binary numbers
    for (int i = 0; i < 4; i++){
        binarySlots[position][3-i] = (number % 2);
        number = number / 2;
    }
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
    for (bit = 0; bit < 4; bit++) {   //checks if there is any alignments on the first diagonal
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
    for (bit = 0; bit < 4; bit++) {   //checks if there is any alignments on the second diagonal
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
void pArray() {
    for (int a = 0; a < 16; a++){
        for (int i = 0; i < 4; i++){
                printf("%d",binarySlots[a][i]);
            }
        printf("\n");
    }
}
int main()
{
    int pos, ans, pNumber;
    initializeSlots();
    printf("- Player 1:\n");
    printf("Enter the next number: ");
    ans = numberChecker();
    printf("\n");
    for (int i = 0; i < 15; i++){
        if (i % 2 != 0) {
            pNumber = 1;
            printf("- Player %d:", pNumber);
        } else {
            pNumber = 2;
            printf("- Player %d:", pNumber);
        }
        printf("\nEnter the position of the previous number: ");
        pos = positionChecker();
        binaryArray(pos,ans);
        printf("\n");
        printBoard(pos,ans);

        if (winCheck()==4){
            printf(" ------------------------ Player %d won ------------------------\n", pNumber);
            system("pause");
            return 0;
        }

        printf("Enter the next number: ");
        ans = numberChecker();
        printf("\n");

    }
    printf("- Player 2:\n");
    printf("\nEnter the position of the previous number: ");
    pos = positionChecker();
    binaryArray(pos,ans);
    printf("\n");
    printBoard(pos,ans);

    if (winCheck()==4){
        printf(" ------------------------ Player %d won ------------------------\n", pNumber);
        system("pause");
        return 0;
    }
}
