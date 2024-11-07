/**
 * @file Wiggler.h - A Wiggling Worm!
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 5042, Spring 2024"
 */

#pragma once
#include "Wriggler.h"

/**
 * @class Wiggler - Critter that wiggles around like an inch worm on the screen.
 *
 * Rendered as a 7-pixel green and white body whose midsection oscillates
 * on each movement. There are four body states that are cycled through as
 * time passes.
 */
class Wiggler : public Wriggler {
public:
    Wiggler() : Wriggler() {
        ROW = 10;
        COL = 100;
        state = B;
    }
    void render(PixelMatrix &pxm) const override;
    void move() override;
};

