#include "raylib.h"

Texture2D CreateButton(const char *path, Vector2 *position, float scale)
{
  Image image = LoadImage(path);
  int imgWidth = image.width;
  int imgHeight = image.height;
  int newWidth = static_cast<int>(imgWidth * scale);
  int newHeight = static_cast<int>(imgHeight * scale);
  ImageResize(&image, newWidth, newHeight);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  // GetScreenWidth() and GetScreenHeight() return the screen dimensions
  *position = {(GetScreenWidth() - newWidth) / 2.0f, (GetScreenHeight() - newHeight) / 2.0f};

  return texture;
}

void DestroyButton(Texture2D texture)
{
  UnloadTexture(texture);
}

void DrawButton(Texture2D texture, Vector2 position)
{
  DrawTextureV(texture, position, WHITE);
}
bool IsButtonClicked(Texture2D texture, Vector2 position)
{
  Vector2 mousePoint = GetMousePosition();
  Rectangle buttonRect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};

  if (CheckCollisionPointRec(mousePoint, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    return true;
  }
  return false;
}