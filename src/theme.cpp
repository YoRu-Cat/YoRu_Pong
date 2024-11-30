#include <raylib.h>
#include "YoRu.h"

extern bool themePage;
extern bool showSettings;

void DrawThemePage()
{
  Color bgColor = {205, 25, 74, 255};
  Vector2 mousePosition = GetMousePosition();
  bool themeClicked[22] = {false};

  const int buttonWidth = 200;
  const int buttonHeight = 50;
  const int spacing = 20;
  const int buttonsPerRow = 3;
  const int totalButtons = 22;
  Rectangle themeButtons[totalButtons];

  for (int i = 0; i < totalButtons; i++)
  {
    int row = i / buttonsPerRow;
    int col = i % buttonsPerRow;
    themeButtons[i] = {(float)(GetScreenWidth() / 2 - (buttonWidth * buttonsPerRow + spacing * (buttonsPerRow - 1)) / 2 + col * (buttonWidth + spacing)), 150.0f + row * (buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight};

    if (CheckCollisionPointRec(mousePosition, themeButtons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      themeClicked[i] = true;
    }
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  for (int i = 0; i < totalButtons; i++)
  {
    DrawRectangleRec(themeButtons[i], bgColor);
    DrawText(TextFormat("Theme %d", i + 1), themeButtons[i].x + themeButtons[i].width / 2 - MeasureText(TextFormat("Theme %d", i + 1), 20) / 2, themeButtons[i].y + themeButtons[i].height / 2 - 10, 20, RAYWHITE);
  }

  DrawText("Press BACKSPACE to go back", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 20, DARKGRAY);

  EndDrawing();

  for (int i = 0; i < totalButtons; i++)
  {
    if (themeClicked[i])
    {
      bgColor = {205, 25, 74, 255}; // Change this to different colors for each theme if needed
    }
  }

  if (IsKeyPressed(KEY_BACKSPACE))
  {
    themePage = false;
    showSettings = true;
  }
}
