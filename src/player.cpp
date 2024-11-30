#include <raylib.h>
#include "YoRu.h"

// External variable declarations
extern float paddleX, paddleY;
extern float paddleWidth, paddleHeight;
extern int paddleSpeed;

void DrawPaddle()
{
  Color bgColor = {205, 25, 74, 255};
  float roundness = 0.5f; // Roundness factor (0.0f to 1.0f)

  // Draw the paddle
  DrawRectangleRounded((Rectangle){paddleX, paddleY, paddleWidth, paddleHeight}, roundness, 16, bgColor);
}

void MovePaddle()
{
  if (IsKeyDown(KEY_UP) && paddleY > 45)
  {
    paddleY -= paddleSpeed;
  }
  else if (IsKeyDown(KEY_DOWN) && paddleY + paddleHeight + 10 < GetScreenHeight())
  {
    paddleY += paddleSpeed;
  }
}

void ResetPaddle()
{
  paddleY = GetScreenHeight() / 2 - paddleHeight / 2;
}
