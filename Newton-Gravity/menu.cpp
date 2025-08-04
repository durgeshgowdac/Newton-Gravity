#include "menu.h"

// Menu display variables
bool showControlsMenu = true;  // Toggle menu visibility
void* menuFont = GLUT_BITMAP_HELVETICA_12;
const int menuFontHeight = 12;
const int menuLineSpacing = 4;
const int menuPadding = 15;

void drawControlsMenu() {
    if (!showControlsMenu) return;

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

    // Menu content
    const char* menuItems[] = {
        "CONTROLS:",
        "",
        "SPACEBAR - Start/Reset Apple",
        "R - Reset Apple",
        "",
        "WASD - Rotate Camera",
        "Arrow Keys - Rotate Camera",
        "Mouse Drag - Rotate Camera",
        "",
        "+/- - Zoom In/Out",
        "",
        "H - Toggle This Menu",
        "Q / ESC - Quit"
    };
    const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

    // Calculate menu dimensions
    float maxWidth = 0;
    for (int i = 0; i < menuItemCount; i++) {
        float width = 0;
        for (const char* c = menuItems[i]; *c != '\0'; c++) {
            width += glutBitmapWidth(menuFont, *c);
        }
        if (width > maxWidth) maxWidth = width;
    }

    float menuWidth = maxWidth + 2 * menuPadding;
    float menuHeight = menuItemCount * (menuFontHeight + menuLineSpacing) + 2 * menuPadding;

    float menuX = menuPadding;
    float menuY = viewport[3] - menuHeight - menuPadding;

    // Draw menu background
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(menuX, menuY);
    glVertex2f(menuX + menuWidth, menuY);
    glVertex2f(menuX + menuWidth, menuY + menuHeight);
    glVertex2f(menuX, menuY + menuHeight);
    glEnd();

    // Draw menu border
    glColor4f(0.8f, 0.8f, 0.8f, 0.9f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(menuX, menuY);
    glVertex2f(menuX + menuWidth, menuY);
    glVertex2f(menuX + menuWidth, menuY + menuHeight);
    glVertex2f(menuX, menuY + menuHeight);
    glEnd();

    // Draw menu text
    for (int i = 0; i < menuItemCount; i++) {
        float textX = menuX + menuPadding;
        float textY = menuY + menuHeight - menuPadding - (i + 1) * (menuFontHeight + menuLineSpacing);

        // Highlight the title
        if (i == 0) {
            glColor4f(1.0f, 1.0f, 0.0f, 1.0f); // Yellow for title
        } else if (strlen(menuItems[i]) == 0) {
            continue; // Skip empty lines
        } else {
            glColor4f(0.9f, 0.9f, 0.9f, 1.0f); // Light gray for regular text
        }

        glRasterPos2f(textX, textY);
        for (const char* c = menuItems[i]; *c != '\0'; c++) {
            glutBitmapCharacter(menuFont, *c);
        }
    }

    // Restore state
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
