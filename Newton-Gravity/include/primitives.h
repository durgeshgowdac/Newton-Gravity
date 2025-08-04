// primitives.h - Basic 3D primitive rendering utilities
#pragma once
#include "constants.h"

// Color Management
void setColor(float r, float g, float b);  // Sets current OpenGL color

// Geometric Primitives
void drawCube(float size);                 // Draws centered cube with given size
void drawSphere(float radius);             // Draws centered sphere
void drawCylinder(float radius, float height); // Draws Z-axis aligned cylinder

// Randomized Elements Storage
extern float leafOffsets[MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 3];  // Leaf position variations
extern float leafRotations[MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 2]; // Leaf orientation variations
extern int appleSeeds[MAX_BRANCHES];       // Random seeds for apple placement
extern float branchAngleSeeds[MAX_BRANCHES]; // Random branch angle variations

// Initialization
void initRandomValues();  // Pre-computes all random values for consistency
