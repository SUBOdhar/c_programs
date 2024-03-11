#include <stdio.h>

#define ROWS 20
#define COLS 40

char a[ROWS][COLS];
int whiteRow = ROWS / 2;
int whiteCol = COLS / 2;
int blackRow = ROWS / 2;
int blackCol = COLS / 2 + 5;
int i, j;

void printArray(char a[][COLS], int rows, int cols) {
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize array with white spaces
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            a[i][j] = ' ';
        }
    }

    // Place black and white characters
    a[whiteRow][whiteCol] = 'W'; // White
    a[blackRow][blackCol] = 'B'; // Black

    // Main loop for continuous movement
    char direction;
    while (1) {
        // Print initial array
        printf("\033[H\033[J"); // Clear screen
        printArray(a, ROWS, COLS);

        // Move black and white characters
        printf("Enter direction to move (W: up, S: down, A: left, D: right, Q: quit): ");
        scanf(" %c", &direction);

        if (direction == 'Q' || direction == 'q') // Quit if Q is pressed
            break;

        switch (direction) {
            case 'W':
                --whiteRow;
                break;
            case 'S':
                ++whiteRow;
                break;
            case 'A':
                --whiteCol;
                break;
            case 'D':
                ++whiteCol;
                break;
            default:
                printf("Invalid direction!\n");
                continue; // Continue loop if invalid direction is entered
        }

        // Update array with new positions
        a[whiteRow][whiteCol] = 'W'; // White
        a[blackRow][blackCol] = 'B'; // Black
    }

    return 0;
}

