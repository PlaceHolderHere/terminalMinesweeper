# CONSTANTS
    * grid
        - grid is a 2d array of size GRID_HEIGHT x GRID_WIDTH and uses numbers to represent certain tile types which is mapped to certain indeces within the CHARMAP
    * CHARMAP
        - CHARMAP is an array of characters which is used to map tile types to characters for printGrid() 
# FUNCTIONS
    * printGrid(grid) 
        - printGrid(grid) takes in a grid[GRID_HEIGHT][GRID_WIDTH] as input and prints it out in the terminal with corresponding borders and coordinate labels
        - printGrid(grid) refers to CHARMAP for what characters to use for each tile type

    * int initGrid(grid)
        - initGrid(grid) takes in a grid[GRID_HEIGHT][GRID_WIDTH] as input and edits the grid directly to have a set number of mines and adjust the surrounding tiles accordingly
        * RETURN VALUES
            - a return value of 0 means that NO problems were encountered
            - a return value of 1 means that an ERROR has occured 