#include "message.h"

// Message Configuration
int lineIndex = 0;
const char* line1[] = {
    "Apple dropped. Physics popped.",
    "The apple fell... but why?",
    "With this fall, a law shall rise"
};
const int line1Count = 3;

const char* line2 = "GRAVITY";

// Font Configuration
void* font = GLUT_BITMAP_TIMES_ROMAN_24;
const int fontHeight = 24;
const int lineSpacing = 8;

// Runtime variables
bool showMessage = false;
float messageTimer = 0.0f;
float bubbleScale = 0.5f;

void drawMessage() {
    if (!showMessage) return;

    // Save current state
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glOrtho(0, viewport[2], 0, viewport[3], -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Calculate bubble position and size
    float bubbleWidth = BUBBLE_WIDTH * bubbleScale;
    float bubbleHeight = BUBBLE_HEIGHT * bubbleScale;
    float bubbleX = (viewport[2] - bubbleWidth) / 2;
    float bubbleY = viewport[3] - BUBBLE_Y_OFFSET;

    // Draw main bubble with old parchment color
    glColor4f(0.96f, 0.93f, 0.82f, 0.95f * bubbleScale);
    glBegin(GL_POLYGON);
    glVertex2f(bubbleX + BUBBLE_CORNER_RADIUS, bubbleY + bubbleHeight);
    glVertex2f(bubbleX + bubbleWidth - BUBBLE_CORNER_RADIUS, bubbleY + bubbleHeight);
    glVertex2f(bubbleX + bubbleWidth, bubbleY + bubbleHeight - BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX + bubbleWidth, bubbleY + BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX + bubbleWidth - BUBBLE_CORNER_RADIUS, bubbleY);
    glVertex2f(bubbleX + BUBBLE_CORNER_RADIUS, bubbleY);
    glVertex2f(bubbleX, bubbleY + BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX, bubbleY + bubbleHeight - BUBBLE_CORNER_RADIUS);
    glEnd();

    // Draw antique border
    glLineWidth(BORDER_WIDTH);
    glColor4f(0.5f, 0.4f, 0.3f, 0.8f * bubbleScale);
    glBegin(GL_LINE_LOOP);
    glVertex2f(bubbleX + BUBBLE_CORNER_RADIUS, bubbleY + bubbleHeight);
    glVertex2f(bubbleX + bubbleWidth - BUBBLE_CORNER_RADIUS, bubbleY + bubbleHeight);
    glVertex2f(bubbleX + bubbleWidth, bubbleY + bubbleHeight - BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX + bubbleWidth, bubbleY + BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX + bubbleWidth - BUBBLE_CORNER_RADIUS, bubbleY);
    glVertex2f(bubbleX + BUBBLE_CORNER_RADIUS, bubbleY);
    glVertex2f(bubbleX, bubbleY + BUBBLE_CORNER_RADIUS);
    glVertex2f(bubbleX, bubbleY + bubbleHeight - BUBBLE_CORNER_RADIUS);
    glEnd();

    // Get current line1 text
    const char* currentLine1 = line1[lineIndex];

    // Calculate text widths
    float line1Width = 0;
    for (const char* c = currentLine1; *c != '\0'; c++) {
        line1Width += glutBitmapWidth(font, *c);
    }

    float line2Width = 0;
    for (const char* c = line2; *c != '\0'; c++) {
        line2Width += glutBitmapWidth(font, *c);
    }

    // Calculate text positions - center both lines
    float line1X = bubbleX + (bubbleWidth - line1Width) / 2;
    float line2X = bubbleX + (bubbleWidth - line2Width) / 2;

    // Vertical centering for two lines
    float centerY = bubbleY + bubbleHeight / 2;
    float halfSpacing = lineSpacing / 2;
    float line1Y = centerY + halfSpacing + fontHeight * 0.3f;  // Top line baseline
    float line2Y = centerY - halfSpacing - fontHeight * 0.3f;  // Bottom line baseline

    // Draw line 1 shadow
    glColor4f(0.3f, 0.3f, 0.3f, 0.7f * bubbleScale);
    glRasterPos2f(line1X + 1, line1Y - 1);
    for (const char* c = currentLine1; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }

    // Draw line 1 main text
    glColor4f(0.2f, 0.15f, 0.1f, bubbleScale);
    glRasterPos2f(line1X, line1Y);
    for (const char* c = currentLine1; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }

    // Draw line 2 shadow
    glColor4f(0.3f, 0.3f, 0.3f, 0.7f * bubbleScale);
    glRasterPos2f(line2X + 1, line2Y - 1);
    for (const char* c = line2; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }

    // Draw line 2 main text (highlighted)
    glColor4f(0.6f, 0.3f, 0.1f, bubbleScale);
    glRasterPos2f(line2X, line2Y);
    for (const char* c = line2; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }

    // Restore state
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void checkAppleHitGround() {
    if (!showMessage) {
        showMessage = true;
        messageTimer = 0.0f;
        // Cycle to next message
        lineIndex = (lineIndex + 1) % line1Count;
    }
}

void updateMessage(float deltaTime) {
    if (showMessage) {
        messageTimer += deltaTime;

        if (messageTimer < SCALE_IN_DURATION) {
            bubbleScale = (messageTimer / SCALE_IN_DURATION) * MAX_SCALE;
        } else if (messageTimer < SCALE_IN_DURATION + SCALE_BOUNCE_DURATION) {
            bubbleScale = MAX_SCALE - 0.2f * ((messageTimer - SCALE_IN_DURATION) / SCALE_BOUNCE_DURATION);
        } else if (messageTimer < MESSAGE_DURATION - SCALE_OUT_DURATION) {
            bubbleScale = 1.0f;
        } else {
            bubbleScale = 1.0f - pow((messageTimer - (MESSAGE_DURATION - SCALE_OUT_DURATION)) / SCALE_OUT_DURATION, 2);
        }

        if (messageTimer >= MESSAGE_DURATION) {
            showMessage = false;
        }
    }
}
