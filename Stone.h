// File: Stone.h
// Author: Isaac Husaiin
// Date: April 25, 2024
// Purpose: Defines the Stone class which is a specialized form of Wriggler.
// This class inherits from Wriggler and modifies movement and rendering behaviors
// to simulate stone-like characteristics in a graphical environment.

#include "PixelMatrix.h"
#include "Wriggler.h"

/**
 * Class: Stone
 * Inherits: Wriggler
 * Description: Represents a stone object within the game. The Stone class
 * provides specific implementations for Stone's movement and rendering behavior,
 * differentiating it from other Wriggler-derived objects.
 */
class Stone : public Wriggler {
public:
    /**
     * Constructor for the Stone class.
     * Initializes the Stone object at the specified starting position.
     * @param startRow The initial row position of the Stone.
     * @param startCol The initial column position of the Stone.
     */
    Stone(int startRow, int startCol);

    /**
     * Virtual destructor for the Stone class.
     * Ensures proper cleanup of Stone objects, preventing resource leaks.
     */
    ~Stone() override;

    /**
     * Renders the Stone on the game's pixel matrix.
     * This method overrides the render method from the Wriggler base class,
     * providing a specific drawing logic for the stone's appearance.
     * @param pxm Reference to the PixelMatrix where the Stone will be drawn.
     */
    void render(PixelMatrix &pxm) const override;

    /**
     * Defines the movement behavior of the Stone.
     * Overrides the move method from the Wriggler base class to implement
     * specific movement logic that simulates the behavior of a stone moving
     * within the game field.
     */
    void move() override;

};
