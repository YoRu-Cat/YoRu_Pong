#include <math.h>
#include <raylib.h>
#include "ball.h"
#include "player.h"
#include "fileHand.h"
#include "buttons.h"
#include "anim.h"
#include "menu.h"        // Include the menu header file
#include "setting.h"     // Include the setting header file
#include "theme.h"       // Include the theme header file
#include "leaderboard.h" // Include the leaderboard header file
#include "reset.h"       // Include the reset header file
#include <fstream>
using namespace std;

const int MAX_FRAME_DELAY = 60;
const int MIN_FRAME_DELAY = 1;
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
  const int width = 1600;
  const int height = 900;

  Color bgColor = {205, 25, 74, 255};
  Color trans = {0, 0, 0, 0};
  Color tan = {0, 0, 0, 150};
  Color tanN = {255, 255, 255, 150};
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

  // Animation variables
  int animFrames = 0;
  Image imScarfyAnim = LoadImageAnim("Graphics/15.gif", &animFrames);
  Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
  int currentAnimFrame = 0;
  int frameDelay = 8;
  int frameCounter = 0;

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

    // Update animation frame and handle input
    UpdateAnimationFrame(imScarfyAnim, texScarfyAnim, currentAnimFrame, animFrames, frameCounter, frameDelay);
    HandleInput(frameDelay, width, height);

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
        player1Score++;
        if (player1Score % 5 == 0)
        {
          paddleHeight *= 0.9;
        }
        paddleSpeed *= 1.02;
        ballSpeedX *= 1.08;
        ballSpeedY *= 1.05;
      }

      // Draw the frame with the animated background

      BeginDrawing();
      DrawFrame(texScarfyAnim, imScarfyAnim);

      // DrawRectangle(0, 0, 1600, 35, bgColor);
      Rectangle rec0 = {0, 0, 1600, 35};
      DrawRectangleRec(rec0, tan);

      DrawText("YoRu Pong", 50, 10, 18, RAYWHITE);
      DrawText("V-3.0.1.", 200, 10, 18, RAYWHITE);

      Rectangle rec1 = {0, 35, 30, 900};
      DrawRectangleRec(rec1, tan);
      DrawLineEx({0, 35}, {1600, 35}, 1, tanN);
      Rectangle rec = {0, 0, 1600, 900};
      DrawRectangleLinesEx(rec, 5, bgColor);

      Rectangle rec2 = {1568, 2, 30, 30};
      DrawRectangleLinesEx(rec2, 1, trans);
      DrawText("X", 1574 - 5, 6, 30, WHITE);

      Rectangle rec3 = {1533, 2, 30, 30};
      DrawRectangleLinesEx(rec3, 1, trans);
      DrawText("-", 1542 - 5, 7, 30, WHITE);

      Rectangle rec4 = {1498, 2, 30, 30};
      DrawRectangleLinesEx(rec4, 1, trans);
      DrawText("O", 1504 - 5, 6, 30, WHITE);

      // DrawCircleLines(width / 2, height / 2, 100, bgColor);

      DrawBall();
      DrawPaddle();
      DrawText("Score:", width / 1.2, height / 10, 50, bgColor);
      DrawText(TextFormat("%i", player1Score), width / 1.2, height / 6, 60, bgColor);
      DrawText("FPS:", width / 8, height / 10, 50, bgColor);
      DrawText(TextFormat("%i", GetFPS()), width / 8, height / 6, 60, bgColor);
      // DrawLine(width / 2, 35, width / 2, height, bgColor);

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
      ToggleFullscreen();
    }
  }

  UnloadTexture(texScarfyAnim);
  UnloadImage(imScarfyAnim);
  CloseWindow();
  return 0;
}
