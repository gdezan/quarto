#ifndef ai_H_
#define ai_H_

int aiPlayFirst();      // main function to play the game against AI (AI goes first)
int aiPlaySecond();     // main function to play the game against AI (player goes first)
int aiChooseNumber();   // will return a new piece for the player to choose the position
int aiPlace(int ans);   // will return the position of the piece chosen by the player

#endif