/**
 * @file Wiggler.cpp - Implementation of the Wiggler class
 * @author Kevin Lundee
 * @see "Seattle University, CPSC 5042, Spring 2024"
 */

#include "Wiggler.h"

/**
 * Renders the Wiggler on the PixelMatrix with a stylized appearance.
 * @param pxm Reference to the PixelMatrix where the Wiggler will be drawn.
 *
 * This method draws the Wiggler as a monster with eyes and teeth using
 * green and red pixels respectively. The shape is defined within an 11x11 grid.
 */
void Wiggler::render(PixelMatrix &pxm) const {
    const int width = 11;  // Width of the monster.
    const int height = 11; // Height of the monster.
    const RGB GREEN(0x00, 0xff, 0x00); // Green color for the monster's body.
    const RGB RED(0xff, 0x00, 0x00); // Red color for the monster's eyes and teeth.

    // Draw the monster's body, eyes, and teeth.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Draw the body, excluding the area for the mouth.
            if (!(x >= 2 && x <= 6 && y >= 5 && y <= 9)) {
                pxm.paint(ROW + y, COL + x, GREEN);
            }
            // Draw the eyes.
            if ((x == 2 && y == 2) || (x == 8 && y == 2)) {
                pxm.paint(ROW + y, COL + x, RED);
            }
            // Draw the teeth.
            if ((x >= 3 && x <= 5 && y == 7) || (x >= 6 && x <= 8 && y == 7)) {
                pxm.paint(ROW + y, COL + x, RED);
            }
        }
    }
}

/**
 * virtically moves the Stone monster object on the game grid.
 *.
 */
void Wiggler::move() {
    // Increment the row position to move the wiggler down.
    ROW++;
    // If the wiggler reaches the bottom of the screen, wrap around to the top.
    if (ROW >= 40) {
        ROW = 0;
    }
}
