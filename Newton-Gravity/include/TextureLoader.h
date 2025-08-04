// TextureLoader.h - Texture management system
#pragma once
#include "imports.h"

// Texture Identifiers
extern GLuint groundTexture;  // Ground surface texture
extern GLuint barkTexture;    // Tree bark texture
extern GLuint leafTexture;    // Foliage texture
extern GLuint skyTexture;     // Skybox/sky background texture
extern GLuint appleTexture;   // Apple surface texture

// Newton
extern GLuint skinTexture;    // Skin texture
extern GLuint hairTexture;    // Hair Texture
extern GLuint noseTexture;    // Nose texture

extern GLuint coatTexture; 
extern GLuint collarTexture;
extern GLuint goldTexture;   // For vest and buttons
extern GLuint whiteTexture;  // For cravat

extern GLuint blackTexture;
extern GLuint brownTexture;

// Initialization
void initTextures(bool useTexture=true);  // Loads all textures with optional fallback mode
