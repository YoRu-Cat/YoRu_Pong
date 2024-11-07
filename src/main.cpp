#include <raylib.h>

class Ball
{
public:
  float x = 0.0, y = 0.0;
  int speedX = 0, speedY = 0;
  int radius = 0;
  void draw()
  {
    Color bgColor = {205, 25, 74, 255};
    DrawCircle(x, y, radius, bgColor);
  }
  void move()
  {
    x += speedX;
    y += speedY;
    if (y + radius >= GetScreenHeight() || y - radius <= 30)
    {
      speedY *= -1;
    }
    if (x + radius >= GetScreenWidth() || x - radius <= 30)
    {
      speedX *= -1;
    }
  }
};

class Paddle
{
public:
  float x, y;
  float width, height;
  int speed;
  void draw()
  {
    Color bgColor = {205, 25, 74, 255};
    DrawRectangle(x, y, width, height, bgColor);
  }
  void move()
  {
    if (IsKeyDown(KEY_UP) && y > 45)
    {
      y -= speed;
    }
    else if (IsKeyDown(KEY_DOWN) && y + height + 10 < GetScreenHeight())
    {
      y += speed;
    }
  }
};

Ball ball;
Paddle player;

int main()
{
  const int width = 1600;
  const int height = 900;
  Color bgColor = {205, 25, 74, 255};
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(width, height, "YoRu Pong");
  SetTargetFPS(120);
  ball.radius = 15;
  ball.x = width / 2;
  ball.y = height / 2;
  ball.speedX = 4;
  ball.speedY = 4;

  player.width = 25;
  player.height = 120;
  player.x = width - player.width - 10;
  player.y = height / 2 - player.height / 2;
  player.speed = 4;
  // int ballX = width / 2;
  // int ballY = height / 2;
  bool drag = false;
  Vector2 dragOffset = {0, 0};
  // Game loop
  while (!WindowShouldClose())
  {
    // Event handling
    Vector2 mousePosition = GetMousePosition();
    // Vector2 is a Built in Element provided by Raylib that takes two float values, x and y and draw 2D calculations
    bool closeButtonClicked = false;
    // if (IsKeyDown(KEY_RIGHT))
    // {
    //   ballX += 2;
    // }
    // else if (IsKeyDown(KEY_LEFT))
    // {
    //   ballX -= 2;
    // }
    // else if (IsKeyDown(KEY_UP))
    // {
    //   ballY -= 2;
    // }
    // else if (IsKeyDown(KEY_DOWN))
    // {
    //   ballY += 2;
    // }
    // if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))
    // {
    //   ballX += 1;
    //   ballY -= 1;
    // }
    // else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN))
    // {
    //   ballY += 1;
    //   ballX += 1;
    // }
    // else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))
    // {
    //   ballY -= 1;
    //   ballX -= 1;
    // }
    // else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN))
    // {
    //   ballY += 1;
    //   ballX -= 1;
    // }
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
      else if (mousePosition.y >= 0 && mousePosition.y <= 30)
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

    // (0,0).______________(5,0)
    //      |
    //      |
    //      |
    //      |
    // (0,5)|

    // Updating positions
    ball.move();
    player.move();

    // Drawing
    ClearBackground(RAYWHITE);

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("YoRu Pong", 50, 8, 20, DARKGRAY);

    // Draw close button
    DrawRectangle(1570, 0, 30, 30, bgColor);
    DrawText("X", 1577, 2, 30, WHITE);

    // Draw the ball
    // DrawCircle(ballX, ballY, 15, bgColor);
    Rectangle rec = {0, 0, 1600, 900};
    DrawRectangleLinesEx(rec, 5, bgColor);

    Rectangle rec1 = {0, 30, 30, 900};
    DrawRectangleLinesEx(rec1, 5, bgColor);

    Rectangle rec2 = {0, 0, 1600, 35};
    DrawRectangleLinesEx(rec2, 5, bgColor);
    // DrawRectangle(width - 35, height / 2 - 60, 25, 120, bgColor);
    ball.draw();
    player.draw();
    DrawLine(width / 2, 35, width / 2, height, bgColor);
    EndDrawing();

    if (closeButtonClicked)
    {
      break;
    }
  }

  CloseWindow();
  return 0;
}