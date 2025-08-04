#include "controls.h"

// Control variables
int lastX, lastY;
bool rotating = false;
float rotationX = 0.0f;  // Pitch (vertical rotation)
float rotationY = 0.0f;  // Yaw (horizontal rotation)

float cameraDistance = 7.0f;  // Initial camera distance

bool useClamp = true;
float minClampX = -10.f;
float maxClampX = 89.0f;

// Helper function to wrap angles to [0, 360]
inline float wrapAngle(float angle) {
    angle = fmod(angle, 360.0f);
    return angle < 0.0f ? angle + 360.0f : angle;
}

// Helper function to wrap angles to [0, 360]
inline float clamp(float value, float minVal, float maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        rotating = (state == GLUT_DOWN);
        if (rotating) {
            lastX = x;
            lastY = y;
        }
    }
}

void mouseMotion(int x, int y) {
    if (rotating) {
        // Calculate mouse movement delta
        int dx = x - lastX;
        int dy = y - lastY;

        // Update rotations with sensitivity applied
        rotationY += dx * ROTATION_SENSITIVITY;
        rotationX += dy * ROTATION_SENSITIVITY;

        // Wrap angles to [0, 360)
        rotationY = wrapAngle(rotationY);

        // Clamp x to 90 degrees
        if (!useClamp) {
            rotationX = wrapAngle(rotationX);
        } else {
            rotationX = clamp(rotationX, minClampX, maxClampX);
        }

        // Store current position for next motion event
        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

void handleAppleReset() {
    resetApple();
    showMessage = false;
    updateMessage(0.5f);
}

void keyboard(unsigned char key, int x, int y) {
    switch(tolower(key)) {
        case ' ':  // Spacebar - toggle apple falling
            if (!appleFalling && !appleOnGround) {
                appleFalling = true;
                fallingAppleVelocity = 0.0f;

            } else {
                handleAppleReset();
            }
            break;

        case 'r':  // Reset apple
            handleAppleReset();
            break;

        case 'h':  // Toggle controls menu
            showControlsMenu = !showControlsMenu;
            break;

        // WASD camera controls
        case 'w':  // Look up
            rotationX += KEY_ROTATION_STEP;
            break;
        case 's':  // Look down
            rotationX -= KEY_ROTATION_STEP;
            break;
        case 'a':  // Look left
            rotationY += KEY_ROTATION_STEP;
            break;
        case 'd':  // Look right
            rotationY -= KEY_ROTATION_STEP;
            break;

        // Zoom controls
        case '+':
        case '=':  // Zoom in
            cameraDistance = std::max(cameraDistance - ZOOM_SPEED, MIN_ZOOM);
            break;
        case '-':
        case '_':  // Zoom out
            cameraDistance = std::min(cameraDistance + ZOOM_SPEED, MAX_ZOOM);
            break;

        // Exit controls
        case 'q':
        case 27:   // ESC key
            exit(0);
            break;
    }

    // Wrap angles after keyboard rotation
    rotationY = wrapAngle(rotationY);
    if (!useClamp) {
        rotationX = wrapAngle(rotationX);
    } else {
        rotationX = clamp(rotationX, minClampX, maxClampX);
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            rotationY += KEY_ROTATION_STEP;
            break;
        case GLUT_KEY_RIGHT:
            rotationY -= KEY_ROTATION_STEP;
            break;
        case GLUT_KEY_UP:
            rotationX += KEY_ROTATION_STEP;
            break;
        case GLUT_KEY_DOWN:
            rotationX -= KEY_ROTATION_STEP;
            break;
    }

    // Wrap angles after a special key rotation
    if (!useClamp) {
        rotationX = wrapAngle(rotationX);
    } else {
        rotationX = clamp(rotationX, minClampX, maxClampX);
    }
    rotationY = wrapAngle(rotationY);

    glutPostRedisplay();
}

void timer(int value) {
    if (appleFalling) {
        glutPostRedisplay();
    }
    glutTimerFunc(FRAME_DELAY, timer, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void initLighting() {
    GLfloat light_position[] = {4.0f, 6.0f, 8.0f, 1.0f};
    GLfloat light_ambient[]  = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat light_diffuse[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat light_specular[] = {0.9f, 0.9f, 0.9f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}