// tree.h - Procedural tree generation and rendering
#pragma once
#include "imports.h"
#include "TextureLoader.h"
#include "primitives.h"

// Shared Apple Physics State
extern float fallingAppleVelocity;
extern float cameraDistance;
extern float fallingAppleY;
extern float fallingAppleX;
extern float fallingAppleZ;

// Main Rendering Function
void drawTree();  // Generates and renders the entire tree structure