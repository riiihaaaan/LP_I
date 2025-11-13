#include <iostream>
using namespace std;

#define N 8 // You can change this value (4, 5, 6, ...)

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if placing a queen is safe
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check same column above
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queen
bool solveNQueen(int board[N][N], int row) {
    // Base case: all queens are placed
    if (row >= N)
        return true;

    // Try placing this queen in all columns one by one
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // Place the queen
            board[row][col] = 1;

            // Recur to place rest of the queens
            if (solveNQueen(board, row + 1))
                return true;

            // If placing queen here doesn't lead to solution
            // backtrack
            board[row][col] = 0;
        }
    }

    // If queen cannot be placed in any column
    return false;
}

int main() {
    int board[N][N] = {0};

    if (solveNQueen(board, 0))
        printBoard(board);
    else
        cout << "No solution exists!" << endl;

    return 0;
}