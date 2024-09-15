#include "TetrisCheckLines.h"

#define LINE_POINTS 100
#define DESCENT_SPEED_INCREASE_THRESHOLD 300
#define MAX_DESCENT_TIME 0.2

void UpdateScore(int* score, float* descentTime)
{
    *score += LINE_POINTS;

    if ((*score % DESCENT_SPEED_INCREASE_THRESHOLD) == 0 && *descentTime > MAX_DESCENT_TIME)
    {
        *descentTime -= 0.1;
    }
}

void ResetLines(const int startLineY)
{
    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int offsetBelow = (y + 1) * STAGE_WIDTH + x;

            if (stage[offsetBelow] == 0 && stage[offset] > 0)
            {
                stage[offsetBelow] = stage[offset];
                stage[offset] = 0;
            }
        }
    }
}

void CheckDeleteLines(Sound SFXDeleteLines, int* score, float* descentTime)
{
    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
                // line has an empty position
                checkLine = 0;
                break;
            }
        }

        if (checkLine)
        {
            const int offset = y * STAGE_WIDTH + 1;

            memset(stage + offset, 0, (STAGE_WIDTH - 2) * sizeof(int));

            ResetLines(y);
            PlaySound(SFXDeleteLines);
            UpdateScore(score, descentTime);
        }
    }
}





























































































