#ifndef TETRIS_DELETE_LINES
#define TETRIS_DELETE_LINES
#include <string.h>
#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22

#define LINE_POINTS 100
#define DESCENT_SPEED_INCREASE_THRESHOLD 300
#define MAX_DESCENT_TIME 0.2


void DeleteLines();
void UpdateScore();
void ResetLines(const int startLineY);


#endif

