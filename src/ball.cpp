#include <raylib.h>
#include "ball.h"
#include "player.h"

// External variable declarations
extern float ballX, ballY;
extern int ballSpeedX, ballSpeedY;
extern int ballRadius;
extern bool isGameOver;
extern int player1Score;
extern float paddleX, paddleY;
extern float paddleWidth, paddleHeight;
extern int paddleSpeed;

void DrawBall()
{
  Color bgColor = {205, 25, 74, 255};
  DrawCircle(ballX, ballY, ballRadius, bgColor);
}

void MoveBall()
{
  ballX += ballSpeedX;
  ballY += ballSpeedY;
  if (ballY + ballRadius >= GetScreenHeight() || ballY - ballRadius <= 30)
  {
    ballSpeedY *= -1;
  }
  if (ballX + ballRadius >= GetScreenWidth())
  {
    isGameOver = true;
  }
  else if (ballX - ballRadius <= 30)
  {
    ballSpeedX *= -1;
  }
}

void ResetBall()
{
  ballX = GetScreenWidth() / 2;
  ballY = GetScreenHeight() / 2;
  ballSpeedX = 10;
  ballSpeedY = 10;
}
