
#include "Poop.h"

/**
 * Constructor for Poop.
 * Initializes a Poop object with a specific start position on the game grid.
 * @param startRow Starting row for the Poop.
 * @param startCol Starting column for the Poop.
 */
Poop::Poop(int startRow, int startCol) : Wriggler(startRow, startCol) {

}

/**
 * Destructor for Poop.
 * Cleans up resources or memory if necessary when a Poop object is destroyed.
 */
Poop::~Poop() {

}



/**
 * Renders the Poop object on the PixelMatrix with a stylized appearance.
 * @param pxm Reference to the PixelMatrix where the Poop will be drawn.
 *
 * This method draws the Poop as a swirl shape using dark salmon color,
 * providing a playful design. The shape is defined within a 4x5 grid.
 */
void Poop::render(PixelMatrix &pxm) const {
    const int poopWidth = 5;  // Width of the poop shape
    const int poopHeight = 4; // Increased height for better shape definition
    const RGB DARK_SALMON(0xE9, 0x96, 0x7A); // Dark Salmon color, visually appealing for a playful design

    // Define a more realistic poop shape, reminiscent of a swirl
    int shape[4][5] = {
            {0, 0, 1, 0, 0},  // Tip of the swirl
            {0, 1, 1, 1, 0},  // Upper part of the swirl
            {1, 1, 1, 1, 1},  // Middle body of the swirl
            {0, 1, 1, 1, 0}   // Base of the swirl, slightly narrower
    };

    // Draw the poop shape using the new color
    for (int y = 0; y < poopHeight; y++) {
        for (int x = 0; x < poopWidth; x++) {
            if (shape[y][x] == 1) {  // Only paint parts of the grid defined by the shape array
                pxm.paint(ROW + y, COL + x, DARK_SALMON);
            }
        }
    }
}




/**
 * Moves the Poop object based on its current state.
 *
 * This method determines the direction of movement based on the current state
 * and updates the position accordingly, considering wrap-around at grid edges.
 */
void Poop::move() {
    switch(state) {
        case A: // Move right
            COL++;
            break;
        case B: // Move down
            ROW++;
            if (ROW >= 40) {
                ROW = 0;  // Wrap to the top if it moves past the bottom boundary
            }
            state = B;
            break;
        case C: // Move left
            COL--;
            if (COL < 0) {
                COL = 39;  // Wrap to the other side of the screen if it moves past the left boundary
            }
            break;
        case D: // Move up
            ROW--;
            if (ROW < 0) {
                ROW = 39;  // Wrap to the bottom if it moves past the top boundary
            }
            break;
    }
}

