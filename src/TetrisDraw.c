#include "TetrisDraw.h"
#include "TetrisData.h"


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

void DrawArena(const int startOffsetX, const int startOffsetY)
{
    for (int y = 0; y < STAGE_HEIGHT; y++)
    {
        for (int x = 0; x < STAGE_WIDTH; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int stageColor = stage[offset]; 
            if (stage[offset] != 0)
            {
                DrawRectangle(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorsTypes[stageColor - 1]);
            }
            
            DrawRectangleLines(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
        }
    }
}






























































































