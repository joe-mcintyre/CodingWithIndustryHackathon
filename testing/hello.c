#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char board[9];  // Tic-Tac-Toe board

void initializeBoard();
void displayBoard();
int checkWinner();
void makeMove(int position, char player);
void wrong();
void resetGame();

int main() {
    char buff[256];   // buffer for reading input
    int move;
    
    initializeBoard(); // Set up the board

    int loop = 1;
    while (loop == 1) {
        printf("\nEnter your move (0-8) or 'exit' to quit: ");
        fflush(stdout);  // Ensure prompt is shown before input
        fscanf(stdin, "%s", buff);

        if (strcmp(buff, "exit") == 0) {
            break;
        }

        // Convert input to an integer for the board position
        move = atoi(buff);

        if (move >= 0 && move <= 8 && board[move] == ' ') {
            makeMove(move, 'X'); // Player move
            displayBoard();

            // Check if the player won
            if (checkWinner() == 1) {
                printf("You win! Exiting!\n");
                loop = 0;
                continue;
            }

            // Let the computer make a move
            for (int i = 0; i < 9; i++) {
                if (board[i] == ' ') {
                    makeMove(i, 'O');
                    break;
                }
            }

            displayBoard();

            // Check if the computer won
            if (checkWinner() == -1) {
                printf("Computer wins! Restarting...\n");
                resetGame(); // Restart if the computer wins
            }

        } else {
            wrong();  // Invalid move
        }

        fflush(stdout); // Flush the output buffer
    }

    return 0;
}

void initializeBoard() {
    // Set up the board with blank spaces
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

void displayBoard() {
    printf("\n %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n-----------\n");
    printf(" %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n-----------\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

int checkWinner() {
    // Check rows, columns, and diagonals for a winner
    int winningPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (board[winningPatterns[i][0]] != ' ' &&
            board[winningPatterns[i][0]] == board[winningPatterns[i][1]] &&
            board[winningPatterns[i][1]] == board[winningPatterns[i][2]]) {
            return (board[winningPatterns[i][0]] == 'X') ? 1 : -1;
        }
    }

    // Check for a tie (no empty spaces)
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return 0;  // No winner yet
        }
    }

    return 0; // Tie or ongoing game
}

void makeMove(int position, char player) {
    board[position] = player;
}

void wrong() {
    printf("Invalid move! Please try again.\n");
}

void resetGame() {
    printf("Restarting the game...\n");
    initializeBoard();
    displayBoard();
}
