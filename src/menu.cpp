#include <raylib.h>
#include "YoRu.h"

#define MAX_INPUT_CHARS 8

extern bool gameStarted;
extern bool showLeaderboard;
extern bool showSettings;
extern bool themePage;
extern char nam[MAX_INPUT_CHARS + 1];

char name[MAX_INPUT_CHARS + 1] = "\0";
int letterCount = 0;
Rectangle textBox = {GetScreenWidth() / 2.0f - 150, GetScreenHeight() / 2.0f + 150, 300, 70}; // Adjusted y coordinate and size
bool mouseOnText = false;
int framesCounter = 0;

void UpdateTextBox()
{
  Vector2 mousePosition = GetMousePosition();
  if (CheckCollisionPointRec(mousePosition, textBox))
    mouseOnText = true;
  else
    mouseOnText = false;

  if (mouseOnText)
  {
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    int key = GetCharPressed();
    while (key > 0)
    {
      if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
      {
        name[letterCount] = (char)key;
        name[letterCount + 1] = '\0';
        letterCount++;
      }
      key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
      letterCount--;
      if (letterCount < 0)
        letterCount = 0;
      name[letterCount] = '\0';
    }
  }
  else
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

  if (mouseOnText)
  {
    framesCounter++;
  }
  else
  {
    framesCounter = 0;
  }
}

void DrawTextBox()
{
  textBox.width = 300.0f; // Set the width equal to other buttons
  textBox.height = 70.0f; // Set the height equal to other buttons
  textBox.x = GetScreenWidth() / 2.0f - textBox.width / 2.0f;
  DrawRectangleRec(textBox, LIGHTGRAY);
  if (mouseOnText)
    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
  else
    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

  DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
  DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), GetScreenWidth() / 2 - MeasureText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 20) / 2, GetScreenHeight() / 2 + 280, 20, DARKGRAY); // Adjusted y coordinate

  if (mouseOnText)
  {
    if (letterCount < MAX_INPUT_CHARS)
    {
      if (((framesCounter / 20) % 2) == 0)
        DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
    }
    else
      DrawText("Press BACKSPACE to delete chars...", GetScreenWidth() / 2 - MeasureText("Press BACKSPACE to delete chars...", 20) / 2, GetScreenHeight() / 2 + 330, 20, GRAY); // Adjusted y coordinate
  }
}

void DrawMenu()
{
  UpdateTextBox();

  Color bgColor = {205, 25, 74, 255};
  Vector2 mousePosition = GetMousePosition();
  bool playButtonClicked = false;
  bool leaderboardButtonClicked = false;
  bool settingsButtonClicked = false;
  bool exitButtonClicked = false;

  float buttonWidth = 300.0f;
  float buttonHeight = 70.0f;
  float buttonSpacing = 16.0f;
  float startY = GetScreenHeight() / 2 - (buttonHeight * 2 + buttonSpacing * 1.5f);

  Rectangle playButton = {(float)(GetScreenWidth() / 2 - buttonWidth / 2), startY, buttonWidth, buttonHeight};
  Rectangle leaderBoard = {(float)(GetScreenWidth() / 2 - buttonWidth / 2), startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight};
  Rectangle settingsButton = {(float)(GetScreenWidth() / 2 - buttonWidth / 2), startY + (buttonHeight + buttonSpacing) * 2, buttonWidth, buttonHeight};
  Rectangle exitButton = {(float)(GetScreenWidth() / 2 - buttonWidth / 2), startY + (buttonHeight + buttonSpacing) * 3, buttonWidth, buttonHeight};

  if (CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && letterCount > 3)
  {
    playButtonClicked = true;
  }
  else
  {
    DrawText("Enter your name to play (atlest 4 chars)", GetScreenWidth() / 2 - MeasureText("Enter your name to play (atlest 4 chars)", 20) / 2, GetScreenHeight() / 2 + 380, 20, DARKGRAY); // Adjusted y coordinate
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

  DrawTextBox();

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
    for (int i = 0; i <= letterCount; i++)
    {
      nam[i] = name[i];
    }
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