// constants.h - Global configuration constants
#pragma once

// Randomization
constexpr int SEED = 42;  // Fixed seed for deterministic randomness

// Tree Generation Parameters
constexpr int MAX_DEPTH = 5;                // Maximum recursion depth for branches
constexpr float BRANCH_ANGLE = 45.0f;       // Base angle between branches (degrees)
constexpr float SCALE = 0.75f;              // Scaling factor per branch level
constexpr int BRANCHES_PER_LEVEL = 4;       // Branches generated per node
constexpr float TRUNK_HEIGHT = 1.5f;        // Initial trunk height
constexpr float TRUNK_SCALE_FACTOR = 1.7f;  // Trunk scaling relative to branches

// Leaf/Branch Limits
constexpr int MAX_LEAVES_PER_TWIG = 8;      // Maximum leaves per terminal branch
constexpr int MAX_BRANCHES = 1000;          // Maximum branches in an entire tree

// Apple Physics
constexpr float APPLE_Y = 2.5f;             // Initial apple height
constexpr float APPLE_X = 0.7f;             // Initial apple X position
constexpr float APPLE_Z = -1.0f;            // Initial apple Z position
constexpr float GRAVITY = 0.008f;           // Acceleration due to gravity
constexpr float GROUND_LEVEL = 0.08f;       // Y-coordinate where ground begins
constexpr float MAX_VELOCITY = 0.25f;       // Terminal velocity of falling apple
constexpr float APPLE_SCALE = 0.5f;         // Rendering scale for apples

// Environment Dimensions
constexpr float UNDERGROUND_WIDTH = 10.0f;  // Half-width of underground area
constexpr float UNDERGROUND_HEIGHT = 10.0f; // Half-height of underground area
constexpr float UNDERGROUND_DEPTH = 0.2f;   // Depth below ground surface
constexpr float UNDERGROUND_OFFSET = 0.01f; // Vertical offset below ground

// Camera Control
constexpr float MIN_ZOOM = 2.5f;            // Minimum camera zoom distance
constexpr float MAX_ZOOM = 15.0f;           // Maximum camera zoom distance
constexpr float ZOOM_SPEED = 0.5f;          // Zoom adjustment speed
constexpr float ROTATION_SENSITIVITY = 0.5f; // Mouse rotation sensitivity
constexpr float KEY_ROTATION_STEP = 2.5f;   // Keyboard rotation increment
constexpr int FRAME_DELAY = 16;  // ~60 FPS

// Message State
extern bool showMessage;  // Toggles message visibility

// Message Duration
constexpr float MESSAGE_DURATION = 2.0f;

// Bubble Configuration
constexpr float BUBBLE_WIDTH = 350.0f;
constexpr float BUBBLE_HEIGHT = 120.0f;
constexpr float BUBBLE_CORNER_RADIUS = 20.0f;
constexpr float BUBBLE_Y_OFFSET = 300.0f;

// Border
constexpr float BORDER_WIDTH = 2.0f;

// Animation Configuration
constexpr float SCALE_IN_DURATION = 0.3f;
constexpr float SCALE_BOUNCE_DURATION = 0.2f;
constexpr float SCALE_OUT_DURATION = 0.5f;
constexpr float MAX_SCALE = 1.2f;

// Sky dome parameters - sized to nicely surround the ground (radius 10.0f)
constexpr float SKY_RADIUS = 5000.0f;  // 2.5x ground radius for good proportion
constexpr int SKY_SEGMENTS = 64;     // Increased for smoother appearance
constexpr int SKY_RINGS = 32;        // Increased for better vertical resolution
