#pragma once
#include <raylib.h>

void UpdateAnimationFrame(Image &imScarfyAnim, Texture2D &texScarfyAnim, int &currentAnimFrame, int animFrames, int &frameCounter, int frameDelay);
void HandleInput(int &frameDelay, int screenWidth, int screenHeight);
void DrawFrame(Texture2D &texScarfyAnim, Image &imScarfyAnim);
void DrawBall();
void MoveBall();
void ResetBall();
Texture2D CreateButton(const char *path, Vector2 *position, float scale);
void DestroyButton(Texture2D texture);
void DrawButton(Texture2D texture, Vector2 position);
bool IsButtonClicked(Texture2D texture, Vector2 position);
void SaveScore(int score);
void DrawSavedScores();
void DrawLeaderboard();
void DrawMenu();
void DrawPaddle();
void MovePaddle();
void ResetPaddle();
void ResetGame();
void DrawSettings();
void DrawThemePage();
void LoadResources();
void UnloadResources();
