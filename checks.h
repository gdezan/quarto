#ifndef CHECKS_H_
#define CHECKS_H_

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

#endif