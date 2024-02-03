/*
Name: Suman Bhandari
Date: 16/11/2023
Program 4: Chutes and Ladders Game
Introduction:
In this game, two players take turns rolling a die.
The goal is to be the first to reach the end of the board.
Players roll a 6-sided die, and move accordingly. Special squares, like chutes ('a'-'m')
and ladders ('o'-'z') helps move the players forward and backward and they get removed after the player lands on it .
 Backward ('B') and Forward ('F') squares directs players to move backward or forward to next available haven on the board.
 Havens ('H') disappears after a player lands on them using B or F squares and is replaced with '*'.
The game continues until one player reaches or surpasses the end of the board, triggering the endgame.
Player collisions, where one lands on the other's square, results in the player causing collisions  to move back 1 position.
 But, this is not in effect if both players are at the beginning of the game.
Functions like move, output, findHaven, and chuteLadder manage different aspects of player movement and board updates.
 Player positions and board manipulation are strictly handled using pointers and pointer arithmetic, emphasizing
a pointer-centric approach.
The main loop directs the game's flow, updating the board, and ultimately declaring the winner.

 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function prototypes

//Responsible for handling a player's movement based on the die roll and special squares.
char* move(char*, char*, int, char*, int);

//Writes the current state of the game board to a file.
void output(char* board, char* player1, char* player2, FILE* outputFile);

//Locates the next 'H' square on the board for the player's movement.
char* findHaven(char*, char*, int SIZE);

//handles the player's movement on chutes or ladders
char* chuteLadder(char*);

//The main function initializes the game by setting up players, the game board, and the output file.
// It runs a loop where players take turns moving and updating the board until one player wins.
// After the loop, it determines the winner based on who has progressed the farthest on the board,
// not necessarily the first to reach the end, and declares the winner.

int main() {
    //Defining the SIZE of a board as a constant 100
    int const SIZE = 100;
    //Initializing variables
    char board[100]="  mHk tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB ";
    char *p1, *p2;
    FILE *outputFile;

    // Initializing the players
    p1 = board;
    p2 = board;

    //  random number generator
    srand(time(NULL));

    // Opening the FILE as an output file
    outputFile = fopen("output.txt", "w");

//Loop continues until a player wins

    while (p1 < board + SIZE && p2 < board + SIZE) {
        //Player 1 turn
        p1 = move(p1, p2, 1, board, SIZE);
        //Player 2 turn
        p2 = move(p2, p1, 2, board, SIZE);


        output(board, p1, p2, outputFile);

        // Check the winning condition and breaking out of the loop

        if (p1 >= board + SIZE || p2 >= board + SIZE) {
            break;
        }
    }


    // Determine and output the winner after the loop
    if (p1 > p2) {
        printf("Player 1 wins! \n");
    } else if (p2 > p1) {
        printf("Player 2 wins! \n");
    } else {
        printf("Tie. \n");
    }

    // Close the output file
    fclose(outputFile);

    // Return a value indicating successful execution
    return 0;
}

//The move method manages player movement in this game.
// It moves the player accordingly to the rolling of dice,
// handles special squares like chutes, ladders, forwards, or backward movements,
// and resolves collisions with the opponent.
// It ensures all player actions and outcomes are displayed via output .
char* move(char* player, char* secondPlayer, int playerNumber, char* board, int SIZE) {
    int diceMove = rand() % 6 + 1;  // Randomly generate a move between 1 and 6
    char* resultingMove = player + diceMove;

    // Output the result of the player's move
    printf("Player %d rolled %d and is moved to %ld", playerNumber, diceMove, resultingMove - board);

    //Check if the player is still within the board
    //AND determining if the player has landed on chute/ladder/B/F and calling appropriate functions
    if(resultingMove>= board && resultingMove < board + SIZE) {
        // Check for special squares and update the player's position accordingly
        //Checking for chute
        if (*resultingMove >= 'a' && *resultingMove <= 'm') {
            resultingMove = chuteLadder(resultingMove);
            printf(" and landed on a chute and slid down to %ld", resultingMove - board);
            //checking for ladder
        } else if (*resultingMove >= 'o' && *resultingMove <= 'z') {
            resultingMove = chuteLadder(resultingMove);
            printf(" and landed on a ladder and climbed up to %ld", resultingMove - board);
        }
            //Checking for forward and backward move and printing appropriately
        else if (*resultingMove == 'F' || *resultingMove == 'B') {
            if (*resultingMove == 'B') {
                printf("and landed on a 'B', and moved backward to ");
            } else {                                                     // when *resultingMove = 'F'
                printf("and landed on a 'F', and moved to ");
            }
            resultingMove = findHaven(resultingMove, board, SIZE);
            // Move the player to the beginning of the board if there are no more havens while moving backward
            if (resultingMove == board ) {
                printf("the beginning of the board");
            } else {
                printf("%ld ", resultingMove - board);
            }
        }

        //If we reach board + SIZE while moving forward then we should stop searching and don't move the player

        // Checking for collision
        if (resultingMove == secondPlayer) {
            resultingMove -= 1; // player causing collision moves back 1 step
            printf(" and landed on the other player and moved back to %ld", resultingMove - board);

        }
    }

    printf("\n");

    return resultingMove;
}




// Function to output the current game board to a disk file
// Parameters used:
// - board: Pointer to the game board string
// - player1: Pointer to the current position of player 1 on the game board
// - player2: Pointer to the current position of player 2 on the game board
// - outputFile: FILE pointer to the output file
void output(char* board, char* player1, char* player2, FILE* outputFile) {
    // Pointer to iterate through the game board
    char* current = board;

    // Iterate through the game board until the end of the string is reached
    while (*current != '\0') {
        // Check if the current position is where player 1 is
        if (*current == *player1) {
            // Output '1' to represent player 1's position
            //Output is generated character - by character
            putc('1', outputFile);
        }
            // Check if the current position is where player 2 is
        else if (*current == *player2) {
            // Output '2' to represent player 2's position
            putc('2', outputFile);
        }
            // If neither player is at the current position
        else {
            // Output the character at the current position
            putc(*current, outputFile);
        }

        // Move to the next position on the game board
        current++;
    }

    // Output a newline character at the end to separate each board state
    putc('\n', outputFile);
}


// Function to find the next 'H' on the game board
// Parameters:
// - currentPosition: Pointer to the current position of the player on the game board
// - board: Pointer to the game board string
// - size: Size of the game board
char* findHaven(char* currentPosition, char* board, int SIZE) {
    // Pointer to store the result (new location of the player)

    char *result = currentPosition;

    // Iterate through the characters on the board starting from the current position (result)
    // and continue until it finds the next 'H' or reaches the end of the board (board + size).

    // While moving forward, if it reaches board + SIZE then we should stop searching and do not move the player.
    if (*currentPosition == 'F') {
        result++;
        while (result < board + SIZE && *result != 'H') {
            result++;
        }
    }else {         // if *currentPosition == 'B'
        result--;
        // While moving backward if we reach beginning then, stop searching and move the player there.
        //So, it moves backward until the haven is found or unless the beginning is reached
        while (result != board && *result != 'H') {
            result--;

        }
    }

    // If the player has been moved to an 'H', change it on the board to '*'
    if (*result == 'H' && (*currentPosition == 'B' || *currentPosition == 'F')) {
        *result = '*';
    }

    // Return the new location of the player on the game board
    return result;
}

// Function to handle the player's movement on chutes or ladders
// Parameters: player: Pointer to the current position of the player on the game board
// Returns: Pointer to the updated location of the player on the game board
char* chuteLadder(char* player) {
    // Calculate the distance based on the ASCII value difference between the current character and 'n'.
    int distance = *player - 'n';

    // Store the current location in a temp pointer
    char* temp = player;

    // Move the player's position forward or backward on the game board by the calculated distance
    player += distance;

    // Reset the letter at the original position to '-'
    *temp = '-';

    // Return the updated position of the player on the game board
    return player;
}


/*
 * OUTPUT
Player 1 rolled 1 and is moved to 1
Player 2 rolled 6 and is moved to 6 and landed on a ladder and climbed up to 12
Player 1 rolled 3 and is moved to 4 and landed on a chute and slid down to 1
Player 2 rolled 1 and is moved to 13
Player 1 rolled 1 and is moved to 2 and landed on a chute and slid down to 1
Player 2 rolled 4 and is moved to 17 and landed on a chute and slid down to 15
Player 1 rolled 2 and is moved to 3
Player 2 rolled 4 and is moved to 19
Player 1 rolled 5 and is moved to 8
Player 2 rolled 3 and is moved to 22
Player 1 rolled 4 and is moved to 12
Player 2 rolled 6 and is moved to 28
Player 1 rolled 2 and is moved to 14 and landed on a chute and slid down to 5
Player 2 rolled 4 and is moved to 32
Player 1 rolled 6 and is moved to 11and landed on a 'B', and moved backward to 7
Player 2 rolled 6 and is moved to 38 and landed on a chute and slid down to 34
Player 1 rolled 1 and is moved to 8
Player 2 rolled 2 and is moved to 36
Player 1 rolled 6 and is moved to 14
Player 2 rolled 1 and is moved to 37
Player 1 rolled 5 and is moved to 19
Player 2 rolled 4 and is moved to 41
Player 1 rolled 6 and is moved to 25 and landed on a chute and slid down to 19
Player 2 rolled 5 and is moved to 46 and landed on a ladder and climbed up to 50
Player 1 rolled 4 and is moved to 23
Player 2 rolled 6 and is moved to 56 and landed on a ladder and climbed up to 63
Player 1 rolled 4 and is moved to 27 and landed on a ladder and climbed up to 38
Player 2 rolled 6 and is moved to 69
Player 1 rolled 5 and is moved to 43and landed on a 'B', and moved backward to 41
Player 2 rolled 6 and is moved to 75and landed on a 'F', and moved to 79
Player 1 rolled 2 and is moved to 43and landed on a 'B', and moved backward to 33
Player 2 rolled 3 and is moved to 82 and landed on a chute and slid down to 81
Player 1 rolled 2 and is moved to 35and landed on a 'B', and moved backward to 28
Player 2 rolled 4 and is moved to 85and landed on a 'B', and moved backward to 69
Player 1 rolled 2 and is moved to 30 and landed on a chute and slid down to 24
Player 2 rolled 5 and is moved to 74and landed on a 'B', and moved backward to 62
Player 1 rolled 5 and is moved to 29 and landed on a chute and slid down to 27
Player 2 rolled 6 and is moved to 68 and landed on a chute and slid down to 67
Player 1 rolled 2 and is moved to 29
Player 2 rolled 4 and is moved to 71 and landed on a ladder and climbed up to 81
Player 1 rolled 1 and is moved to 30
Player 2 rolled 1 and is moved to 82
Player 1 rolled 1 and is moved to 31 and landed on a ladder and climbed up to 32
Player 2 rolled 1 and is moved to 83
Player 1 rolled 4 and is moved to 36
Player 2 rolled 6 and is moved to 89
Player 1 rolled 2 and is moved to 38
Player 2 rolled 3 and is moved to 92 and landed on a chute and slid down to 86
Player 1 rolled 5 and is moved to 43and landed on a 'B', and moved backward to 22
Player 2 rolled 2 and is moved to 88 and landed on a chute and slid down to 86
Player 1 rolled 1 and is moved to 23
Player 2 rolled 6 and is moved to 92
Player 1 rolled 1 and is moved to 24
Player 2 rolled 6 and is moved to 98
Player 1 rolled 1 and is moved to 25
Player 2 rolled 1 and is moved to 99
Player 1 rolled 6 and is moved to 31
Player 2 rolled 5 and is moved to 104
Player 2 wins!

 *
 */