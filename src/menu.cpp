#include <raylib.h>
#include "menu.h"

extern bool gameStarted;
extern bool showLeaderboard;
extern bool showSettings;
extern bool themePage;

void DrawMenu()
{
  Color bgColor = {205, 25, 74, 255};
  Vector2 mousePosition = GetMousePosition();
  bool playButtonClicked = false;
  bool leaderboardButtonClicked = false;
  bool settingsButtonClicked = false;
  bool exitButtonClicked = false;

  Rectangle playButton = {(float)(GetScreenWidth() / 2 - 150), (float)(GetScreenHeight() / 2 - 120), 300.0f, 70.0f};
  Rectangle leaderBoard = {(float)(GetScreenWidth() / 2 - 150), (float)(GetScreenHeight() / 2 - 30), 300.0f, 70.0f};
  Rectangle settingsButton = {(float)(GetScreenWidth() / 2 - 150), (float)(GetScreenHeight() / 2 + 60), 300.0f, 70.0f};
  Rectangle exitButton = {(float)(GetScreenWidth() / 2 - 150), (float)(GetScreenHeight() / 2 + 150), 300.0f, 70.0f};

  if (CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    playButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, leaderBoard) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    leaderboardButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    settingsButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    exitButtonClicked = true;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawRectangleRec(playButton, bgColor);
  DrawText("Play", playButton.x + playButton.width / 2 - MeasureText("Play", 30) / 2, playButton.y + playButton.height / 2 - 15, 30, RAYWHITE);
  DrawRectangleRec(leaderBoard, bgColor);
  DrawText("LeaderBoard", leaderBoard.x + leaderBoard.width / 2 - MeasureText("LeaderBoard", 30) / 2, leaderBoard.y + leaderBoard.height / 2 - 15, 30, RAYWHITE);
  DrawRectangleRec(settingsButton, bgColor);
  DrawText("Settings", settingsButton.x + settingsButton.width / 2 - MeasureText("Settings", 30) / 2, settingsButton.y + settingsButton.height / 2 - 15, 30, RAYWHITE);
  DrawRectangleRec(exitButton, bgColor);
  DrawText("Exit", exitButton.x + exitButton.width / 2 - MeasureText("Exit", 30) / 2, exitButton.y + exitButton.height / 2 - 15, 30, RAYWHITE);

  EndDrawing();

  if (playButtonClicked)
  {
    gameStarted = true;
  }
  if (leaderboardButtonClicked)
  {
    showLeaderboard = true;
  }
  if (settingsButtonClicked)
  {
    showSettings = true;
  }
  if (exitButtonClicked)
  {
    CloseWindow();
  }
}