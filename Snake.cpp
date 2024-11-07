#include "Snake.h"

/**
 * Constructor for Snake.
 * Initializes a Snake object with a specific start position on the game grid.
 * @param startRow Starting row for the snake.
 * @param startCol Starting column for the snake.
 */
Snake::Snake(int startRow, int startCol) : Wriggler(startRow, startCol) {}

/**
 * Destructor for Snake.
 * Cleans up resources or memory if necessary when a Snake object is destroyed.
 */
Snake::~Snake() {}

/**
 * Renders the Snake object on the provided PixelMatrix.
 * @param pxm Reference to the PixelMatrix where the Snake will be drawn.
 *
 * The snake is rendered as a horizontal line, characterized by a specific color and includes
 * details like eyes and possibly a tongue in future enhancements.
 */
void Snake::render(PixelMatrix &pxm) const {
    const int snakeWidth = 10;  // Width of the snake
    const int snakeHeight = 1;  // Height of the snake (integer for simplicity)
    const RGB PURPLE(0x80, 0x00, 0x80); // Purple color for the snake's body
    const RGB GREEN(0x00, 0xff, 0x00); // Green color for the snake's eyes

    // Draw the snake's body
    for (int y = 0; y < snakeHeight; y++) {
        for (int x = 0; x < snakeWidth; x++) {
            pxm.paint(ROW + y, COL + x, PURPLE);
        }
    }

    // Draw the snake's eyes
    pxm.paint(ROW, COL + 2, GREEN); // Left eye
    pxm.paint(ROW, COL + 7, GREEN); // Right eye
}

/**
 * Updates the position of the Snake object on the game grid based on its current state.
 *
 * This method controls the movement of the Snake, allowing it to navigate right or left depending
 * on its current state, with boundary conditions that wrap around the edges of the game grid.
 */
void Snake::move() {
    switch(state) {
        case A: // Move right
            COL++;  // Increment the column position to move right
            if (COL >= 100) {  // Check for the right boundary
                COL = 0;  // Wrap around to the left side
            }
            break;
        case B: // Move left
            COL--;  // Decrement the column position to move left
            if (COL < 0) {  // Check for the left boundary
                COL = 39;  // Wrap around to the right side
            }
            break;
        case C:
            // Placeholder for additional states
            break;
        case D:
            // Placeholder for additional states
            break;
    }
}
