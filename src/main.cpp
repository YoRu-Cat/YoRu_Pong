#include <raylib.h>

int main()
{
  int width = 1600;
  int height = 900;
  Color bgColor = {205, 25, 74, 255};
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(width, height, "YoRu Pong");
  SetTargetFPS(120);
  int ballX = width / 2;
  int ballY = height / 2;
  bool drag = false;
  Vector2 dragOffset = {0, 0};
  // Game loop
  while (!WindowShouldClose())
  {
    // Event handling
    Vector2 mousePosition = GetMousePosition();
    // Vector2 is a Built in Element provided by Raylib that takes two float values, x and y and draw 2D calculations
    bool closeButtonClicked = false;
    if (IsKeyDown(KEY_RIGHT))
    {
      ballX += 2;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
      ballX -= 2;
    }
    else if (IsKeyDown(KEY_UP))
    {
      ballY -= 2;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
      ballY += 2;
    }
    if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))
    {
      ballX += 1;
      ballY -= 1;
    }
    else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN))
    {
      ballY += 1;
      ballX += 1;
    }
    else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))
    {
      ballY -= 1;
      ballX -= 1;
    }
    else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN))
    {
      ballY += 1;
      ballX -= 1;
    }
    // else if (IsKeyDown(KEY_SPACE))
    // {
    //   bgColor = {(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255};
    // }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (mousePosition.x >= 1565 && mousePosition.x <= 1600 &&
          mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        closeButtonClicked = true;
      }
      else if (mousePosition.y >= 0 && mousePosition.y <= 10)
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
    // Coordinate system
    // increasing x value moves right
    // increasing y value moves down

    // Updating positions
    // ballX += 2;

    // Drawing
    ClearBackground(RAYWHITE);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("YoRu Pong", 10, 10, 20, DARKGRAY);

    // Draw close button
    DrawRectangle(1570, 0, 30, 30, RED);
    DrawText("X", 1577, 2, 30, WHITE);

    // Draw the ball
    DrawCircle(ballX, ballY, 15, bgColor);
    EndDrawing();

    if (closeButtonClicked)
    {
      break;
    }
  }

  CloseWindow();
  return 0;
}