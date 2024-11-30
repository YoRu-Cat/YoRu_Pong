#pragma once
#include <raylib.h>

void UpdateAnimationFrame(Image &imScarfyAnim, Texture2D &texScarfyAnim, int &currentAnimFrame, int animFrames, int &frameCounter, int frameDelay);
void HandleInput(int &frameDelay, int screenWidth, int screenHeight);
void DrawFrame(Texture2D &texScarfyAnim, Image &imScarfyAnim);
