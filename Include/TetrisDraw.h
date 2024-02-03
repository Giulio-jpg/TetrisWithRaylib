#ifndef TETRIS_DRAW
#define TETRIS_DRAW
#include "TetrisData.h"


void DrawArena(const int startOffsetX, const int startOffsetY);
void DrawTetromino(const int startOffsetX, const int startOffsetY, const int tetrominoCellX, const int tetrominoCellY, const int *tetromino, const Color tetrominoColor);


#endif




