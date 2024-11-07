/**
 * @file Wriggler.cpp - A Wriggling Worm!
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 5042, Spring 2024"
 */

#include "Wriggler.h"

/**
 * Renders the Wriggler on the PixelMatrix as an apple with a leaf.
 * @param pxm Reference to PixelMatrix where the Wriggler will be drawn.
 *
 * This method draws a stylized apple using red and green pixels to represent the body
 * and leaf of an apple respectively. The shape is defined within a 7x7 grid.
 */
void Wriggler::render(PixelMatrix &pxm) const {
    const int appleWidth = 7;  // Width of the apple.
    const int appleHeight = 7; // Height of the apple.
    const RGB RED(0xff, 0x00, 0x00); // Red color for the apple.
    const RGB GREEN(0x00, 0xff, 0x00); // Green color for the leaf.

    // Draw the apple shape.
    for (int y = 0; y < appleHeight; y++) {
        for (int x = 0; x < appleWidth; x++) {
            // Draw the apple's body.
            if ((y >= 1 && y <= 5 && x >= 2 && x <= 4) ||
                (y >= 2 && y <= 4 && x >= 1 && x <= 5) ||
                (y == 3 && (x == 0 || x == 6))) {
                pxm.paint(ROW + y, COL + x, RED);
            }
            // Draw the leaf.
            if ((y == 0 && x == 3) || (y == 1 && (x == 2 || x == 3 || x == 4))) {
                pxm.paint(ROW + y, COL + x, GREEN);
            }
        }
    }
}

/**
 * Updates the position of the Wriggler based on its current state.
 *
 * This method controls the movement of the Wriggler, allowing it to navigate
 * right, down, left, or up depending on its current state. Transitions between
 * states dictate the next direction of movement.
 */
void Wriggler::move() {
    switch(state) {
        case A: // Move right.
            COL++;
            break;
        case B: // Move down.
            ROW--;
            if (ROW < 0) {
                ROW = 40;
            };
            state = B;
            break;
        case C: // Move left.
            ROW--;
            state = D;
            break;
        case D: // Move up.
            ROW--;
            state = A;
            break;
    }
}
