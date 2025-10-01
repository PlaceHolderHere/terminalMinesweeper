#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTS
#define GRID_HEIGHT 10
#define GRID_WIDTH 10
static const char CHAR_MAP[] = "?";

// FUNCTIONS
int randInt(int min, int max);
void printGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);

// MAIN
int main(){
    int grid[GRID_HEIGHT][GRID_WIDTH] = {0};
    printGrid(grid);

    return 0;
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
