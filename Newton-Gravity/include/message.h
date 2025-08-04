// message.h - message system
#pragma once
#include "imports.h"
#include "constants.h"

// Message Functions
void drawMessage();       // Renders the message
void updateMessage(float deltaTime); // Handles animation
void checkAppleHitGround();     // Checks collision for message trigger
