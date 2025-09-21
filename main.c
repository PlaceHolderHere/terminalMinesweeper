#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define INNER_GRID_HEIGHT 10
#define INNER_GRID_WIDTH 10
#define OUTER_GRID_HEIGHT INNER_GRID_HEIGHT + 2 // +2 is for borders
#define OUTER_GRID_WIDTH INNER_GRID_WIDTH + 2 // +2 is for borders

int randInt(int min, int max){
    srand(time(NULL));
    return (rand() % max) + min; 
}

int main(){

    return 0;
}