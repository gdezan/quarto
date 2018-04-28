#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "begin.h"
#include "ai.h"

int main()
{
    srand(time(NULL));
    initializeSlots();
    boardTypeCheck();
    int game = gameTypeCheck();
    if (game == 1){
        multiplayer();
    } else if (game == 2){
        aiPlayFirst();
    } else {
        aiPlaySecond();
    }
    printf("\n");
}
