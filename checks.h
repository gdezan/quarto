#ifndef CHECKS_H_
#define CHECKS_H_

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

int positionChecker(){  // uses a while loop to take and check the if the position is not taken and, if it is, take the position again
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

#endif