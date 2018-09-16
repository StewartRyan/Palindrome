//
// Created by Ryan on 23/02/2018.
//

#ifndef ASSIGNMENT1_PAL_H
#define ASSIGNMENT1_PAL_H

#include <stdbool.h>

void startGame(int);
void displayState(int[], int, int, int);
void moveCursorLeft(int*, int*);
void moveCursorRight(int*, int, int*);
void incrementDigitInListAtPos(int*, int*);
void decrementDigitInListAtPos(int*, int*);
bool isPalindrome(const int[], int);
char getCommand();
void processCommand(int[], int, int *, char, int *a);
void setCursorRandomly(int*, int);
int* numberToDigitArray(int, int*);
bool isCommandValid(const char*, char);

#endif //ASSIGNMENT1_PAL_H
