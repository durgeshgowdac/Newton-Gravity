cmake_minimum_required(VERSION 3.16)
project(Newton_Gravity
        VERSION 1.0
        LANGUAGES CXX
        DESCRIPTION "Newton's Gravity Simulation with Apple Physics"
)

# Package information
# set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/yourusername/newton-gravity")

# Policy settings for better compatibility
cmake_policy(SET CMP0079 NEW)  # Honor linked libraries in targets

# Global project settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Platform-specific configurations
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)  # Enable relative paths for macOS bundles
endif()

# Add the main application subdirectory
add_subdirectory(Newton-Gravity)

# Installation configuration (optional)
if(WIN32)
    set(INSTALL_BIN_DIR .)
else()
    set(INSTALL_BIN_DIR bin)
endif()

install(
        DIRECTORY Newton-Gravity/textures
        DESTINATION share/Newton_Gravity
        PATTERN "CMakeLists.txt" EXCLUDE
)