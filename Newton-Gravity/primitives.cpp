#include "imports.h"
#include "constants.h"
#include "primitives.h"

float leafOffsets[MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 3];
float leafRotations[MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 2];
int appleSeeds[MAX_BRANCHES];
float branchAngleSeeds[MAX_BRANCHES];

// Initialize random values once during startup
void initRandomValues() {
    srand(SEED); // Fixed seed for consistency
    
    for (int i = 0; i < MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 3; i++) {
        leafOffsets[i] = (rand() % 20 - 10) * 0.01f;
    }
    
    for (int i = 0; i < MAX_BRANCHES * MAX_LEAVES_PER_TWIG * 2; i++) {
        leafRotations[i] = rand() % 360;
    }
    
    // Pre-generate apple seeds - reduced frequency (1 in 42)
    for (int i = 0; i < MAX_BRANCHES; i++) {
        appleSeeds[i] = rand() % 42;
    }
    
    // Pre-generate branch angle variations
    for (int i = 0; i < MAX_BRANCHES; i++) {
        branchAngleSeeds[i] = rand() % 30 - 15;
    }
}

void setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}

// Draw a cube primitive
void drawCube(float size) {
    float half = size / 2.0f;

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, -half,  half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( half, -half,  half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( half,  half,  half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half,  half,  half);

    // Back face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half,  half, -half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( half,  half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( half, -half, -half);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half,  half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half,  half,  half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half,  half, -half);

    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( half, -half, -half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( half,  half, -half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( half,  half,  half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( half, -half,  half);

    // Top face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half,  half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half,  half,  half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( half,  half,  half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( half,  half, -half);

    // Bottom face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( half, -half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( half, -half,  half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half,  half);

    glEnd();
}

// Draw a sphere primitive
void drawSphere(float radius) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, radius, 32, 32);
    gluDeleteQuadric(quad);
}

// Draw a cylinder primitive
void drawCylinder(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricTexture(quad, GL_TRUE); // Enable texture coords

    // Bottom cap (drawn downward)
    glPushMatrix();
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, radius, 32, 1);
    glPopMatrix();

    // Side surface
    gluCylinder(quad, radius, radius, height, 32, 1);

    // Top cap
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(quad, 0.0f, radius, 32, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}
