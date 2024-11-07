// AUTHOR: Isaac Husaiin
// PROGRAM: Snake Class Definition
// DATE: April 25th 2024
// PURPOSE: This header file defines the Snake class, which inherits from the Wriggler class.
// The Snake class overrides the Wriggler's movement and rendering behaviors to represent
// snake-like behavior within the game environment.

#pragma once

#include "Wriggler.h"
#include "PixelMatrix.h"

/**
 * Class: Snake
 * Inherits: Wriggler
 * Description: The Snake class represents a snake-like object in a graphical application,
 * extending the Wriggler class. It modifies both the movement and rendering behaviors to
 * accommodate the specific attributes and interactions of a snake within the game.
 */
class Snake : public Wriggler {
public:
    /**
     * Constructor for the Snake class.
     * Initializes a Snake object at a specified position on the game grid.
     * @param startRow Initial row location for the Snake in the game area.
     * @param startCol Initial column location for the Snake in the game area.
     */
    explicit Snake(int startRow = 5, int startCol = 5);

    /**
     * Destructor for the Snake class.
     * Responsible for cleaning up resources used by the Snake, if any.
     */
    ~Snake() override;

    /**
     * Overridden render method from Wriggler.
     * Handles the graphical rendering of the Snake object on a PixelMatrix, drawing it
     * according to snake-specific visual characteristics.
     * @param pxm Reference to the PixelMatrix where the Snake is to be drawn.
     */
    void render(PixelMatrix &pxm) const override;

    /**
     * Overridden move method from Wriggler.
     * Implements the specific movement logic for the Snake, allowing it to navigate
     * the game environment in a snake-like manner.
     */
    void move() override;


};
