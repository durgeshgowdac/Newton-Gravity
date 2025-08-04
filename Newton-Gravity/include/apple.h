// apple.h - Apple object and physics simulation
#pragma once
#include "imports.h"
#include "constants.h"
#include "TextureLoader.h"
#include "primitives.h"

// Apple State Tracking
extern bool appleFalling;      // True when apple is in free-fall
extern bool appleOnGround;     // True when apple has landed
extern float fallingAppleY;    // Current vertical position
extern float fallingAppleX;    // Current X position
extern float fallingAppleZ;    // Current Z position
extern float fallingAppleVelocity; // Current downward speed

// Rendering Functions
void drawApple();              // Draws static tree-bound apple
void drawFallingApple();       // Draws apple during fall animation
void updateFallingApple();     // Updates physics for falling apple
void resetApple();             // resets apple to original position
