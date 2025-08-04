#include "environment.h"

#define CIRCLE_SEGMENTS 64  // Number of segments for circular geometry
#define GROUND_RADIUS 10.0f
#define PI 3.14159265359f

void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    setColor(1.0f, 1.0f, 1.0f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Draw circular ground using triangle fan
    glBegin(GL_TRIANGLE_FAN);

    // Center vertex
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(2.5f, 2.5f);  // Center of tiled texture
    glVertex3f(0.0f, 0.0f, 0.0f);

    // Outer vertices in a circle
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++) {
        float angle = 2.0f * PI * i / CIRCLE_SEGMENTS;
        float x = GROUND_RADIUS * cos(angle);
        float y = GROUND_RADIUS * sin(angle);

        // Use world coordinates for texture mapping to avoid seam
        // Scale by texture repeat factor
        float texU = x * 0.25f + 2.5f;  // 0.25 = 5.0 / 20.0 (5 tiles across 20 unit diameter)
        float texV = y * 0.25f + 2.5f;

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(texU, texV);
        glVertex3f(x, y, 0.0f);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// draw the circular underground layer
void drawUnderground() {
    glDisable(GL_TEXTURE_2D);

    // Set brown color for underground
    setColor(0.4f, 0.2f, 0.1f);

    float radius = GROUND_RADIUS;  // Match ground radius
    float topZ = -UNDERGROUND_OFFSET;
    float bottomZ = -UNDERGROUND_OFFSET - UNDERGROUND_DEPTH;

    // Draw top face (circular, just below ground level)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, topZ);  // Center

    for (int i = 0; i <= CIRCLE_SEGMENTS; i++) {
        float angle = 2.0f * PI * i / CIRCLE_SEGMENTS;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, topZ);
    }
    glEnd();

    // Draw bottom face (circular, deeper underground)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, bottomZ);  // Center

    // Reverse winding order for proper normals
    for (int i = CIRCLE_SEGMENTS; i >= 0; i--) {
        float angle = 2.0f * PI * i / CIRCLE_SEGMENTS;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, bottomZ);
    }
    glEnd();

    // Draw cylindrical side walls
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++) {
        float angle = 2.0f * PI * i / CIRCLE_SEGMENTS;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Normal points outward from cylinder
        glNormal3f(cos(angle), sin(angle), 0.0f);

        // Top vertex
        glVertex3f(x, y, topZ);
        // Bottom vertex
        glVertex3f(x, y, bottomZ);
    }
    glEnd();
}


//Simple Sky
 void drawSky() {
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();

     glDisable(GL_DEPTH_TEST);
     glDisable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, skyTexture);

     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
     setColor(1.0f, 1.0f, 1.0f);

     glBegin(GL_QUADS);
     glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
     glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
     glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
     glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
     glEnd();

     glEnable(GL_DEPTH_TEST);
     glDisable(GL_TEXTURE_2D);
     glPopMatrix();
 }

// // Sky dome
// void drawSky() {
//     // Save current states
//     glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
//
//     // Disable depth writing so sky appears behind everything
//     glDepthMask(GL_FALSE);
//     glDisable(GL_LIGHTING);
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, skyTexture);
//
//     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//     setColor(1.0f, 1.0f, 1.0f);
//
//     // Save modelview matrix
//     glMatrixMode(GL_MODELVIEW);
//     glPushMatrix();
//
//     // Start fresh with just the camera view (before the -90 degree rotation)
//     glLoadIdentity();
//     gluLookAt(0.0, 1.5, cameraDistance,  // Same camera position
//               0.0, 0.5, 0.0,             // Same look at point
//               0.0, 1.0, 0.0);            // Same up vector
//
//     // Apply only the mouse rotation, not the -90 degree scene rotation
//     glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
//     glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
//
//     // Remove translation to make sky follow camera
//     GLfloat m[16];
//     glGetFloatv(GL_MODELVIEW_MATRIX, m);
//     m[12] = 0.0f;  // Remove X translation
//     m[13] = 0.0f;  // Remove Y translation
//     m[14] = 0.0f;  // Remove Z translation
//     glLoadMatrixf(m);
//
//     // Draw sky dome as a series of quad strips
//     for (int ring = 0; ring < SKY_RINGS; ring++) {
//         // Calculate vertical angles - extend below horizon to eliminate gap
//         // Range from -45° to +90° (slightly below horizon to zenith)
//         float startAngle = -45.0f * PI / 180.0f;  // Start below horizon
//         float endAngle = PI / 2.0f;               // End at zenith
//         float angleRange = endAngle - startAngle;
//
//         float phi1 = startAngle + (float)ring * angleRange / SKY_RINGS;
//         float phi2 = startAngle + (float)(ring + 1) * angleRange / SKY_RINGS;
//
//         float y1 = SKY_RADIUS * sin(phi1);
//         float y2 = SKY_RADIUS * sin(phi2);
//         float r1 = SKY_RADIUS * cos(phi1);
//         float r2 = SKY_RADIUS * cos(phi2);
//
//         // Texture coordinates - map the extended range to full texture
//         float v1 = (float)ring / SKY_RINGS;
//         float v2 = (float)(ring + 1) / SKY_RINGS;
//
//         glBegin(GL_QUAD_STRIP);
//
//         for (int segment = 0; segment <= SKY_SEGMENTS; segment++) {
//             float theta = 2.0f * PI * segment / SKY_SEGMENTS;
//             float cosTheta = cos(theta);
//             float sinTheta = sin(theta);
//
//             float x1 = r1 * cosTheta;
//             float z1 = r1 * sinTheta;
//             float x2 = r2 * cosTheta;
//             float z2 = r2 * sinTheta;
//
//             // Texture coordinate for horizontal wrapping
//             float u = (float)segment / SKY_SEGMENTS;
//
//             // For sky dome textures, we need to map based on the dome's geometry
//             // Use polar coordinates for proper sky dome texture mapping
//             float u1 = 0.5f + (r1 * cosTheta) / (2.0f * SKY_RADIUS);
//             float v1_polar = 0.5f + (r1 * sinTheta) / (2.0f * SKY_RADIUS);
//             float u2 = 0.5f + (r2 * cosTheta) / (2.0f * SKY_RADIUS);
//             float v2_polar = 0.5f + (r2 * sinTheta) / (2.0f * SKY_RADIUS);
//
//             // First vertex of the strip
//             glTexCoord2f(u1, v1_polar);
//             glVertex3f(x1, y1, z1);
//
//             // Second vertex of the strip
//             glTexCoord2f(u2, v2_polar);
//             glVertex3f(x2, y2, z2);
//         }
//
//         glEnd();
//     }
//
//     // Draw a cap at the zenith (top of dome)
//     glBegin(GL_TRIANGLE_FAN);
//
//     // Center vertex at the top
//     glTexCoord2f(0.5f, 1.0f);
//     glVertex3f(0.0f, SKY_RADIUS, 0.0f);
//
//     // Ring of vertices around the top - use the last ring before zenith
//     float startAngle = -15.0f * PI / 180.0f;
//     float endAngle = PI / 2.0f;
//     float angleRange = endAngle - startAngle;
//     float topRingPhi = startAngle + (float)(SKY_RINGS - 1) * angleRange / SKY_RINGS;
//
//     float topY = SKY_RADIUS * sin(topRingPhi);
//     float topR = SKY_RADIUS * cos(topRingPhi);
//     float topV = (float)(SKY_RINGS - 1) / SKY_RINGS;
//
//     for (int segment = 0; segment <= SKY_SEGMENTS; segment++) {
//         float theta = 2.0f * PI * segment / SKY_SEGMENTS;
//         float x = topR * cos(theta);
//         float z = topR * sin(theta);
//
//         // Use polar coordinates for the zenith cap too
//         float u = 0.5f + (topR * cos(theta)) / (2.0f * SKY_RADIUS);
//         float v_polar = 0.5f + (topR * sin(theta)) / (2.0f * SKY_RADIUS);
//
//         glTexCoord2f(u, v_polar);
//         glVertex3f(x, topY, z);
//     }
//
//     glEnd();
//
//     // Restore states
//     glPopMatrix();
//     glPopAttrib();
// }
