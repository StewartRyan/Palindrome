//
// Created by Ryan on 23/02/2018.
//

#include <printf.h>
#include <stdlib.h>
#include "pal.h"
/**
 * This starts the palindrome game
 * @param number
 */
void startGame(int number) {
    // Attributes
    int numberOfDigits;
    int positionOfCursor;
    int numberOfGoes;

    // Array of numbers
    int* listOfNumbers;

    // Set number of goes to 0
    numberOfGoes = 0;

    // Put number into an array of digits and set total number of digits
    listOfNumbers = numberToDigitArray(number, &numberOfDigits);

    // Randomly set the position of the cursor
    setCursorRandomly(&positionOfCursor, numberOfDigits);

    // Keep asking the user to interact with the game until a palindrome has been formed
    while (!isPalindrome(listOfNumbers, numberOfDigits)) {
        // Always display state of game before receiving user input
        displayState(listOfNumbers, numberOfDigits, positionOfCursor, numberOfGoes);

        // Get command from user
        char userCommand = getCommand();

        // Based on what the user entered, carry out the function related to the input
        processCommand(listOfNumbers, numberOfDigits, &positionOfCursor, userCommand, &numberOfGoes);
    }

    // Display the winning palindrome
    displayState(listOfNumbers, numberOfDigits, 0, numberOfGoes);

    // Tell the user that they have won the game in N number of goes
    printf("\n\nCongratulations! You completed the game in %d number of goes", numberOfGoes);
}

/**
 * Display the current state of the game
 * @param list array of numbers
 * @param size numbers of digits in array of numbers
 * @param cursorPosition position of the cursor
 */
void displayState(int list[], int size, int cursorPosition, int goes) {
    // Print opening line
    printf("------ Game State -------\n[ ");

    // Iterate through int array and print number
    for (int i = 0; i < size; ++i)
        printf("%d ", list[i]);

    // Print closing bracket
    printf("] Goes: %d\n", goes);

    // Print empty spaces
    for (int j = 0; j < cursorPosition; ++j)
        printf("  ");

    // Print cursor marker
    if (cursorPosition > 0 && cursorPosition <= size)
        printf("^\n");
}

/**
 * Move the 'cursor' one place to the left
 * @param cursorPtr a pointer to cursor int
 */
void moveCursorLeft(int* cursorPtr, int* numGoes) {
    // If cursor is already at the first number, it cannot move any further left
    if (*cursorPtr > 1) {
        // Change cursor position
        (*cursorPtr)--;

        // Increment number of goes
        (*numGoes)++;
    }
}

/**
 * Move the 'cursor' one place to the right
 * @param cursorPtr a pointer to cursor int
 * @param numDigits total number of digits in the number
 */
void moveCursorRight(int* cursorPtr, int numDigits, int* numGoes) {
    // If cursor is already at the last number, it cannot move any further right
    if (numDigits > *cursorPtr) {
        (*cursorPtr)++;

        // Increment number of goes
        (*numGoes)++;
    }
}

/**
 * Increment the currently 'selected' number
 */
void incrementDigitInListAtPos(int* number, int* numGoes) {
    // If number is 9 reset it to 0, else increment it
    *number = (*number == 9) ? 0 : *number+1;

    // Increment number of goes
    (*numGoes)++;
}

/**
 * Decrement the currently 'selected' number
 */
void decrementDigitInListAtPos(int* number, int* numGoes) {
    // If number is 0 reset it to 9, else decrement it
    *number = (*number == 0) ? 9 : *number-1;

    // Increment number of goes
    (*numGoes)++;
}

/**
 * Determines if current list is palindrome
 * @param list contains all numbers
 * @param numberDigits size of list
 * @return bool true/false
 */
bool isPalindrome(const int list[], int numberDigits) {
    // Declare half size int
    int halfSize = (numberDigits/2);

    // iterate through half the list
    for (int i = 0; i < halfSize; i++)
        // If number in list doesn't match its mirror in the second
        // half of the list, return false, since it's not a palindrome
        if (list[i] != list[numberDigits-1])
            return false;
        else
            // Decrement numberDigits to check the next pair of numbers
            numberDigits--;

    // Return true if false hasn't been returned
    return true;
}

/**
 * Request a valid command from the user and return the given value
 * @return
 */
char getCommand() {
    // All accepted chars
    char validCharacters[] = { 'a','d', 'w', 's'};

    // Get the input of the user
    char input;

    // Keep going until user entered accepted command
    do {
        // Tell the user what input they can enter
        printf("\nEnter a valid command by keyword( ");

        // Print all accepted commands
        for (int i = 0; i < 4; ++i)
            printf("%c ", validCharacters[i]);

        // Print closing bracket
        printf(")");

        // Get user input
        input = getchar();

        getchar();
    } while(!isCommandValid(validCharacters, input));

    // Return the command
    return input;
}


/**
 * Check if user command is in the array of accepted commands
 * @param acceptedCommands
 * @param command
 * @return
 */
bool isCommandValid(const char acceptedCommands[], char command) {
    // Iterate through all accepted commands
    for (int i = 0; i < (sizeof(acceptedCommands) / sizeof(char)); i++)
        // If command is found, return true
        if (acceptedCommands[i] == command)
            return true;

    // Return false since true was not returned
    return false;
}

/**
 * Processes the user's command
 * @param pList
 * @param size
 * @param pPositionOfCursor
 * @param command
 */
void processCommand(int pList[], int size, int *pPositionOfCursor, char command, int *numGoes) {
    // Based on what the user entered, carry out the function related to the input
    switch (command) {
        // Move cursor left
        case 'a': moveCursorLeft(pPositionOfCursor, numGoes); break;

        // Move cursor right
        case 'd': moveCursorRight(pPositionOfCursor, size, numGoes); break;

        // Increment selected number
        case 'w': incrementDigitInListAtPos(pList + (*pPositionOfCursor - 1), numGoes); break;

        // Decrement selected number
        case 's': decrementDigitInListAtPos(pList + (*pPositionOfCursor - 1), numGoes); break;

        // Print error message
        default : printf("ERROR something went wrong\n"); break;
    }

}

/**
 * Randomly sets the position of the cursor
 * @param cursor
 */
void setCursorRandomly(int* cursor, int size) {
    // Seed the randomizer
    srand(time(NULL));

    *cursor =  (rand() % (size-1)) + 1;
}

/**
 * Insert number's digits into array of type int
 * @param number
 * @param totalNumDigits
 * @return
 */
int* numberToDigitArray(int number, int* totalNumDigits) {
    // Declare counter
    int numOfDigitCounter = 0;

    // Declare a copy
    int numberCopy = number;

    // Loop to find total amount of numbers in
    while(numberCopy > 0){
        // Divide number by 10 to reduce it
        numberCopy /= 10;

        // Increment counter
        numOfDigitCounter++;
    }

    // Dynamically allocate memory for the array
    int* digitArray = (int*)malloc(sizeof(int) * numOfDigitCounter);

    // Set total number of digits to what we have just counted
    *totalNumDigits = numOfDigitCounter;

    // Put each number into the newly created dynamic array of int
    for (int j = numOfDigitCounter; j > 0; j--) {
        // Use modulus to reduce number
        digitArray[j-1] = number % 10;

        // Divide number by 10 to reduce it
        number /= 10;
    }

    return digitArray;
}