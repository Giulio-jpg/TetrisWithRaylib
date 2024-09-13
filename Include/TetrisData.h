#ifndef TETRIS_DATA
#define TETRIS_DATA
#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TETROMINO_SIZE 4
#define TILE_SIZE 22     // in pixel

#define TETROMINO_TYPES 6
#define COLORS 8
#define SCORE_TEXT_X 550
#define SCORE_TEXT_Y 50
#define FONT_SIZE 20

extern int stage[];
extern const Color colorsTypes[9];
extern const int *tetrominoTypes[7][4];

#endif // TETRIS_DATA