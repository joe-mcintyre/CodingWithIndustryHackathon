#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

char board[SIZE][SIZE]; // 3x3 board for Tic-Tac-Toe
char currentPlayer = 'X'; // X starts the game

void printBoard();
int checkWinner();
void resetBoard();
int makeMove(int row, int col);
void switchPlayer();

void hello();
void wrong();

int main() {
    char buff[256];
    int row, col;

    // Initialize the board
    resetBoard();

    printf("Welcome to Naughts & Crosses (Tic-Tac-Toe)\n");
    printBoard();

    while (1) {
        printf("Player %c's turn. Enter your move (row and column) or 'exit' to quit: ", currentPlayer);
        fscanf(stdin, "%s", buff);

        // Exit if 'exit' is typed
        if (strcmp(buff, "exit") == 0) {
            break;
        }

        // Parse the row and column from the input
        sscanf(buff, "%d %d", &row, &col);

        // Make the move if valid
        if (makeMove(row, col)) {
            printBoard();
            if (checkWinner()) {
                printf("Player %c wins!\n", currentPlayer);
                resetBoard();  // Reset the board for a new game
                printBoard();
            }
            switchPlayer(); // Switch to the other player
        } else {
            printf("Invalid move! Try again.\n");
        }
    }

    return 0;
}

// Function to print the current board
void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to reset the board
void resetBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

// Function to make a move, returns 1 if successful, 0 otherwise
int makeMove(int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == '-') {
        board[row][col] = currentPlayer;
        return 1;
    }
    return 0;
}

// Function to switch between players
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Function to check if there is a winner
int checkWinner() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return 1;
    }

    return 0;
}

