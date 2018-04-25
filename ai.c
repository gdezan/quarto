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

void aiPlace() { // function for the AI to place the winning piece
    
    int slot, emptySlot, emptyCount, used; 
    int testArr[16][4];
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            testArr[i][j] = binarySlots[i][j];
        }
    }
    for (int line = 0; line < 16; line = line+4){ // check if there is a winning place in the lines
        emptyCount = 0;
        for (slot = line; slot < line+4; slot++){
            if (testArr[slot][0] == -1){
                emptyCount++;
                emptySlot = slot;
            }
        }
        if (emptyCount == 1){
            for (int i = 0; i < 16; i++){
                for (int j = 0; j < 4; j++){
                    testArr[emptySlot][j] = possibleAnswers[i][j];
                }
                used = 0;
                for (int k = 0; k < 16; k++){
                    if (i == slots[k]) {
                        used = 1;
                    }
                }
                if (winCheck(testArr) == 4 && used != 1){
                    slots[emptySlot] = i;
                    for (int j = 0; j < 4; j++){
                        binarySlots[emptySlot][j] = testArr[emptySlot][j];
                    }   
                }
            }
        }
    }
    for (int column = 0; column < 4; column++){ // check if there is a winning place in the columns
        emptyCount = 0;
        for (slot = column; slot < column+13; slot = slot+4){
            if (testArr[slot][0] == -1){
                emptyCount++;
                emptySlot = slot;
            }
        }
        if (emptyCount == 1){
            for (int i = 0; i < 16; i++){
                for (int j = 0; j < 4; j++){
                    testArr[emptySlot][j] = possibleAnswers[i][j];
                }
                for (int k = 0; k < 16; k++){
                    if (i == slots[k]) {
                        used = 1;
                    }
                }
                if (winCheck(testArr) == 4 && used != 1){
                    slots[emptySlot] = i;
                    for (int j = 0; j < 4; j++){
                        binarySlots[emptySlot][j] = testArr[emptySlot][j];
                    }   
                }
            }
        }
    }
        
    // for (slot = 0; slot < 16; slot = slot+5){ // check if there is a winning place in the first diagonal
    //     emptyCount = 0;
    //     if (testArr[slot][0] == -1){
    //         emptyCount++;
    //         emptySlot = slot;
    //     }
    
    //     if (emptyCount == 1){
    //         for (int i = 0; i < 16; i++){
    //             for (int j = 0; j < 4; j++){
    //                 testArr[emptySlot][j] = possibleAnswers[i][j];
    //             }
    //             if (winCheck(testArr) == 4){
    //                 slots[emptySlot] = i;
    //                 for (int j = 0; j < 4; j++){
    //                     binarySlots[emptySlot][j] = testArr[emptySlot][j];
    //                 }   
    //             }
    //         }
    //     }
    // }

    // for (slot = 3; slot < 13; slot = slot+3){ // check if there is a winning place in the second diagonal
    //     emptyCount = 0;
    //     if (testArr[slot][0] == -1){
    //         emptyCount++;
    //         emptySlot = slot;
    //     }
    
    //     if (emptyCount == 1){
    //         for (int i = 0; i < 16; i++){
    //             for (int j = 0; j < 4; j++){
    //                 testArr[emptySlot][j] = possibleAnswers[i][j];
    //             }
    //             if (winCheck(testArr) == 4){
    //                 slots[emptySlot] = i;
    //                 for (int j = 0; j < 4; j++){
    //                     binarySlots[emptySlot][j] = testArr[emptySlot][j];
    //                 }   
    //             }
    //         }
    //     }
    // }
}