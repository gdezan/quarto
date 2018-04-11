#ifndef begin_H_
#define begin_H_


int slots[16];
int binarySlots[16][4];
int boardType = 1;

void boardTypeCheck (){
    char board[30];
    printf("Welcome to Quarto!\n\nPlease choose your board type by entering the corresponding letter:\n[h] Fills the board with hexadecimal numbers -- [b] Fills the board with binary numbers\n" );
    scanf("%s", &board);
    for(;;){
        if ((board[0] == 72 || board[0] == 104) && strlen(board)<=2){ // if the input is 'H' or 'h'
            boardType = 1;
            break;
        } else if ((board[0] == 66 || board[0] == 98) && strlen(board)<=2){ // if the input is 'B' or 'b'
            boardType = 2;
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


void printHexBoard(int position, int number){ // prints the board after receiving the position and the number of the new answer (using hexadecimal numbers)
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