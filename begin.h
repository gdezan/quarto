#ifndef begin_H_
#define begin_H_


int slots[16];
int binarySlots[16][4];

void initializeSlots(){  // initializes the answer array to print empty spaces on the board
    for (int i = 0; i < 16; i++){
        slots[i] = -1;
        binarySlots[i][0] = -1;
    }
}

void binaryArray (int position, int number) { // takes the hex inputs and puts them in a array of binary numbers
    for (int i = 0; i < 4; i++){
        binarySlots[position][3-i] = (number % 2);
        number = number / 2;
    }
}


void printBoard(int position, int number){ // prints the board after receiving the position and the number of the new answer (using hexadecimal numbers)
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

#endif