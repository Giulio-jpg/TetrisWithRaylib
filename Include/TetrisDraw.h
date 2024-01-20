#ifndef TETRIS_DRAW
#define TETRIS_DRAW
#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 22
#define TETROMINO_SIZE 4

void DrawArena(const int startOffsetX, const int startOffsetY);
void DrawTetromino(const int startOffsetX, const int startOffsetY, const int tetrominoCellX, const int tetrominoCellY, const int *tetromino, const Color tetrominoColor);


#endif




