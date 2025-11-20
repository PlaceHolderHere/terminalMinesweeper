# CONSTANTS
    * gameGrid[GRID_HEIGHT][GRID_WIDTH]
        - gameGrid[GRID_HEIGHT][GRID_WIDTH] is a 2D array used to store necessary game data like mines and tile values not yet revealed to the player.
        - when using functions to initialize the grid, all edits should be made to gameGrid()
    * playerGrid[GRID_HEIGHT][GRID_WIDTH]
    * CHARMAP
        - CHARMAP is an array of characters which is used to map tile types to characters for printGrid().
# FUNCTIONS
    * printGrid(grid) 
        - printGrid(grid) takes in playerGrid[GRID_HEIGHT][GRID_WIDTH] as an input and prints it out in the terminal with corresponding borders and coordinate labels.
        - printGrid(grid) refers to CHARMAP for what characters to use for each tile type.

    * int addMines(grid)
        - addMines(grid) takes in gameGrid[GRID_HEIGHT][GRID_WIDTH] as an input and edits the grid directly to have a set number of mines.
        * RETURN VALUES
            - a return value of 0 means that NO problems were encountered.
            - a return value of 1 means that an ERROR has occured .

    * void formatGrid(grid)
        - formatGrid(grid) takes in gameGrid[GRID_HEIGHT][GRID_WIDTH] as an input and edits the grid cells directly to have the appropriate values.

# Error Codes/Return values
    - An Error code is a number that corresponds to a specific error.
    0 - No errors occurred 
    1 - NUM_MINES is set to a value greater than the number of tiles in the grid. 

# CHARMAP
    - When referencing the charmap, a comment should be present to indicate so (e.g. //CHARMAP REFERENCE)
    0 - Non-revealed Tile
    1 - Tile neighbouring 1 mine
    2 - Tile neighbouring 2 mine
    3 - Tile neighbouring 3 mine
    4 - Tile neighbouring 4 mine
    5 - Tile neighbouring 5 mine
    6 - Tile neighbouring 6 mine
    7 - Tile neighbouring 7 mine
    8 - Tile neighbouring 8 mine
    9 - A flagged tile
    10 - A mine