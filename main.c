#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTS
#define GRID_HEIGHT 10
#define GRID_WIDTH 10
#define NUM_MINES 15
static const char CHAR_MAP[] = "?";

// FUNCTIONS
int randInt(int min, int max);
void printGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
void formatGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
int addMines(int grid[GRID_HEIGHT][GRID_WIDTH]);

// MAIN
int main(){
    // VARIABLES
    int gameGrid[GRID_HEIGHT][GRID_WIDTH] = {0};
    int playerGrid[GRID_HEIGHT][GRID_WIDTH] = {0};

    // GAME GRID INITIALIZATION
    if (addMines(gameGrid) == 1){
        return 1;
    }
    formatGrid(gameGrid);

    // GAME LOOP
    printGrid(playerGrid);

    return 0;
}

int addMines(int grid[GRID_HEIGHT][GRID_WIDTH]){
    // ERROR HANDLING
    if (NUM_MINES > GRID_WIDTH * GRID_HEIGHT){
        printf("Error! number of mines greater than the number of tiles");
        return 1;
    }
    // Adding Mines
    for (int mine=0; mine < NUM_MINES; mine++){
        bool mine_found = false;
        while (!mine_found){
            int row = randInt(0, GRID_HEIGHT - 1);
            int col = randInt(0, GRID_WIDTH - 1);
            if (grid[row][col] != 10){
                grid[row][col] = 10;
                mine_found = true;
            }
        }
    }
}

void formatGrid(int grid[GRID_HEIGHT][GRID_WIDTH]){
    // Calculating Cell Values
    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            // Checking if the Cell is a mine
            if (grid[row][col] != 10){
                int counter = 0;
                // Top Row
                if (row > 0){
                    if (grid[row - 1][col] == 10) {counter++;} // Top Cell
                    if (col > 0) {if (grid[row - 1][col - 1] == 10) {counter++;}} // Top Left
                    if (col < GRID_WIDTH - 1) {if (grid[row - 1][col + 1] == 10) {counter++;}} // Top Right
                }  
                
                // Middle Row
                if (col > 0) {if (grid[row][col - 1] == 10) {counter++;}} // Middle Left
                if (col < GRID_WIDTH - 1) {if (grid[row][col + 1]){counter++;}} // Middle Right
                
                // Bottom Row
                if (row < GRID_HEIGHT - 1){
                    if (grid[row + 1][col] == 10) {counter++;} // Bottom Cell
                    if (col > 0) {if (grid[row + 1][col - 1] == 10) {counter++;}} // Bottom Left
                    if (col < GRID_WIDTH - 1) {if (grid[row + 1][col + 1] == 10) {counter++;}} // Bottom Right
                }
                grid[row][col] = counter;
            }
        }
    }
}

void printGrid(int grid[GRID_HEIGHT][GRID_WIDTH]){
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
