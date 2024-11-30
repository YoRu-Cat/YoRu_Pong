#include "raylib.h"
#include <cmath>

const int MAX_FRAME_DELAY = 60;
const int MIN_FRAME_DELAY = 1;

void UpdateAnimationFrame(Image &imScarfyAnim, Texture2D &texScarfyAnim, int &currentAnimFrame, int animFrames, int &frameCounter, int frameDelay)
{
  frameCounter++;
  if (frameCounter >= frameDelay)
  {
    currentAnimFrame++;
    if (currentAnimFrame >= animFrames)
      currentAnimFrame = 0;

    unsigned int nextFrameDataOffset = imScarfyAnim.width * imScarfyAnim.height * 4 * currentAnimFrame;
    UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrameDataOffset);

    frameCounter = 0;
  }
}

void HandleInput(int &frameDelay, int screenWidth, int screenHeight)
{
  if (IsKeyPressed(KEY_RIGHT))
    frameDelay++;
  else if (IsKeyPressed(KEY_LEFT))
    frameDelay--;

  if (frameDelay > MAX_FRAME_DELAY)
    frameDelay = MAX_FRAME_DELAY;
  else if (frameDelay < MIN_FRAME_DELAY)
    frameDelay = MIN_FRAME_DELAY;

  if (IsKeyPressed(KEY_F11))
  {
    if (IsWindowFullscreen())
    {
      ToggleFullscreen();
      SetWindowSize(screenWidth, screenHeight);
    }
    else
    {
      ToggleFullscreen();
    }
  }
}

void DrawFrame(Texture2D &texScarfyAnim, Image &imScarfyAnim)
{
  ClearBackground(RAYWHITE);

  float scale = fmaxf((float)GetScreenWidth() / imScarfyAnim.width, (float)GetScreenHeight() / imScarfyAnim.height);
  DrawTextureEx(texScarfyAnim, (Vector2){0, 0}, 0.0f, scale, WHITE);
}
