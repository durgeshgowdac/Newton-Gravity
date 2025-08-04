// apple.cpp - Handles apple physics and rendering with bouncing and rolling

#include "apple.h"

// Apple physics state
float fallingAppleVelocity = 0.0f;
bool appleFalling = false;
bool appleOnGround = false;
bool appleRolling = false;

// Apple position
float fallingAppleY = APPLE_Y;
float fallingAppleX = APPLE_X;
float fallingAppleZ = APPLE_Z;

// Bouncing physics
float bounceVelocity = 0.0f;
bool hasBounced = false;
const float BOUNCE_DAMPING = 0.3f;  // Single small bounce

// Rolling physics
float rollVelocity = 0.0f;
float rollAngle = 0.0f;
const float ROLL_FRICTION = 0.96f;  // More friction to limit roll distance
const float MIN_ROLL_VELOCITY = 0.01f;

/**
 * Draws a textured apple using sphere approximation
 */
void drawApple() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, appleTexture);
    setColor(1.0f, 1.0f, 1.0f);
    
    glPushMatrix();
    glScalef(APPLE_SCALE, APPLE_SCALE, APPLE_SCALE);

    const int slices = 10;
    const int stacks = 8;
    const float radius = 0.15f;

    // Create sphere approximation using quad strips
    for (int i = 0; i < stacks; i++) {
        float lat0 = M_PI * (-0.5f + (float)i / stacks);
        float z0 = sin(lat0) * radius;
        float zr0 = cos(lat0) * radius;

        float lat1 = M_PI * (-0.5f + (float)(i + 1) / stacks);
        float z1 = sin(lat1) * radius;
        float zr1 = cos(lat1) * radius;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2 * M_PI * (float)j / slices;
            float x = cos(lng);
            float y = sin(lng);

            glTexCoord2f((float)j / slices, (float)i / stacks);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            glTexCoord2f((float)j / slices, (float)(i + 1) / stacks);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/**
 * Draws the falling apple with rotation effect
 */
void drawFallingApple() {
    glPushMatrix();
    
    // Position the apple
    glTranslatef(fallingAppleX, fallingAppleZ, fallingAppleY);
    
    // Add rotation effect
    if (appleFalling) {
        // Falling rotation
        static float rotationAngle = 0.0f;
        rotationAngle += 2.0f;
        glRotatef(rotationAngle, 1.0f, 1.0f, 0.0f);
    } else if (appleRolling) {
        // Rolling rotation around X-axis
        glRotatef(rollAngle, 1.0f, 0.0f, 0.0f);
    }
    
    drawApple();
    glPopMatrix();
}

/**
 * Updates apple physics (gravity, bouncing, and rolling)
 */
void updateFallingApple() {
    if (appleFalling && !appleOnGround) {
        // Apply gravity
        fallingAppleVelocity += GRAVITY;
        
        // Limit to terminal velocity
        if (fallingAppleVelocity > MAX_VELOCITY) {
            fallingAppleVelocity = MAX_VELOCITY;
        }
        
        // Update position
        fallingAppleY -= fallingAppleVelocity;
        
        // Check ground collision
        if (fallingAppleY <= GROUND_LEVEL) {
            fallingAppleY = GROUND_LEVEL;
            
            // Bounce once if we haven't bounced yet
            if (!hasBounced) {
                bounceVelocity = fallingAppleVelocity * BOUNCE_DAMPING;
                hasBounced = true;
                appleFalling = false;
                
                // Start rolling immediately with the impact energy
                rollVelocity = fallingAppleVelocity * 0.08f;  // Reduced rolling energy
            } else {
                // Already bounced, now settle and roll
                appleOnGround = true;
                appleFalling = false;
                fallingAppleVelocity = 0.0f;
                bounceVelocity = 0.0f;
                appleRolling = true;
            }
        }
    }
    
    // Handle bouncing physics
    if (bounceVelocity > 0.0f && !appleFalling) {
        // Apply gravity to bounce
        bounceVelocity -= GRAVITY;
        
        // Update vertical position
        fallingAppleY += bounceVelocity;
        
        // Check if bounce is going back down
        if (bounceVelocity <= 0.0f) {
            appleFalling = true;
            fallingAppleVelocity = -bounceVelocity; // Convert bounce velocity back to falling velocity
            bounceVelocity = 0.0f;
        }
    }
    
    // Handle rolling physics
    if (appleRolling && appleOnGround) {
        // Apply friction to rolling
        rollVelocity *= ROLL_FRICTION;
        
        // Update horizontal position
        fallingAppleX += rollVelocity;
        
        // Update roll angle based on distance traveled
        rollAngle += (rollVelocity / (0.15f * APPLE_SCALE)) * (180.0f / M_PI);
        
        // Stop rolling when velocity is too low
        if (rollVelocity < MIN_ROLL_VELOCITY) {
            appleRolling = false;
            rollVelocity = 0.0f;
        }
    }
}

/**
 * Resets apple to initial falling state
 */
void resetApple() {
    fallingAppleY = APPLE_Y;
    fallingAppleX = APPLE_X;
    fallingAppleZ = APPLE_Z;
    fallingAppleVelocity = 0.0f;
    appleFalling = true;
    appleOnGround = false;
    appleRolling = false;
    bounceVelocity = 0.0f;
    hasBounced = false;
    rollVelocity = 0.0f;
    rollAngle = 0.0f;
}
