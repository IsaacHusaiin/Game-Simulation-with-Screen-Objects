// AUTHOR: Isaac Husaiin
// PROGRAM: Poop Class Definition
// DATE: [Current Date]
// PURPOSE: This header file defines the Poop class which inherits from the Wriggler class.
// The Poop class overrides the Wriggler's basic functionalities to exhibit behaviors
// specific to the Poop object within a game environment.

#ifndef POOP_H
#define POOP_H

#include "Wiggler.h"
#include "PixelMatrix.h"

/**
 * Class: Poop
 * Inherits: Wriggler
 * Description: The Poop class represents a playful variation of the Wriggler within the game,
 * designed to simulate a character with unique rendering and movement styles. This class
 * specializes the rendering and moving methods of its parent to reflect its distinct character traits.
 */
class Poop : public Wriggler {
public:
    /**
     * Constructor for the Poop class.
     * Initializes a Poop object at a specified position within the game area.
     * @param startRow Initial row location for the Poop on the game field.
     * @param startCol Initial column location for the Poop on the game field.
     */
    explicit Poop(int startRow = 5, int startCol = 5);

    /**
     * Destructor for the Poop class.
     * Cleans up any resources specific to the Poop, if necessary.
     */
    ~Poop() override;

    /**
     * Overridden render method from Wriggler.
     * Customizes the rendering of the Poop object on a PixelMatrix to visually differentiate
     * it from other Wrigglers.
     * @param pxm Reference to the PixelMatrix where the Poop is to be drawn.
     */
    void render(PixelMatrix &pxm) const override;

    /**
     * Overridden move method from Wriggler.
     * Updates the Poop's position within the game according to a predefined logic,
     * ensuring it moves in a manner befitting its character.
     */
    void move() override;

};

#endif // POOP_H
