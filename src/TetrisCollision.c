#include "TetrisCollision.h"
#include "TetrisDefine.h"

extern int stage[];

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




























































































