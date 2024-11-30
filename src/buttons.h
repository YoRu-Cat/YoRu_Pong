#pragma once
#include <raylib.h>

Texture2D CreateButton(const char *path, Vector2 *position, float scale);
void DestroyButton(Texture2D texture);
void DrawButton(Texture2D texture, Vector2 position);
bool IsButtonClicked(Texture2D texture, Vector2 position);
