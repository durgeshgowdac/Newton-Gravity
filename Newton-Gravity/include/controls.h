// controls.h - User input handling and view management
#pragma once
#include "imports.h"
#include "constants.h"
#include "apple.h"
#include "message.h"
#include "menu.h"

// View Rotation State
extern float rotationX;  // X-axis rotation angle (degrees)
extern float rotationY;  // Y-axis rotation angle (degrees)
extern float cameraDistance;  // Camera distance from origin

// Input Handlers
void mouse(int button, int state, int x, int y);      // Mouse click handling
void mouseMotion(int x, int y);                      // Mouse drag handling
void keyboard(unsigned char key, int x, int y);      // Keyboard input
void specialKeys(int key, int x, int y);             // Special keys handling

// System Functions
void timer(int value);              // Animation timer callback
void reshape(int w, int h);         // Window resize handler
void initLighting();                // Sets up OpenGL lighting
void drawControlsMenu();            // Control Menu