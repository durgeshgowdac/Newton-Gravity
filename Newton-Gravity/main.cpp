#include "imports.h"
#include "TextureLoader.h"
#include "environment.h"
#include "tree.h"
#include "apple.h"
#include "newton.h"
#include "message.h"
#include "controls.h"

bool useTexture = true;     // true - to use textures

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSky();

    // Check if apple just hit the ground before updating
    static int wasAppleFalling = 0;
    if (wasAppleFalling && !appleFalling) {
        // Apple just stopped falling - it hit the ground
        checkAppleHitGround();
    }
    wasAppleFalling = appleFalling;

    updateFallingApple();
    updateMessage(0.016f);  // Assuming ~60 FPS (16 ms per frame)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Use dynamic camera distance for zoom
    gluLookAt(0.0, 1.5, cameraDistance,  // Camera position with zoom
              0.0, 0.5, 0.0,             // Look at point
              0.0, 1.0, 0.0);            // Up vector

    // Apply rotation based on mouse drag
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    glRotatef(-90, 1.0f, 0.0f, 0.0f);

    glDisable(GL_LIGHTING);
    drawUnderground();
    drawGround();
    drawNewton();
    glEnable(GL_LIGHTING);

    drawTree();

    // Draw the falling/stationary apple
    drawFallingApple();

    // Draw the message on top of everything
    drawMessage();

    // Draw controls menu LAST to ensure it overlays everything
    drawControlsMenu();

    glutSwapBuffers();

    // Force continuous updates while apple is falling or message is showing
    if (appleFalling || showMessage) {
        glutPostRedisplay();
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    initLighting();
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    initTextures(useTexture);

    initRandomValues();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Newton Gravity Discovery");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(FRAME_DELAY, timer, 0);

    glutMainLoop();
    return 0;
}
