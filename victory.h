#ifndef VICTORY_H_
#define VICTORY_H_

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

#endif