#ifndef TETRIS_DELETE_LINES
#define TETRIS_DELETE_LINES
#include <string.h>
#include "TetrisData.h"

void CheckDeleteLines(Sound SFXDeleteLines, int* score, float* descentTime);

void UpdateScore(int* score, float* descentTime);

void ResetLines(const int startLineY);


#endif