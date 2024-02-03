#ifndef TETRIS_DATA
#define TETRIS_DATA
#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TETROMINO_SIZE 4
#define TILE_SIZE 22

extern int stage[];
extern const Color colorsTypes[9];
extern const int *tetrominoTypes[7][4];

#endif // TETRIS_DATA