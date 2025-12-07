#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTS
#define GRID_HEIGHT 10
#define GRID_WIDTH 10
#define NUM_MINES 15
static const char CHAR_MAP[] = "?12345678!* ";

// FUNCTIONS
int randInt(int min, int max);
void printGrid(int grid[GRID_HEIGHT][GRID_WIDTH], int numAvailableFlags);
void formatGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
int addMines(int grid[GRID_HEIGHT][GRID_WIDTH], int mineCoordinates[NUM_MINES][2]);
void revealBlankTiles(int inputRow, int inputCol, int gameGrid[GRID_HEIGHT][GRID_WIDTH], int playerGrid[GRID_HEIGHT][GRID_WIDTH]);
bool didPlayerWin(int mineCoordinates[NUM_MINES][2], int playerGrid[GRID_HEIGHT][GRID_WIDTH]);

// MAIN
int main(){
    // VARIABLES
    bool running = true;
    int cycleCounter = 0;
    int row;
    bool rowFound;
    int col;
    bool colFound;
    int inputType;
    bool inputFound;
    int numAvailableFlags = NUM_MINES;
    int gameGrid[GRID_HEIGHT][GRID_WIDTH] = {11};
    int playerGrid[GRID_HEIGHT][GRID_WIDTH] = {0};
    int mineCoordinates[NUM_MINES][2];

    // GAME GRID INITIALIZATION
    if (addMines(gameGrid, mineCoordinates) == 1){
        return 1;
    }
    formatGrid(gameGrid);

    // GAME LOOP
    while (running){
        // Kill Switch
        cycleCounter++;
        if (cycleCounter > 100){
            running = false;
        }

        // Checking if player has won
        if (didPlayerWin(mineCoordinates, playerGrid)){
            printf("Congratulations! You win!\n");
            printGrid(gameGrid, numAvailableFlags);
            running = false;
            return 0;
        }

        printGrid(playerGrid, numAvailableFlags);

        // Input Processing
        // Note: scanf truncates any input floats
        rowFound = false;
        while (!rowFound){
            printf("Pick a row: ");
            if (scanf(" %d", &row) != 1){
                printf("Error! Please input a whole number\n");
            }
            else if(row <= 0 || row > GRID_HEIGHT){
                printf("Error! Please input a row from 1-%d\n", GRID_HEIGHT);
            }
            else{rowFound = true;}

            while ((row = getchar()) != '\n' && row != EOF) { }  // Clearing scanf's input buffer
        }
        
        colFound = false;
        while (!colFound){
            printf("Pick a column: ");
            if (scanf(" %d", &col) != 1){
                printf("Error! Please input a whole number\n");
            }
            else if(col <= 0 || col > GRID_HEIGHT){
                printf("Error! Please input a column from 1-%d\n", GRID_HEIGHT);
            }
            else{colFound = true;}

            while ((col = getchar()) != '\n' && col != EOF) { }  // Clearing scanf's input buffer
        }
        
        inputFound = false;
        while (!inputFound){
            printf("Press 1 to flag a mine \nPress 2 to reveal a tile \nPress 3 to remove a flag \nInput:");
            if (scanf(" %d", &inputType) != 1){
                printf("Error! Please input a whole number\n");
            }
            else if(inputType <= 0 || inputType > GRID_HEIGHT){
                printf("Error! Please input a column from 1-3\n", GRID_HEIGHT);
            }
            else{inputFound = true;}

            while ((inputType = getchar()) != '\n' && inputType != EOF) { }  // Clearing scanf's input buffer
        }
        
        // Set 1st col/row to 0th index
        row -= 1;
        col -= 1;

        // Flag a Mine CHARMAP REFERENCE
        if (inputType == 1){
            if (numAvailableFlags > 0){
                playerGrid[row][col] = 9;
                numAvailableFlags -= 1;
            }
            else{
                printf("Error! You're trying to place more flags than there are mines.\n");
            }
        }

        // Revealing a Tile CHARMAP REFERENCE
        else if(inputType == 2){
            // Checking if tile is a mine CHARMAP REFERENCE
            if (gameGrid[row][col] == 10){
                printGrid(gameGrid, numAvailableFlags);
                printf("RIP, you hit a mine! Game Over\n");
                running = false;
            }
            // Checking if a tile is a blank CHARMAP REFERENCE
            else if(gameGrid[row][col] == 11){
                revealBlankTiles(row, col, gameGrid, playerGrid);
            }
            // Checking if a tile is a number 
            else{
                playerGrid[row][col] = gameGrid[row][col];
            }
        }

        // Removing a Flag CHARMAP REFERENCE
        else if(inputType == 3){
            if (playerGrid[row][col] == 9){
                playerGrid[row][col] = 0;
                numAvailableFlags += 1;
            }
            else{
                printf("Error! That tile is not a mine\n");
            }
        }
    }
    return 0;
}

bool didPlayerWin(int mineCoordinates[NUM_MINES][2], int playerGrid[GRID_HEIGHT][GRID_WIDTH]){
    for (int i = 0; i < NUM_MINES; i++){
        // CHARMAP REFERENCE
        if (playerGrid[mineCoordinates[i][0]][mineCoordinates[i][1]] != 9){
            return false;
        }
    }
    return true;
}

void revealBlankTiles(int inputRow, int inputCol, int gameGrid[GRID_HEIGHT][GRID_WIDTH], int playerGrid[GRID_HEIGHT][GRID_WIDTH]){
    // Initializing Variables
    int queueStartIndex = 0;
    int queueEndIndex = 1;
    int queueSize = GRID_HEIGHT * GRID_WIDTH;
    int queueLength = 1;
    int queue[queueSize][2];
    queue[0][0] = inputRow;
    queue[0][1] = inputCol;
    
    while (queueLength > 0){
        // Revealing the first tile in Queue
        int row = queue[queueStartIndex][0];
        int col = queue[queueStartIndex][1];

        // checking if the tile is unrevealed and not a mine; CHARMAP REFERENCE
        if (playerGrid[row][col] == 0 && gameGrid[row][col] != 10){
            playerGrid[row][col] = gameGrid[row][col];
            if (gameGrid[row][col] == 11){
                // Top Row
                if (row > 0){
                    // Top Middle
                    queue[queueEndIndex][0] = row - 1;
                    queue[queueEndIndex][1] = col;
                    queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                    queueLength++;

                    // Top Left
                    if (col > 0){
                        queue[queueEndIndex][0] = row - 1;
                        queue[queueEndIndex][1] = col - 1;
                        queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                        queueLength++;
                    }

                    // Top Right
                    if (col < GRID_WIDTH - 1){
                        queue[queueEndIndex][0] = row - 1;
                        queue[queueEndIndex][1] = col + 1;
                        queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                        queueLength++;
                    }
                }

                // Middle Left
                if (col > 0){
                    queue[queueEndIndex][0] = row;
                    queue[queueEndIndex][1] = col - 1;
                    queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                    queueLength++;
                }

                // Middle Right
                if (col < GRID_WIDTH - 1){
                    queue[queueEndIndex][0] = row;
                    queue[queueEndIndex][1] = col + 1;
                    queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                    queueLength++;
                }

                // Bottom Row
                if (row < GRID_HEIGHT - 1){
                    // Bottom Middle
                    queue[queueEndIndex][0] = row + 1;
                    queue[queueEndIndex][1] = col;
                    queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                    queueLength++;

                    // Bottom Left
                    if (col > 0){
                        queue[queueEndIndex][0] = row + 1;
                        queue[queueEndIndex][1] = col - 1;
                        queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                        queueLength++;
                    }

                    // Bottom Right
                    if (col < GRID_WIDTH - 1){
                        queue[queueEndIndex][0] = row + 1;
                        queue[queueEndIndex][1] = col + 1;
                        queueEndIndex = (queueEndIndex > queueSize) ? 0 : queueEndIndex + 1;
                        queueLength++;
                    }
                }
            }   
        }
        // Moving to the next index of the queue
        queueStartIndex = (queueStartIndex > queueSize) ? 0 : queueStartIndex + 1;
        queueLength -= 1;
    } 
}

int addMines(int grid[GRID_HEIGHT][GRID_WIDTH], int mineCoordinates[NUM_MINES][2]){
    // ERROR HANDLING
    if (NUM_MINES > GRID_WIDTH * GRID_HEIGHT){
        printf("Error! number of mines greater than the number of tiles");
        return 1;
    }
    // Adding Mines
    for (int mineIndex=0; mineIndex < NUM_MINES; mineIndex++){
        bool mine_found = false;
        while (!mine_found){
            int row = randInt(0, GRID_HEIGHT - 1);
            int col = randInt(0, GRID_WIDTH - 1);
            //  CHARMAP REFERENCE
            if (grid[row][col] != 10){
                grid[row][col] = 10;
                mineCoordinates[mineIndex][0] = row;
                mineCoordinates[mineIndex][1] = col;
                mine_found = true;
            }
        }
    }
}

void formatGrid(int grid[GRID_HEIGHT][GRID_WIDTH]){
    // Calculating Cell Values
    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            // Checking if the Cell is a mine CHARMAP REFERENCE
            if (grid[row][col] != 10){
                int counter = 0;
                // Top Row CHARMAP REFERENCE
                if (row > 0){
                    if (grid[row - 1][col] == 10) {counter++;} // Top Cell
                    if (col > 0) {if (grid[row - 1][col - 1] == 10) {counter++;}} // Top Left
                    if (col < GRID_WIDTH - 1) {if (grid[row - 1][col + 1] == 10) {counter++;}} // Top Right
                }  
                
                // Middle Row CHARMAP REFERENCE
                if (col > 0) {if (grid[row][col - 1] == 10) {counter++;}} // Middle Left
                if (col < GRID_WIDTH - 1) {if (grid[row][col + 1]){counter++;}} // Middle Right
                
                // Bottom Row CHARMAP REFERENCE
                if (row < GRID_HEIGHT - 1){
                    if (grid[row + 1][col] == 10) {counter++;} // Bottom Cell
                    if (col > 0) {if (grid[row + 1][col - 1] == 10) {counter++;}} // Bottom Left
                    if (col < GRID_WIDTH - 1) {if (grid[row + 1][col + 1] == 10) {counter++;}} // Bottom Right
                }
                grid[row][col] = (counter > 0) ? counter : 11;
            }
        }
    }
}

void printGrid(int grid[GRID_HEIGHT][GRID_WIDTH], int numAvailableFlags){
    printf("\n============================================================================\n\n");
    // Available Flags:
    printf("Flags Remaining: %d \n", numAvailableFlags);
    
    // Top Border & Column Coordinates
    printf("    ");
    for (int col=0; col < GRID_WIDTH; col++){
        printf("%3d", col + 1);
    }
    printf("\n    ");
    for (int col=0; col < GRID_WIDTH; col++){
        printf("___");
    }
    printf("\n");

    // Grid
    for (int row=0; row < GRID_HEIGHT; row++){
        printf("%3d|", row + 1);  // Row Coordinates
        for (int col=0; col < GRID_WIDTH; col++){
            printf("%3c", CHAR_MAP[grid[row][col]]);
        }
        printf("\n");
    }
}

int randInt(int min, int max){
    srand(time(NULL) * rand());
    return (rand() % max) + min; 
}
