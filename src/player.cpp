#include <raylib.h>
#include "player.h"

// External variable declarations
extern float paddleX, paddleY;
extern float paddleWidth, paddleHeight;
extern int paddleSpeed;

void DrawPaddle()
{
  Color bgColor = {205, 25, 74, 255};
  DrawRectangle(paddleX, paddleY, paddleWidth, paddleHeight, bgColor);
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