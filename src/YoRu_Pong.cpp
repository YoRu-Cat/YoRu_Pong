#include <raylib.h>
#include <fstream>
using namespace std;

int player1Score = 0;
bool isGameOver = false;
bool scoreSaved = false; // Add this flag

// ball ka content
float ballX, ballY;
int ballSpeedX, ballSpeedY;
int ballRadius;

// player ka content
float paddleX, paddleY;
float paddleWidth, paddleHeight;
int paddleSpeed;

void DrawBall()
{
  Color bgColor = {205, 25, 74, 255};
  DrawCircle(ballX, ballY, ballRadius, bgColor);
}

void MoveBall()
{
  ballX += ballSpeedX;
  ballY += ballSpeedY;
  if (ballY + ballRadius >= GetScreenHeight() || ballY - ballRadius <= 30)
  {
    ballSpeedY *= -1;
  }
  if (ballX + ballRadius >= GetScreenWidth())
  {
    isGameOver = true;
  }
  else if (ballX - ballRadius <= 30)
  {
    player1Score++;
    ballSpeedX *= -1;
  }
}

void ResetBall()
{
  ballX = GetScreenWidth() / 2;
  ballY = GetScreenHeight() / 2;
  ballSpeedX = 5;
  ballSpeedY = 5;
}

void DrawPaddle()
{
  Color bgColor = {205, 25, 74, 255};
  DrawRectangle(paddleX, paddleY, paddleWidth, paddleHeight, bgColor);
}

void MovePaddle()
{
  if (IsKeyDown(KEY_UP) && paddleY > 45)
  {
    paddleY -= paddleSpeed;
  }
  else if (IsKeyDown(KEY_DOWN) && paddleY + paddleHeight + 10 < GetScreenHeight())
  {
    paddleY += paddleSpeed;
  }
}

void ResetPaddle()
{
  paddleY = GetScreenHeight() / 2 - paddleHeight / 2;
}

void ResetGame()
{
  isGameOver = false;
  scoreSaved = false; // Reset the flag
  player1Score = 0;
  ResetBall();
  ResetPaddle();
}

void SaveScore(int score)
{
  ofstream scoreFile("score.txt", ios::app);
  if (scoreFile.is_open())
  {
    scoreFile << "Recent Score: " << score << endl;
    scoreFile.close();
  }
  else
  {
    TraceLog(LOG_ERROR, "Unable to open score file");
  }
}
// void SortAndDisplayTopScores()
// {
//   ifstream scoreFile("score.txt");
//   int scores[100];
//   int scoreCount = 0;
//   string line;

//   if (scoreFile.is_open())
//   {
//     while (getline(scoreFile, line))
//     {
//       size_t pos = line.find("Recent Score: ");
//       if (pos != string::npos)
//       {
//         int score = stoi(line.substr(pos + 14));
//         scores[scoreCount++] = score;
//       }
//     }
//     scoreFile.close();
//   }
//   else
//   {
//     TraceLog(LOG_ERROR, "Unable to open score file");
//     return;
//   }

//   for (int i = 0; i < scoreCount - 1; i++)
//   {
//     for (int j = 0; j < scoreCount - i - 1; j++)
//     {
//       if (scores[j] > scores[j + 1])
//       {
//         int temp = scores[j];
//         scores[j] = scores[j + 1];
//         scores[j + 1] = temp;
//       }
//     }
//   }

//   int displayCount = scoreCount < 10 ? scoreCount : 10;
//   for (int i = 0; i < displayCount; i++)
//   {
//     DrawText(TextFormat("%i", scores[i]), GetScreenWidth() / 1.2, GetScreenHeight() / 1.2 - 40 - i * 20, 20, DARKGRAY);
//   }
// }
void DrawSavedScores()
{
  ifstream scoreFile("score.txt");
  int scores[100];
  int scoreCount = 0;

  if (scoreFile.is_open())
  {
    char line[256];
    while (scoreFile.getline(line, sizeof(line)))
    {
      int i = 0;
      while (line[i] != ':' && line[i] != '\0')
      {
        i++;
      }
      if (line[i] == ':')
      {
        int score = 0;
        for (int j = i + 2; line[j] != '\0'; j++)
        {
          if (line[j] >= '0' && line[j] <= '9')
          {
            score = score * 10 + (line[j] - '0');
          }
        }
        scores[scoreCount] = score;
        scoreCount++;
      }
    }
    scoreFile.close();
  }
  else
  {
    TraceLog(LOG_ERROR, "Unable to open score file");
    return;
  }

  // Bubble sort scores in descending order
  for (int i = 0; i < scoreCount - 1; i++)
  {
    for (int j = 0; j < scoreCount - i - 1; j++)
    {
      if (scores[j] < scores[j + 1])
      {
        int temp = scores[j];
        scores[j] = scores[j + 1];
        scores[j + 1] = temp;
      }
    }
  }

  // Draw top 5 scores
  DrawText("Top 5 Scores:", GetScreenWidth() / 1.2, GetScreenHeight() / 1.2 - 22, 20, DARKGRAY);
  for (int i = 0; i < (scoreCount < 5 ? scoreCount : 5); i++)
  {
    DrawText(TextFormat("%d", scores[i]), GetScreenWidth() / 1.2, GetScreenHeight() / 1.2 + i * 22, 20, DARKGRAY);
  }
}

int main()
{
  int width = 1600;
  const int height = 900;
  Color bgColor = {205, 25, 74, 255};
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(width, height, "YoRu Pong");
  SetTargetFPS(120);

  ballRadius = 20;
  ballX = width / 2;
  ballY = height / 2;
  ballSpeedX = 5;
  ballSpeedY = 5;

  paddleWidth = 25;
  paddleHeight = 120;
  paddleX = width - paddleWidth - 10;
  paddleY = height / 2 - paddleHeight / 2;
  paddleSpeed = 6;

  bool drag = false;
  Vector2 dragOffset = {0, 0};

  while (!WindowShouldClose())
  {
    Vector2 mousePosition = GetMousePosition();
    bool closeButtonClicked = false;
    bool minimizeButtonClicked = false;
    bool maximizeButtonClicked = false;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (mousePosition.x >= 1565 && mousePosition.x <= 1600 &&
          mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        closeButtonClicked = true;
      }
      else if (mousePosition.x >= 1530 && mousePosition.x <= 1565 &&
               mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        minimizeButtonClicked = true;
      }
      else if (mousePosition.x >= 1495 && mousePosition.x <= 1530 &&
               mousePosition.y >= 0 && mousePosition.y <= 20)
      {
        maximizeButtonClicked = true;
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

    if (isGameOver)
    {
      if (!scoreSaved)
      {
        SaveScore(player1Score);
        scoreSaved = true; // Set the flag to true after saving the score
      }
    }
    else
    {
      MoveBall();
      MovePaddle();
    }

    if (isGameOver && IsKeyPressed(KEY_ENTER))
    {
      ResetGame();
    }

    if (CheckCollisionCircleRec({ballX, ballY}, ballRadius, {paddleX, paddleY, paddleWidth, paddleHeight}))
    {
      ballSpeedX *= -1;
    }
    ClearBackground(RAYWHITE);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1600, 35, bgColor);
    DrawText("YoRu Pong", 50, 8, 20, RAYWHITE);
    DrawText("V-2.1.2.", 200, 8, 20, RAYWHITE);

    Rectangle rec = {0, 0, 1600, 900};
    DrawRectangleLinesEx(rec, 5, bgColor);

    Rectangle rec1 = {0, 30, 30, 900};
    DrawRectangleLinesEx(rec1, 5, bgColor);

    Rectangle rec2 = {1568, 2, 30, 30};
    DrawRectangleLinesEx(rec2, 1, RAYWHITE);
    DrawText("X", 1574, 3, 30, WHITE);

    Rectangle rec3 = {1533, 2, 30, 30};
    DrawRectangleLinesEx(rec3, 1, RAYWHITE);
    DrawText("-", 1542, 4, 30, WHITE);

    Rectangle rec4 = {1498, 2, 30, 30};
    DrawRectangleLinesEx(rec4, 1, RAYWHITE);
    DrawText("O", 1504, 3, 30, WHITE);

    DrawCircleLines(width / 2, height / 2, 100, bgColor);

    DrawBall();
    DrawPaddle();
    DrawText("Score:", width / 1.2, height / 10, 50, bgColor);
    DrawText(TextFormat("%i", player1Score), width / 1.2, height / 6, 60, bgColor);
    DrawText("FPS:", width / 8, height / 10, 50, bgColor);
    DrawText(TextFormat("%i", GetFPS()), width / 8, height / 6, 60, bgColor);
    DrawLine(width / 2, 35, width / 2, height, bgColor);

    if (isGameOver)
    {
      DrawRectangle(width / 2 - 200, height / 2 - 75, 400, 150, bgColor);
      DrawText("Game Over", width / 2 - 100, height / 2 - 30, 40, RAYWHITE);
      DrawText("Press Enter to Restart", width / 2 - 120, height / 2 + 20, 20, RAYWHITE);
    }

    DrawSavedScores();

    EndDrawing();

    if (closeButtonClicked)
    {
      break;
    }
    if (minimizeButtonClicked || IsKeyPressed(KEY_F10))
    {
      MinimizeWindow();
    }
    if (maximizeButtonClicked || IsKeyPressed(KEY_F11))
    {
      ToggleFullscreen();
    }
  }

  CloseWindow();
  return 0;
}
