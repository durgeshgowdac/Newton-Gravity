//#include "newton.h"
//
//// Function prototypes
//void drawHead();      // Draws Newton's head with facial features and wig
//void drawTorso();     // Draws torso with coat, vest, and accessories
//void drawArms();      // Draws arms and hands, including the book being held
//void drawLegs();      // Draws legs and shoes
//void drawBook();      // Draws the book Newton is reading
//
//// Global transformation variables for Newton figure
//float newtonScale = 0.5f;           // Uniform scaling factor for an entire figure
//float newtonPosX = 0.0f;            // X-axis position in world space
//float newtonPosY = -0.5f;           // Y-axis position (vertical)
//float newtonPosZ = 0.35f;            // Z-axis position (depth)
//float newtonRotX = 90.0f;            // Rotation angle around X-axis (for posing)
//
//// Draws Newton's head with all facial features and wig
//void drawHead() {
//    // Head positioning and dimensions
//    float headY = 1.4f;             // Vertical position relative to torso
//    float headRadius = 0.35f;        // Base size of head sphere
//    float eyeRadius = 0.035f;        // Size of eyes
//    float eyeSpacing = 0.12f;        // Distance between eyes
//    float eyeForwardZ = 0.31f;       // How far the eyes protrude - forward
//    float eyeUpY = 0.08f;            // Vertical position of eyes on face
//    float noseRadius = 0.06f;        // Size of nose sphere
//    float noseForwardZ = 0.31f;      // How far the nose protrudes
//    float noseDownY = -0.05f;        // Vertical position of nose
//    
//    // Wig dimensions
//    float wigCapY = 0.25f;           // Vertical position of wig base
//    float wigCapZ = -0.2f;           // Depth position of wig base
//    float wigCapRadius = 0.4f;       // Size of main wig mass
//    float curlRadius = 0.1f;         // Size of individual curls
//    float curlSpacing = 0.15f;       // Vertical spacing between curls
//    float sideX = 0.45f;             // Horizontal position of side curls
//    float backZ = -0.35f;            // Depth position of back curls
//    
//    // Color values (RGB)
//    float skinR = 0.9f, skinG = 0.8f, skinB = 0.7f;  // Skin tone
//    float eyeR = 0.1f, eyeG = 0.1f, eyeB = 0.1f;     // Eye color (black)
//    float noseR = 0.85f, noseG = 0.75f, noseB = 0.65f; // Nose color
//    float wigR = 0.85f, wigG = 0.85f, wigB = 0.85f;  // Wig color (gray-white)
//
//    // Begin head group
//    glPushMatrix();
//    glTranslatef(0.0f, headY, 0.0f);  // Position head relative to body
//
//    // Head (base sphere)
//    setColor(skinR, skinG, skinB);
//    drawSphere(headRadius);
//
//    // Eyes (two spheres)
//    glPushMatrix();
//        setColor(eyeR, eyeG, eyeB);
//        glTranslatef(-eyeSpacing, eyeUpY, eyeForwardZ);    // Left eye position
//        drawSphere(eyeRadius);
//        glTranslatef(eyeSpacing * 2, 0.0f, 0.0f);         // Right eye position
//        drawSphere(eyeRadius);
//    glPopMatrix();
//
//    // Nose (scaled sphere)
//    glPushMatrix();
//        setColor(noseR, noseG, noseB);
//        glTranslatef(0.0f, noseDownY, noseForwardZ);
//        glScalef(1.0f, 0.5f, 1.3f);  // Flatten vertically, elongate forward
//        drawSphere(noseRadius);
//    glPopMatrix();
//
//    // Wig cap (main mass of hair)
//    glPushMatrix();
//        setColor(wigR, wigG, wigB);
//        glTranslatef(0.0f, wigCapY, wigCapZ);
//        glScalef(1.6f, 1.0f, 1.2f);    // Widen and deepen wig shape
//        drawSphere(wigCapRadius);
//    glPopMatrix();
//
//    // Side curls - left (three spheres)
//    for (int i = 0; i < 3; i++) {
//        glPushMatrix();
//            glTranslatef(-sideX, -0.05f - i * curlSpacing, 0.0f);
//            drawSphere(curlRadius);
//        glPopMatrix();
//    }
//
//    // Side curls - right (three spheres)
//    for (int i = 0; i < 3; i++) {
//        glPushMatrix();
//            glTranslatef(sideX, -0.05f - i * curlSpacing, 0.0f);
//            drawSphere(curlRadius);
//        glPopMatrix();
//    }
//
//    // Back curls (three spheres)
//    for (int i = 0; i < 3; i++) {
//        glPushMatrix();
//            glTranslatef(0.0f, -0.1f - i * curlSpacing, backZ);
//            drawSphere(curlRadius);
//        glPopMatrix();
//    }
//
//    glPopMatrix();  // End head group
//}
//
//// Draws Newton's torso with coat, collar, vest and buttons
//void drawTorso() {
//    // Torso dimensions
//    float torsoRadius = 0.35f;       // Base radius of torso cylinder
//    float torsoHeight = 0.8f;        // Height of torso
//    float collarY = 0.9f;            // Vertical position of collar
//    float collarRadius = 0.22f;      // Collar size
//    float collarHeight = 0.20f;      // Collar thickness
//    float cravatY = 1.02f;           // Vertical position of necktie
//    float cravatZ = 0.2f;            // Depth position of necktie
//    float cravatSize = 0.5f;         // Size of necktie cube
//    float vestY = 0.5f;              // Vertical position of vest
//    float vestZ = 0.2f;              // Depth position of vest
//    float vestSize = 0.75f;          // Size of vest cube
//    float buttonSpacing = 0.12f;      // Space between buttons
//    float buttonRadius = 0.025f;      // Button size
//    float buttonZ = 0.25f;           // Depth position of buttons
//    
//    // Color values (RGB)
//    float coatR = 0.2f, coatG = 0.1f, coatB = 0.4f;      // Dark purple coat
//    float collarR = 0.15f, collarG = 0.05f, collarB = 0.35f; // Darker collar
//    float cravatR = 0.9f, cravatG = 0.9f, cravatB = 0.8f; // White necktie
//    float vestR = 0.6f, vestG = 0.5f, vestB = 0.3f;      // Brown vest
//    float buttonR = 0.8f, buttonG = 0.7f, buttonB = 0.4f; // Gold buttons
//
//    // Torso base (coat cylinder)
//    glPushMatrix();
//        setColor(coatR, coatG, coatB);
//        glTranslatef(0.0f, 0.0f, 0.0f);
//        glScalef(1.0f, 1.2f, 0.7f);      // Stretch vertically, compress depth
//        glRotatef(-90, 1, 0, 0);         // Orient cylinder vertically
//        drawCylinder(torsoRadius, torsoHeight);
//    glPopMatrix();
//    
//    // Collar (smaller cylinder)
//    glPushMatrix();
//        setColor(collarR, collarG, collarB);
//        glTranslatef(0.0f, collarY, 0.0f);
//        glRotatef(-90, 1, 0, 0);         // Orient vertically
//        drawCylinder(collarRadius, collarHeight);
//    glPopMatrix();
//
//    // Cravat (neck tie - thin rectangle)
//    glPushMatrix();
//        setColor(cravatR, cravatG, cravatB);
//        glTranslatef(0.0f, cravatY, cravatZ);
//        glScalef(0.25f, 0.4f, 0.15f);    // Scale - to thin rectangular shape
//        drawCube(cravatSize);
//    glPopMatrix();
//
//    // Vest (scaled cube)
//    glPushMatrix();
//        setColor(vestR, vestG, vestB);
//        glTranslatef(0.0f, vestY, vestZ);
//        glScalef(0.6f, 1.0f, 0.18f);     // Narrow and thin vest shape
//        drawCube(vestSize);
//    glPopMatrix();
//
//    // Buttons (spheres in a column)
//    int buttonCount = 6;                  // Total number of buttons
//    float topButtonY = 0.8f;              // Topmost button position
//    for (int i = 0; i < buttonCount; i++) {
//        glPushMatrix();
//            setColor(buttonR, buttonG, buttonB);
//            glTranslatef(0.0f, topButtonY - i * buttonSpacing, buttonZ);
//            drawSphere(buttonRadius);
//        glPopMatrix();
//    }
//}
//
//// Draws the book Newton is holding
//void drawBook() {
//    // Book dimensions
//    float pageWidth = 0.45f;          // Width of open book spread
//    float pageHeight = 0.6f;          // Height of pages
//    float pageDepth = 0.01f;          // Thickness of pages
//    float bindingWidth = 0.05f;        // Spine width
//    float bindingHeight = 0.62f;       // Spine height
//    
//    // Color values (RGB)
//    float pageR = 0.95f, pageG = 0.95f, pageB = 0.9f;  // Off-white pages
//    float bindingR = 0.4f, bindingG = 0.15f, bindingB = 0.05f; // Brown binding
//    float textR = 0.1f, textG = 0.1f, textB = 0.1f;    // Black text
//
//    // Central spine (book binding)
//    glPushMatrix();
//        setColor(bindingR, bindingG, bindingB);
//        glScalef(bindingWidth, bindingHeight, pageDepth * 3); // Thicker spine
//        drawCube(1.0f);
//    glPopMatrix();
//
//    // Common Z-offset for covers and pages
//    float coverZ = pageDepth * 0.4f;
//
//    // Page block (static inner pages)
//    glPushMatrix();
//        setColor(pageR, pageG, pageB);
//        glTranslatef(0.0f, 0.0f, coverZ - pageDepth * 0.5f); // Slightly under covers
//        glScalef(pageWidth * 2, pageHeight, pageDepth * 1.5f); // Full page block
//        drawCube(1.0f);
//    glPopMatrix();
//
//    // Text lines (simulated with thin rectangles)
//    for (int i = 0; i < 8; i++) {  // 8 lines of text per page
//        float yOffset = (pageHeight * 0.3f) - (i * 0.06f); // Vertical position
//        float jitter = (i % 2 == 0) ? 0.005f : -0.005f;   // Alternating offset
//
//        // Left page text line
//        glPushMatrix();
//            glTranslatef(-bindingWidth * 0.5f, 0.0f, pageDepth * 2.5f);
//            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
//            glTranslatef(-pageWidth, yOffset + jitter, 0.0f);
//            glTranslatef(pageWidth * 0.5f, 0.0f, 0.0f);
//            setColor(textR, textG, textB);
//            glScalef(pageWidth * 0.8f, 0.01f, pageDepth); // Thin rectangle
//            drawCube(1.0f);
//        glPopMatrix();
//
//        // Right page text line
//        glPushMatrix();
//            glTranslatef(bindingWidth * 0.5f, 0.0f, pageDepth * 2.5f);
//            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
//            glTranslatef(pageWidth, yOffset + jitter, 0.0f);
//            glTranslatef(-pageWidth * 0.5f, 0.0f, 0.0f);
//            setColor(textR, textG, textB);
//            glScalef(pageWidth * 0.8f, 0.01f, pageDepth); // Thin rectangle
//            drawCube(1.0f);
//        glPopMatrix();
//    }
//}
//
//// Draws Newton's arms and hands, including the book
//void drawArms() {
//    // Arm dimensions
//    float armLength = 0.75f;         // Length from shoulder to hand
//    float armOffsetX = 0.4f;         // Horizontal offset from the center
//    float shoulderY = 0.6f;          // Vertical shoulder position
//    float shoulderZ = 0.4f;          // Depth shoulder position
//    float handRadius = 0.12f;        // Size of hands
//    float armThickness = 0.18f;      // Width of arms
//    
//    // Color values (RGB)
//    float coatR = 0.2f, coatG = 0.1f, coatB = 0.4f;  // Matches coat color
//    float skinR = 0.9f, skinG = 0.8f, skinB = 0.7f;  // Matches head skin tone
//
//    // Left arm (cube stretched into arm shape)
//    glPushMatrix();
//        setColor(coatR, coatG, coatB);
//        glTranslatef(-armOffsetX, shoulderY, shoulderZ);  // Shoulder position
//        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            // Rotate forward
//        glScalef(armThickness, armLength, armThickness);  // Lengthen arm
//        drawCube(1.0f);
//    glPopMatrix();
//
//    // Left hand (sphere at the end of arm)
//    glPushMatrix();
//        setColor(skinR, skinG, skinB);
//        glTranslatef(-armOffsetX, shoulderY, shoulderZ + (armLength * 0.5f));
//        drawSphere(handRadius);
//    glPopMatrix();
//
//    // Right arm (cube stretched into arm shape)
//    glPushMatrix();
//        setColor(coatR, coatG, coatB);
//        glTranslatef(armOffsetX, shoulderY, shoulderZ);   // Shoulder position
//        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            // Rotate forward
//        glScalef(armThickness, armLength, armThickness);  // Lengthen arm
//        drawCube(1.0f);
//    glPopMatrix();
//
//    // Right hand (sphere at the end of arm)
//    glPushMatrix();
//        setColor(skinR, skinG, skinB);
//        glTranslatef(armOffsetX, shoulderY, shoulderZ + (armLength * 0.5f));
//        drawSphere(handRadius);
//    glPopMatrix();
//
//    // Book positioned in hands (angled for reading)
//    glPushMatrix();
//        glTranslatef(0.0f, shoulderY + 0.15f, shoulderZ + (armLength * 0.5f) + 0.15f);
//        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);    // Rotate to face Newton
//        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);    // Tilt for reading angle
//        drawBook();
//    glPopMatrix();
//}
//
//// Draws Newton's legs and shoes
//void drawLegs() {
//    // Leg dimensions
//    float bottomY = -0.70f;          // Base of pants position
//    float bottomHeight = 1.17f;       // Height of pants cylinder
//    float bottomRadius = 0.35f;      // Width of pants
//    float legY = -0.59f;             // Vertical start of legs
//    float legX = 0.3f;               // Horizontal leg spacing
//    float legZ = 0.05f;              // Depth position of legs
//    float legThickness = 0.22f;       // Width of legs
//    float legRadius = 0.4f;           // Used for cylindrical legs
//    float legLength = 1.5f;           // Length parameter for legs
//    float shoeY = -0.46f;             // Vertical shoe position
//    float shoeZ = 1.1f;               // Depth shoe position
//    float shoeSize = 0.8f;            // Base shoe scale
//    
//    // Color values (RGB)
//    float pantsR = 0.1f, pantsG = 0.1f, pantsB = 0.1f;  // Black pants
//    float shoeR = 0.1f, shoeG = 0.05f, shoeB = 0.0f;    // Dark brown shoes
//
//    // Bottom (pant base - scaled cylinder)
//    glPushMatrix();
//        setColor(pantsR, pantsG, pantsB);
//        glTranslatef(0.0f, bottomY, 0.0f);
//        glScalef(1.0f, 0.6f, 0.7f);      // Flatten and compress pants
//        glRotatef(-90, 1.0f, 0.0f, 0.0f); // Orient vertically
//        drawCylinder(bottomRadius, bottomHeight);
//    glPopMatrix();
//    
//    // Left leg (scaled cylinder)
//    glPushMatrix();
//        setColor(pantsR, pantsG, pantsB);
//        glTranslatef(-legX, legY, legZ);  // Left leg position
//        glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
//        glScalef(legThickness, legThickness, 0.7f);  // Make cylindrical
//        drawCylinder(legRadius, legLength);
//    glPopMatrix();
//    
//    // Right leg (scaled cylinder)
//    glPushMatrix();
//        setColor(pantsR, pantsG, pantsB);
//        glTranslatef(legX, legY, legZ);   // Right leg position
//        glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
//        glScalef(legThickness, legThickness, 0.7f);  // Make cylindrical
//        drawCylinder(legRadius, legLength);
//    glPopMatrix();
//    
//    // Shoes (scaled cubes)
//    // Left shoe
//    glPushMatrix();
//        setColor(shoeR, shoeG, shoeB);
//        glTranslatef(-legX - 0.03f, shoeY, shoeZ);  // Slightly offset from leg
//        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);       // Orient horizontally
//        glScalef(0.3f, 0.15f, 0.6f);               // Shoe proportions
//        drawCube(shoeSize);
//    glPopMatrix();
//    
//    // Right shoe
//    glPushMatrix();
//        setColor(shoeR, shoeG, shoeB);
//        glTranslatef(legX + 0.03f, shoeY, shoeZ);   // Slightly offset from leg
//        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);       // Orient horizontally
//        glScalef(0.3f, 0.15f, 0.6f);               // Shoe proportions
//        drawCube(shoeSize);
//    glPopMatrix();
//}
//
//// Main function that composes the complete Newton figure
//void drawNewton() {
//    glPushMatrix();  // Isolate Newton's transformations
//        // Apply global transformations
//        glTranslatef(newtonPosX, newtonPosY, newtonPosZ);  // Position in the scene
//        glRotatef(newtonRotX, 1.0f, 0.0f, 0.0f);          // Rotation
//        glScalef(newtonScale, newtonScale, newtonScale);   // Uniform scaling
//        
//        // Assemble the complete figure
//        drawHead();
//        drawTorso();
//        drawArms();
//        drawLegs();
//    glPopMatrix();  // End Newton's transformation scope
//}

#include "newton.h"

// Function prototypes
void drawHead();      // Draws Newton's head with facial features and wig
void drawTorso();     // Draws torso with coat, vest, and accessories
void drawArms();      // Draws arms and hands, including the book being held
void drawLegs();      // Draws legs and shoes
void drawBook();      // Draws the book Newton is reading

// Global transformation variables for Newton figure
float newtonScale = 0.5f;           // Uniform scaling factor for an entire figure
float newtonPosX = 0.0f;            // X-axis position in world space
float newtonPosY = -0.5f;           // Y-axis position (vertical)
float newtonPosZ = 0.35f;            // Z-axis position (depth)
float newtonRotX = 90.0f;            // Rotation angle around X-axis (for posing)

// Draws Newton's head with all facial features and wig
void drawHead() {
    extern GLuint skinTexture, hairTexture; // Make sure these are loaded elsewhere

    float headY = 1.4f;
    float headRadius = 0.35f;
    float eyeRadius = 0.035f;
    float eyeSpacing = 0.12f;
    float eyeForwardZ = 0.31f;
    float eyeUpY = 0.08f;
    float noseRadius = 0.06f;
    float noseForwardZ = 0.31f;
    float noseDownY = -0.05f;

    float wigCapY = 0.25f;
    float wigCapZ = -0.2f;
    float wigCapRadius = 0.4f;
    float curlRadius = 0.1f;
    float curlSpacing = 0.15f;
    float sideX = 0.45f;
    float backZ = -0.35f;

    glPushMatrix();
    glTranslatef(0.0f, headY, 0.0f);

    // Head (with skin texture)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skinTexture);
    glColor3f(1.0f, 1.0f, 1.0f); // White to keep texture colors
    drawSphere(headRadius);
    glDisable(GL_TEXTURE_2D);

    // Eyes
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, blackTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-eyeSpacing, eyeUpY, eyeForwardZ);
        drawSphere(eyeRadius);
        glTranslatef(eyeSpacing * 2, 0.0f, 0.0f);
        drawSphere(eyeRadius);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Nose (with skin texture)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, noseTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, noseDownY, noseForwardZ);
        glScalef(1.0f, 0.5f, 1.3f);
        drawSphere(noseRadius);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Wig cap (with hair texture)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, hairTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, wigCapY, wigCapZ);
        glScalef(1.6f, 1.0f, 1.2f);
        drawSphere(wigCapRadius);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Side curls - left
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hairTexture);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(-sideX, -0.05f - i * curlSpacing, 0.0f);
            drawSphere(curlRadius);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    // Side curls - right
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hairTexture);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(sideX, -0.05f - i * curlSpacing, 0.0f);
            drawSphere(curlRadius);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    // Back curls
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hairTexture);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(0.0f, -0.1f - i * curlSpacing, backZ);
            drawSphere(curlRadius);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    glPopMatrix();
}

// Draws Newton's torso with coat, collar, vest and buttons
void drawTorso() {
    extern GLuint coatTexture, goldTexture, whiteTexture;

    float torsoRadius = 0.35f, torsoHeight = 0.8f;
    float collarY = 0.9f, collarRadius = 0.22f, collarHeight = 0.20f;
    float cravatY = 1.02f, cravatZ = 0.2f, cravatSize = 0.5f;
    float vestY = 0.5f, vestZ = 0.2f, vestSize = 0.75f;
    float buttonSpacing = 0.12f, buttonRadius = 0.025f, buttonZ = 0.25f;
    int buttonCount = 6;
    float topButtonY = 0.8f;

    // Torso base (purple coat)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, coatTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glScalef(1.0f, 1.2f, 0.7f);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(torsoRadius, torsoHeight);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Collar (also purple texture)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, collarTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, collarY, 0.0f);
        glRotatef(-90, 1, 0, 0);
        drawCylinder(collarRadius, collarHeight);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Cravat (white texture)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, whiteTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, cravatY, cravatZ);
        glScalef(0.25f, 0.4f, 0.15f);
        drawCube(cravatSize);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Vest (gold texture)
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, brownTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, vestY, vestZ);
        glScalef(0.6f, 1.0f, 0.18f);
        drawCube(vestSize);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Buttons (gold texture on spheres)
    for (int i = 0; i < buttonCount; i++) {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, goldTexture);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(0.0f, topButtonY - i * buttonSpacing, buttonZ);
            drawSphere(buttonRadius);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

// Draws the book Newton is holding
void drawBook() {
    // Book dimensions
    float pageWidth = 0.45f;          // Width of open book spread
    float pageHeight = 0.6f;          // Height of pages
    float pageDepth = 0.01f;          // Thickness of pages
    float bindingWidth = 0.05f;        // Spine width
    float bindingHeight = 0.62f;       // Spine height
    
    // Color values (RGB)
    float pageR = 0.95f, pageG = 0.95f, pageB = 0.9f;  // Off-white pages
    float bindingR = 0.4f, bindingG = 0.15f, bindingB = 0.05f; // Brown binding
    float textR = 0.1f, textG = 0.1f, textB = 0.1f;    // Black text

    // Central spine (book binding)
    glPushMatrix();
        setColor(bindingR, bindingG, bindingB);
        glScalef(bindingWidth, bindingHeight, pageDepth * 3); // Thicker spine
        drawCube(1.0f);
    glPopMatrix();

    // Common Z-offset for covers and pages
    float coverZ = pageDepth * 0.4f;

    // Page block (static inner pages)
    glPushMatrix();
        setColor(pageR, pageG, pageB);
        glTranslatef(0.0f, 0.0f, coverZ - pageDepth * 0.5f); // Slightly under covers
        glScalef(pageWidth * 2, pageHeight, pageDepth * 1.5f); // Full page block
        drawCube(1.0f);
    glPopMatrix();

    // Text lines (simulated with thin rectangles)
    for (int i = 0; i < 8; i++) {  // 8 lines of text per page
        float yOffset = (pageHeight * 0.3f) - (i * 0.06f); // Vertical position
        float jitter = (i % 2 == 0) ? 0.005f : -0.005f;   // Alternating offset

        // Left page text line
        glPushMatrix();
            glTranslatef(-bindingWidth * 0.5f, 0.0f, pageDepth * 2.5f);
            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
            glTranslatef(-pageWidth, yOffset + jitter, 0.0f);
            glTranslatef(pageWidth * 0.5f, 0.0f, 0.0f);
            setColor(textR, textG, textB);
            glScalef(pageWidth * 0.8f, 0.01f, pageDepth); // Thin rectangle
            drawCube(1.0f);
        glPopMatrix();

        // Right page text line
        glPushMatrix();
            glTranslatef(bindingWidth * 0.5f, 0.0f, pageDepth * 2.5f);
            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
            glTranslatef(pageWidth, yOffset + jitter, 0.0f);
            glTranslatef(-pageWidth * 0.5f, 0.0f, 0.0f);
            setColor(textR, textG, textB);
            glScalef(pageWidth * 0.8f, 0.01f, pageDepth); // Thin rectangle
            drawCube(1.0f);
        glPopMatrix();
    }
}

// Draws Newton's arms and hands, including the book
void drawArms() {
    // Arm dimensions
    float armLength = 0.75f;
    float armOffsetX = 0.4f;
    float shoulderY = 0.6f;
    float shoulderZ = 0.4f;
    float handRadius = 0.12f;
    float armThickness = 0.18f;

    // --- LEFT ARM ---
    glPushMatrix();
        glTranslatef(-armOffsetX, shoulderY, shoulderZ);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(armThickness, armLength, armThickness);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, coatTexture);
        glColor3f(1.0f, 1.0f, 1.0f); // Prevent tint
        drawCube(1.0f);     // Needs to support tex coords
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Left hand
    glPushMatrix();
        glTranslatef(-armOffsetX, shoulderY, shoulderZ + (armLength * 0.5f));

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, skinTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawSphere(handRadius);  // Needs tex support
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- RIGHT ARM ---
    glPushMatrix();
        glTranslatef(armOffsetX, shoulderY, shoulderZ);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(armThickness, armLength, armThickness);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, coatTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCube(1.0f);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Right hand
    glPushMatrix();
        glTranslatef(armOffsetX, shoulderY, shoulderZ + (armLength * 0.5f));

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, skinTexture);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawSphere(handRadius);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- Book ---
    glPushMatrix();
        glTranslatef(0.0f, shoulderY + 0.15f, shoulderZ + (armLength * 0.5f) + 0.15f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
        drawBook();  // Optional: Add texture to book if desired
    glPopMatrix();
}


// Draws Newton's legs and shoes
void drawLegs() {
    // Leg dimensions
    float bottomY = -0.70f;
    float bottomHeight = 1.17f;
    float bottomRadius = 0.35f;
    float legY = -0.59f;
    float legX = 0.3f;
    float legZ = 0.05f;
    float legThickness = 0.22f;
    float legRadius = 0.4f;
    float legLength = 1.5f;
    float shoeY = -0.46f;
    float shoeZ = 1.1f;
    float shoeSize = 0.8f;

    // --- Bottom pants section ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, blackTexture);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(0.0f, bottomY, 0.0f);
        glScalef(1.0f, 0.6f, 0.7f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        drawCylinder(bottomRadius, bottomHeight);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- Left leg ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, blackTexture);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-legX, legY, legZ);
        glScalef(legThickness, legThickness, 0.7f);
        drawCylinder(legRadius, legLength);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- Right leg ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, blackTexture);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(legX, legY, legZ);
        glScalef(legThickness, legThickness, 0.7f);
        drawCylinder(legRadius, legLength);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- Left shoe ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, brownTexture);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-legX - 0.03f, shoeY, shoeZ);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.3f, 0.15f, 0.6f);
        drawCube(shoeSize);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // --- Right shoe ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, brownTexture);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(legX + 0.03f, shoeY, shoeZ);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.3f, 0.15f, 0.6f);
        drawCube(shoeSize);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
// Main function that composes the complete Newton figure
void drawNewton() {
    glPushMatrix();  // Isolate Newton's transformations
        // Apply global transformations
        glTranslatef(newtonPosX, newtonPosY, newtonPosZ);  // Position in the scene
        glRotatef(newtonRotX, 1.0f, 0.0f, 0.0f);          // Rotation
        glScalef(newtonScale, newtonScale, newtonScale);   // Uniform scaling
        
        // Assemble the complete figure
        drawHead();
        drawTorso();
        drawArms();
        drawLegs();
    glPopMatrix();  // End Newton's transformation scope
}

