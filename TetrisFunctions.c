#include <string.h>
#include "TetrisFunctions.h"
#include "TetrisDefine.h"

extern int stage[];
extern int score;
extern float tetrominoDescentTime;
extern Sound SFXDeleteLines;

int CheckCollision(const int tetrominoCellX, const int tetrominoCellY, const int *tetromino)
{
    for (int y = 0; y < TETROMINO_SIZE; y++)
    {
        for (int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if (tetromino[offset] == 1)
            {
                const int stageOffset = (y + tetrominoCellY) * STAGE_WIDTH + (x + tetrominoCellX);   

                if (stage[stageOffset] != 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}


void UpdateScore()
{
    score += LINE_POINTS;

    if ((score % DESCENT_SPEED_INCREASE_THRESHOLD) == 0 && tetrominoDescentTime > MAX_DESCENT_TIME)
    {
        tetrominoDescentTime -= 0.1;
    }
}

void DrawTetromino(const int startOffsetX, const int startOffsetY, const int tetrominoCellX, const int tetrominoCellY, const int *tetromino, const Color tetrominoColor)
{
    for (int y = 0; y < TETROMINO_SIZE; y++)
    {
        for (int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;
            if (tetromino[offset] == 1)
            {
                DrawRectangle((x + tetrominoCellX) * TILE_SIZE + startOffsetX, (y + tetrominoCellY) * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, tetrominoColor);
            }
        }
    }
}

void ResetLines(int startLineY)
{
    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 0; x < STAGE_WIDTH - 1; x++)
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



void DeleteLines()
{
    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;
        for (int x = 0; x < STAGE_WIDTH; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
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
            UpdateScore();
        }
    }
}





























































































