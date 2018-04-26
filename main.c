#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "begin.h"
#include "ai.h"

int main()
{
    srand(time(NULL));
    innitPossible();
    //test();
    initializeSlots();
    boardTypeCheck();
    aiPlay();
}
