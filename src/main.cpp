#include <raylib.h>

int player1Score = 0;
bool isGameOver = false;

float ballX, ballY;
int ballSpeedX, ballSpeedY;
int ballRadius;

float paddleX, paddleY;
float paddleWidth, paddleHeight;
int paddleSpeed;

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
    player1Score++;
    ballSpeedX *= -1;
  }
}

void ResetBall()
{
  ballX = GetScreenWidth() / 2;
  ballY = GetScreenHeight() / 2;
  ballSpeedX = 5;
  ballSpeedY = 5;
}

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

void ResetGame()
{
  isGameOver = false;
  player1Score = 0;
  ResetBall();
  ResetPaddle();
}

int main()
{
  const int width = GetScreenWidth() / 1.2;
  const int height = GetScreenHeight() / 1.2;
  Color bgColor = {205, 25, 74, 255};
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(width, height, "YoRu Pong");
  SetTargetFPS(120);

  ballX = width / 2;
  ballY = height / 2;
  ballSpeedX = 5;
  ballSpeedY = 5;
  ballRadius = 15;

  paddleX = width - 35;
  paddleY = height / 2 - 60;
  paddleWidth = 25;
  paddleHeight = 120;
  paddleSpeed = 6;

  bool drag = false;
  Vector2 dragOffset = {0, 0};

  while (!WindowShouldClose())
  {
    Vector2 mousePosition = GetMousePosition();
    bool closeButtonClicked = false;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (mousePosition.x >= width - 35 && mousePosition.x <= width &&
          mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        closeButtonClicked = true;
      }
      else if (mousePosition.y >= 0 && mousePosition.y <= 30)
      {
        drag = true;
        dragOffset = mousePosition;
      }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
      drag = false;
    }

    if (drag)
    {
      Vector2 currentMousePosition = GetMousePosition();
      Vector2 delta = {currentMousePosition.x - dragOffset.x, currentMousePosition.y - dragOffset.y};
      SetWindowPosition(GetWindowPosition().x + delta.x, GetWindowPosition().y + delta.y);
    }

    if (isGameOver)
    {
      if (IsKeyPressed(KEY_ENTER))
      {
        ResetGame();
      }
    }
    else
    {
      MoveBall();
      MovePaddle();
    }

    if (CheckCollisionCircleRec({ballX, ballY}, ballRadius, {paddleX, paddleY, paddleWidth, paddleHeight}))
    {
      ballSpeedX *= -1;
    }

    ClearBackground(RAYWHITE);
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1600, 35, bgColor);
    DrawText("YoRu Pong", 50, 8, 20, RAYWHITE);

    Rectangle rec = {0, 0, 1600, 900};
    DrawRectangleLinesEx(rec, 5, bgColor);

    Rectangle rec1 = {0, 30, 30, 900};
    DrawRectangleLinesEx(rec1, 5, bgColor);

    Rectangle rec2 = {1568, 2, 30, 30};
    DrawRectangleLinesEx(rec2, 1, RAYWHITE);
    DrawText("X", 1574, 3, 30, WHITE);
    DrawCircleLines(width / 2, height / 2, 100, bgColor);

    DrawBall();
    DrawPaddle();
    DrawText("Score:", width / 1.2, height / 10, 50, bgColor);
    DrawText(TextFormat("%i", player1Score), width / 1.2, height / 6, 60, bgColor);
    DrawLine(width / 2, 35, width / 2, height, bgColor);
    DrawText("FPS:", width / 8, height / 10, 50, bgColor);
    DrawText(TextFormat("%i", GetFPS()), width / 8, height / 6, 60, bgColor);

    if (isGameOver)
    {
      DrawRectangle(width / 2 - 200, height / 2 - 75, 400, 150, bgColor);
      DrawText("Game Over", width / 2 - 100, height / 2 - 30, 40, RAYWHITE);
      DrawText("Press Enter to Restart", width / 2 - 120, height / 2 + 20, 20, RAYWHITE);
    }
    EndDrawing();

    if (closeButtonClicked)
    {
      break;
    }
  }

  CloseWindow();
  return 0;
}
