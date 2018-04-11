#include <stdio.h>
#include <stdlib.h>
#include "begin.h"
#include "victory.h"
#include "checks.h"

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
