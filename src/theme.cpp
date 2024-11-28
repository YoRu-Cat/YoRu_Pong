#include <raylib.h>
#include "theme.h"

extern bool themePage;
extern bool showSettings;

void DrawThemePage()
{
  Color bgColor = {205, 25, 74, 255};
  Vector2 mousePosition = GetMousePosition();
  bool theme1Clicked = false;
  bool theme2Clicked = false;
  bool theme3Clicked = false;

  Rectangle theme1Button = {(float)(GetScreenWidth() / 2 - 150), 150.0f, 300.0f, 50.0f};
  Rectangle theme2Button = {(float)(GetScreenWidth() / 2 - 150), 220.0f, 300.0f, 50.0f};
  Rectangle theme3Button = {(float)(GetScreenWidth() / 2 - 150), 290.0f, 300.0f, 50.0f};

  if (CheckCollisionPointRec(mousePosition, theme1Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    theme1Clicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, theme2Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    theme2Clicked = true;
  }
  if (CheckCollisionPointRec(mousePosition, theme3Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    theme3Clicked = true;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawRectangleRec(theme1Button, bgColor);
  DrawText("Theme 1", theme1Button.x + theme1Button.width / 2 - MeasureText("Theme 1", 20) / 2, theme1Button.y + theme1Button.height / 2 - 10, 20, RAYWHITE);
  DrawRectangleRec(theme2Button, bgColor);
  DrawText("Theme 2", theme2Button.x + theme2Button.width / 2 - MeasureText("Theme 2", 20) / 2, theme2Button.y + theme2Button.height / 2 - 10, 20, RAYWHITE);
  DrawRectangleRec(theme3Button, bgColor);
  DrawText("Theme 3", theme3Button.x + theme3Button.width / 2 - MeasureText("Theme 3", 20) / 2, theme3Button.y + theme3Button.height / 2 - 10, 20, RAYWHITE);
  DrawText("Press BACKSPACE to go back", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 20, DARKGRAY);

  EndDrawing();

  if (theme1Clicked)
  {
    bgColor = {205, 25, 74, 255}; // Theme 1 color
  }
  if (theme2Clicked)
  {
    bgColor = {25, 205, 74, 255}; // Theme 2 color
  }
  if (theme3Clicked)
  {
    bgColor = {74, 25, 205, 255}; // Theme 3 color
  }

  if (IsKeyPressed(KEY_BACKSPACE))
  {
    themePage = false;
    showSettings = true;
  }
}