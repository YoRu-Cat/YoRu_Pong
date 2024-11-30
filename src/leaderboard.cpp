#include "YoRu.h"
#include <raylib.h>

extern bool showLeaderboard;

void DrawLeaderboard()
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawSavedScores();

  DrawText("Press BACKSPACE to go back", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 20, DARKGRAY);

  EndDrawing();

  if (IsKeyPressed(KEY_BACKSPACE))
  {
    showLeaderboard = false;
  }
}