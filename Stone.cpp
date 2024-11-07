#include "Stone.h"
#include <ctime>
#include <cstdlib>

/**
 * Constructor for Stone.
 * Initializes a Stone object with a specific start position on the game grid.
 * @param startRow Starting row for the stone.
 * @param startCol Starting column for the stone.
 */
Stone::Stone(int startRow, int startCol) : Wriggler(startRow, startCol) {};

/**
 * Destructor for Stone.
 * Cleans up resources or memory if necessary when a Stone object is destroyed.
 */
Stone::~Stone() {}

/**
 * Renders the Stone object on the provided PixelMatrix.
 * @param pxm Reference to the PixelMatrix where the Stone will be drawn.
 *
 * The Stone is depicted as a rectangle with a distinctive point on the top, drawn in a deep blue color.
 * The shape of the stone is defined in a 3x5 grid.
 */
void Stone::render(PixelMatrix &pxm) const {
    const int stoneWidth = 5;  // Maintain the width for the square shape
    const int stoneHeight = 3; // Maintain the height
    const RGB BLUE(0x00, 0x00, 0x8B); // Deep blue color for the stone

    // Redefine the stone shape to be a square with a pointy dot on the top
    int shape[3][5] = {
            {0, 0, 1, 0, 0},  // Single pointy dot in the center of the top row
            {1, 1, 1, 1, 1},  // Full middle row for the main body of the square
            {1, 1, 1, 1, 1}   // Full bottom row for the base of the square
    };

    // Draw the stone shape on the PixelMatrix
    for (int y = 0; y < stoneHeight; y++) {
        for (int x = 0; x < stoneWidth; x++) {
            if (shape[y][x] == 1) {  // Only paint parts of the grid defined by the shape array
                pxm.paint(ROW + y, COL + x, BLUE);
            }
        }
    }
}

/**
 * Randomly moves the Stone object on the game grid.
 *
 * This method uses a random number generator to decide on a movement direction and then
 * applies that movement to the Stone's position, considering wrap-around at grid edges.
 */
void Stone::move() {
    srand(time(nullptr));  // Seed the random number generator
    int moveChance = rand() % 2;  // Decide if the stone moves this cycle

    if (moveChance < 3) {  // Always true as moveChance is 0 or 1
        int direction = rand() % 8;  // Randomly choose a direction

        switch(direction) {
            case 0: // Move right
                COL++;
                if (COL >= 40) {
                    COL = 0;  // Wrap around to the left edge
                }
                break;
            case 1: // Move down
                ROW++;
                if (ROW >= 40) {
                    ROW = 0;  // Wrap around to the top edge
                }
                break;
            case 2: // Move left
                COL--;
                if (COL < 0) {
                    COL = 39;  // Wrap around to the right edge
                }
                break;
            case 3: // Move up
                ROW--;
                if (ROW < 0) {
                    ROW = 39;  // Wrap around to the bottom edge
                }
                break;
            case 4: // Move diagonally top-right
                COL++;
                ROW--;
                if (COL >= 40) COL = 0;
                if (ROW < 0) ROW = 39;
                break;
            case 5: // Move diagonally bottom-right
                COL++;
                ROW++;
                if (COL >= 40) COL = 0;
                if (ROW >= 40) ROW = 0;
                break;
            case 6: // Move diagonally bottom-left
                COL--;
                ROW++;
                if (COL < 0) COL = 39;
                if (ROW >= 40) ROW = 0;
                break;
            case 7: // Move diagonally top-left
                COL--;
                ROW--;
                if (COL < 0) COL = 39;
                if (ROW < 0) ROW = 39;
                break;
        }
    }
}
