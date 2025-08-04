#include "tree.h"
#include "apple.h"

int currentBranchIndex = 0;

// Draw a textured cylinder branch
void drawTrunk(float height, float radius) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, barkTexture);

    int slices = 12;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = (float)i / slices * 2.0f * M_PI;
        float x = cos(angle);
        float y = sin(angle);

        // Bottom vertex
        glTexCoord2f((float)i / slices, 0.0f);
        glNormal3f(x, y, 0.0f);
        glVertex3f(x * radius, y * radius, 0.0f);

        // Top vertex
        glTexCoord2f((float)i / slices, 1.0f);
        glNormal3f(x, y, 0.0f);
        glVertex3f(x * radius * 0.8f, y * radius * 0.8f, height);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawLeaves(int branchIndex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leafTexture);
    setColor(1.0f, 1.0f, 1.0f);

    int safeBranchIndex = branchIndex % MAX_BRANCHES;
    int baseIndex = safeBranchIndex * MAX_LEAVES_PER_TWIG;
    int totalLeaves = MAX_BRANCHES * MAX_LEAVES_PER_TWIG;

    for (int i = 0; i < MAX_LEAVES_PER_TWIG; i++) {
        int leafIndex = (baseIndex + i) % totalLeaves;

        float x = leafOffsets[leafIndex * 3 + 0];
        float y = leafOffsets[leafIndex * 3 + 1];
        float z = leafOffsets[leafIndex * 3 + 2];

        float rotZ = leafRotations[leafIndex * 2 + 0];
        float rotX = leafRotations[leafIndex * 2 + 1];

        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(rotZ, 0, 0, 1);
        glRotatef(rotX * 0.5f, 1, 0, 0);

        // Enlarged quad
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, -0.3f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4f, -0.3f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4f, 0.3f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, 0.0f);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawTwig(int branchIndex) {
    setColor(0.8f, 0.8f, 0.8f);
    drawTrunk(0.1f, 0.01f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawLeaves(branchIndex);

    // Add apples with reduced frequency
    if (appleSeeds[branchIndex % MAX_BRANCHES] == 0) {
        glPushMatrix();
        glTranslatef(0.08f, 0.0f, -0.8f);

        glScalef(1.5f, 1.5f, 1.5f);

        drawApple();
        glPopMatrix();
    }

    glPopMatrix();
}

void drawBranch(int depth, float height, float radius) {
    int myBranchIndex = currentBranchIndex++;

    if (depth <= 1) {
        for (int i = 0; i < 6; i++) {
            glPushMatrix();
            float angleVariation = branchAngleSeeds[(myBranchIndex + i) % MAX_BRANCHES];
            glRotatef(i * 60 + angleVariation, 0.0f, 0.0f, 1.0f);
            glRotatef(15 + abs((int)angleVariation) % 20, 1.0f, 0.0f, 0.0f);
            drawTwig(myBranchIndex + i);
            glPopMatrix();
        }
        return;
    }

    setColor(0.8f, 0.8f, 0.8f);
    drawTrunk(height, radius);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);

    for (int i = 0; i < BRANCHES_PER_LEVEL; ++i) {
        glPushMatrix();

        glRotatef(i * (360.0f / BRANCHES_PER_LEVEL), 0.0f, 0.0f, 1.0f);

        float upAngle = BRANCH_ANGLE + (i % 2) * 10.0f;
        glRotatef(upAngle, 1.0f, 0.0f, 0.0f);

        glScalef(SCALE, SCALE, SCALE);
        drawBranch(depth - 1, height * 0.9f, radius * 0.7f);
        glPopMatrix();
    }

    if (depth > 2) {
        for (int i = 0; i < 2; ++i) {
            glPushMatrix();
            glRotatef(i * 180 + 45, 0.0f, 0.0f, 1.0f);
            glRotatef(BRANCH_ANGLE * 0.7f, 1.0f, 0.0f, 0.0f);
            glScalef(SCALE * 0.8f, SCALE * 0.8f, SCALE * 0.8f);
            float taperFactor = 0.6f + 0.15f * ((myBranchIndex % 100) / 100.0f); // varies between 0.6 and 0.75
            drawBranch(depth - 1, height * 0.9f, radius * taperFactor);
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void drawTree() {
    // Reset branch index for consistent numbering each frame
    currentBranchIndex = 0;
    drawBranch(MAX_DEPTH, TRUNK_HEIGHT, 0.15f * TRUNK_SCALE_FACTOR);
}
