// imports.h - Centralized library imports and platform-specific OpenGL includes
#pragma once

// Standard Library Headers
#include <fstream>    // File operations
#include <cmath>      // Math functions
#include <cstdlib>    // Standard library functions
#include <ctime>      // Time functions
#include <algorithm>  // STL algorithms
#include <iostream>   // I/O streams

// OpenGL/GLUT Platform-Specific Includes
#ifdef __APPLE__
    // macOS OpenGL/GLUT headers
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    // Windows/Linux OpenGL/GLUT headers
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif