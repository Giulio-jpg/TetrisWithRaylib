#include "raylib.h"

void UpdateScore();
int CheckCollision(const int tetrominoCellX, const int tetrominoCellY, const int *tetromino);
void DrawArena(const int startOffsetX, const int startOffsetY);
void DrawTetromino(const int startOffsetX, const int startOffsetY, const int tetrominoCellX, const int tetrominoCellY, const int *tetromino, const Color tetrominoColor);
void ResetLines(int startLineY);
void DeleteLines();






