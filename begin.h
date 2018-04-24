#ifndef begin_H_
#define begin_H_

#define HEXADECIMAL 1
#define BINARY 2
#define EMPTY -1

int slots[16];
int binarySlots[16][4];
int boardType;

void boardTypeCheck (); // asks the user the type of board he wants to play
void initializeSlots();  // initializes the answer array to print empty spaces on the board
void binaryArray (int position, int number); // takes the hex inputs and puts them in a array of binary numbers
void printHexBoard(int position, int number); // prints the board after receiving the position and the number of the new answer (using hexadecimal numbers)
void printBinaryBoard(int position, int number); // prints the board using binary numbers
int multiplayer(); // main function to play the game with no AI

#endif