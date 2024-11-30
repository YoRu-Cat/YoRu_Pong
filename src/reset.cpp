#include "YoRu.h"

extern int player1Score;
extern bool isGameOver;
extern bool scoreSaved;
extern float paddleHeight;

void ResetGame()
{
  isGameOver = false;
  scoreSaved = false;
  player1Score = 0;
  paddleHeight = 120;
  ResetBall();
  ResetPaddle();
}