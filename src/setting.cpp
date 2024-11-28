#include <raylib.h>
#include "setting.h"

extern bool showSettings;
extern bool themePage;

void DrawSettings()
{
  Color bgColor = {205, 25, 74, 255};
  Vector2 mousePosition = GetMousePosition();
  bool themeButtonClicked = false;
  bool audioButtonClicked = false;
  bool fpsLockButtonClicked = false;
  bool moreButtonClicked = false;

  Rectangle themeButton = {(float)(GetScreenWidth() / 2 - 150), 150.0f, 300.0f, 50.0f};
  Rectangle audioButton = {(float)(GetScreenWidth() / 2 - 150), 220.0f, 300.0f, 50.0f};
  Rectangle fpsLockButton = {(float)(GetScreenWidth() / 2 - 150), 290.0f, 300.0f, 50.0f};
  Rectangle moreButton = {(float)(GetScreenWidth() / 2 - 150), 360.0f, 300.0f, 50.0f};

  if (CheckCollisionPointRec(mousePosition, themeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    themeButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, audioButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    audioButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, fpsLockButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    fpsLockButtonClicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, moreButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    moreButtonClicked = true;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawRectangleRec(themeButton, bgColor);
  DrawText("Theme", themeButton.x + themeButton.width / 2 - MeasureText("Theme", 20) / 2, themeButton.y + themeButton.height / 2 - 10, 20, RAYWHITE);
  DrawRectangleRec(audioButton, bgColor);
  DrawText("Audio", audioButton.x + audioButton.width / 2 - MeasureText("Audio", 20) / 2, audioButton.y + audioButton.height / 2 - 10, 20, RAYWHITE);
  DrawRectangleRec(fpsLockButton, bgColor);
  DrawText("FPS Lock", fpsLockButton.x + fpsLockButton.width / 2 - MeasureText("FPS Lock", 20) / 2, fpsLockButton.y + fpsLockButton.height / 2 - 10, 20, RAYWHITE);
  DrawRectangleRec(moreButton, bgColor);
  DrawText("More", moreButton.x + moreButton.width / 2 - MeasureText("More", 20) / 2, moreButton.y + moreButton.height / 2 - 10, 20, RAYWHITE);
  DrawText("Press BACKSPACE to go back", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 20, DARKGRAY);

  EndDrawing();
  if (themeButtonClicked)
  {
    themePage = true;
    showSettings = false;
  }
  if (IsKeyPressed(KEY_BACKSPACE))
  {
    showSettings = false;
  }
}