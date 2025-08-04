cmake_minimum_required(VERSION 3.16)
project(Newton-Gravity LANGUAGES CXX)

# Set C++ standard to match parent project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler warnings (consistent with parent)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
        apple.cpp
        controls.cpp
        environment.cpp
        main.cpp
        message.cpp
        newton.cpp
        primitives.cpp
        TextureLoader.cpp
        tree.cpp
        menu.cpp
)

# Create the executable
add_executable(Newton-Gravity ${SOURCES})

# Include headers
target_include_directories(Newton-Gravity PRIVATE include)

# Find OpenGL and GLUT
find_package(OpenGL REQUIRED)

# Platform-specific GLUT handling
if(APPLE)
    find_library(GLUT_LIBRARY GLUT REQUIRED)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)  # Required for macOS GLUT

    target_link_libraries(Newton-Gravity PRIVATE
            ${OPENGL_LIBRARY}
            ${GLUT_LIBRARY}
            ${COCOA_LIBRARY}
    )

    # Disable deprecated OpenGL warnings on macOS
    target_compile_definitions(Newton-Gravity PRIVATE
            GL_SILENCE_DEPRECATION
    )

    # Set macOS deployment target for better compatibility
    set_target_properties(Newton-Gravity PROPERTIES
            MACOSX_DEPLOYMENT_TARGET "10.14"
    )
else()
    find_package(GLUT REQUIRED)
    target_link_libraries(Newton-Gravity PRIVATE
            OpenGL::GL
            ${GLUT_LIBRARIES}
    )

    # Add GLUT include directories for non-Apple platforms
    target_include_directories(Newton-Gravity PRIVATE ${GLUT_INCLUDE_DIRS})
endif()

# Copy textures to build directory (only if they exist)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/textures")
    add_custom_command(TARGET Newton-Gravity POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/textures
            $<TARGET_FILE_DIR:Newton-Gravity>/textures
            COMMENT "Copying textures to build directory"
    )
else()
    message(WARNING "Textures directory not found - some features may not work correctly")
endif()

# Set output directory for better organization
set_target_properties(Newton-Gravity PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation (optional)
install(TARGETS Newton-Gravity
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/textures")
    install(DIRECTORY textures
            DESTINATION share/Newton_Gravity
            PATTERN "CMakeLists.txt" EXCLUDE
    )
endif()