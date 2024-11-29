#include "raylib.h"
#include "fileHand.h"
#include <fstream>

using namespace std;
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

void DrawSavedScores()
{
  ifstream scoreFile("score.txt");
  int scores[1000];
  int scoreCount = 0;

  if (scoreFile.is_open())
  {
    char line[1000];
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
        bool validScore = true;
        for (int j = i + 2; line[j] != '\0'; j++)
        {
          if (line[j] >= '0' && line[j] <= '9')
          {
            score = score * 10 + (line[j] - '0');
          }
          else
          {
            validScore = false;
            break;
          }
        }
        if (validScore)
        {
          scores[scoreCount] = score;
          scoreCount++;
        }
      }
    }
    scoreFile.close();
  }
  else
  {
    TraceLog(LOG_ERROR, "Unable to open score file");
    return;
  }

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
  Color bgColor = {205, 25, 74, 255};
  // Draw a background for the leaderboard
  // DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 150, 300, 250, Fade(bgColor, 0.3f));

  // Draw a border around the leaderboard
  DrawRectangleLines(GetScreenWidth() / 2 - 400, GetScreenHeight() / 2 - 400, 800, 700, bgColor);

  // Draw a title for the leaderboard
  DrawText("Leaderboard", GetScreenWidth() / 2 - MeasureText("Leaderboard", 100) / 2, GetScreenHeight() / 2 - 360, 100, bgColor);

  // Draw a decorative line under the title
  DrawLine(GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 260, GetScreenWidth() / 2 + 300, GetScreenHeight() / 2 - 260, bgColor);

  // Draw the top 5 scores
  DrawText("Top 5 Scores:", GetScreenWidth() / 2 - MeasureText("Top 5 Scores:", 80) / 2, GetScreenHeight() / 2 - 200, 80, bgColor);
  for (int i = 0; i < (scoreCount < 5 ? scoreCount : 5); i++)
  {
    DrawText(TextFormat("%d", scores[i]), GetScreenWidth() / 2 - MeasureText(TextFormat("%d", scores[i]), 70) / 2, GetScreenHeight() / 2 - 100 + i * 80, 70, bgColor);
  }
}