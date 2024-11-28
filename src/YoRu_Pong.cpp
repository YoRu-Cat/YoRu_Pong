#include <raylib.h>
#include "ball.h"
#include "player.h"
#include "fileHand.h"
#include "menu.h"        // Include the menu header file
#include "setting.h"     // Include the setting header file
#include "theme.h"       // Include the theme header file
#include "leaderboard.h" // Include the leaderboard header file
#include "reset.h"       // Include the reset header file
#include <fstream>
using namespace std;

int player1Score = 0;
bool isGameOver = false;
bool scoreSaved = false;
bool gameStarted = false;
bool showLeaderboard = false;
bool showSettings = false; // Add this flag
bool themePage = false;    // Add this flag
// ball ka content
float ballX, ballY;
int ballSpeedX, ballSpeedY;
int ballRadius;

// player ka content
float paddleX, paddleY;
float paddleWidth, paddleHeight;
int paddleSpeed;

int main()
{
  int width = 1600;
  const int height = 900;
  Color bgColor = {205, 25, 74, 255};
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(width, height, "YoRu Pong");
  SetTargetFPS(60);

  ballRadius = 20;
  ballX = width / 2;
  ballY = height / 2;
  ballSpeedX = 10;
  ballSpeedY = 10;

  paddleWidth = 25;
  paddleHeight = 120;
  paddleX = width - paddleWidth - 10;
  paddleY = height / 2 - paddleHeight / 2;
  paddleSpeed = 12;

  bool drag = false;
  Vector2 dragOffset = {0, 0};

  while (!WindowShouldClose())
  {
    Vector2 mousePosition = GetMousePosition();
    bool closeButtonClicked = false;
    bool minimizeButtonClicked = false;
    bool maximizeButtonClicked = false;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (mousePosition.x >= 1565 && mousePosition.x <= 1600 &&
          mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        closeButtonClicked = true;
      }
      else if (mousePosition.x >= 1530 && mousePosition.x <= 1565 &&
               mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        minimizeButtonClicked = true;
      }
      else if (mousePosition.x >= 1495 && mousePosition.x <= 1530 &&
               mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        maximizeButtonClicked = true;
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

    if (!gameStarted)
    {
      if (showLeaderboard)
      {
        DrawLeaderboard();
      }
      else if (showSettings)
      {
        DrawSettings();
      }
      else if (themePage)
      {
        DrawThemePage();
      }
      else
      {
        DrawMenu(); // Call the DrawMenu function from menu.cpp
      }
    }
    else
    {
      if (isGameOver)
      {
        if (!scoreSaved)
        {
          SaveScore(player1Score);
          scoreSaved = true;
        }
      }
      else
      {
        MoveBall();
        MovePaddle();
      }

      if (isGameOver && IsKeyPressed(KEY_ENTER))
      {
        ResetGame();
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
      DrawText("V-3.0.1.", 200, 8, 20, RAYWHITE);

      Rectangle rec = {0, 0, 1600, 900};
      DrawRectangleLinesEx(rec, 5, bgColor);

      Rectangle rec1 = {0, 30, 30, 900};
      DrawRectangleLinesEx(rec1, 5, bgColor);

      Rectangle rec2 = {1568, 2, 30, 30};
      DrawRectangleLinesEx(rec2, 1, RAYWHITE);
      DrawText("X", 1574, 3, 30, WHITE);

      Rectangle rec3 = {1533, 2, 30, 30};
      DrawRectangleLinesEx(rec3, 1, RAYWHITE);
      DrawText("-", 1542, 4, 30, WHITE);

      Rectangle rec4 = {1498, 2, 30, 30};
      DrawRectangleLinesEx(rec4, 1, RAYWHITE);
      DrawText("O", 1504, 3, 30, WHITE);

      DrawCircleLines(width / 2, height / 2, 100, bgColor);

      DrawBall();
      DrawPaddle();
      DrawText("Score:", width / 1.2, height / 10, 50, bgColor);
      DrawText(TextFormat("%i", player1Score), width / 1.2, height / 6, 60, bgColor);
      DrawText("FPS:", width / 8, height / 10, 50, bgColor);
      DrawText(TextFormat("%i", GetFPS()), width / 8, height / 6, 60, bgColor);
      DrawLine(width / 2, 35, width / 2, height, bgColor);

      if (isGameOver)
      {
        DrawRectangle(width / 2 - 200, height / 2 - 75, 400, 150, bgColor);
        DrawText("Game Over", width / 2 - 100, height / 2 - 30, 40, RAYWHITE);
        DrawText("Press Enter to Restart", width / 2 - 120, height / 2 + 20, 20, RAYWHITE);
      }

      EndDrawing();
    }

    if (closeButtonClicked)
    {
      break;
    }
    if (minimizeButtonClicked || IsKeyPressed(KEY_F10))
    {
      MinimizeWindow();
    }
    if (maximizeButtonClicked || IsKeyPressed(KEY_F11))
    {
      // if (IsWindowFullscreen())
      // {
      //   SetTargetFPS(120);
      //   ballSpeedX = 5;
      //   ballSpeedY = 5;
      //   paddleSpeed = 6;
      // }
      // else if (!IsWindowFullscreen())
      // {
      //   SetTargetFPS(60);
      //   ballSpeedX = 11;
      //   ballSpeedY = 11;
      //   paddleSpeed = 13;
      // }
      ToggleFullscreen();
    }
  }

  CloseWindow();
  return 0;
}
