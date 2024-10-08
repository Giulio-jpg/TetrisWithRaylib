#include <time.h>
#include "TetrisCollision.h"
#include "TetrisCheckLines.h"
#include "TetrisDraw.h"
#include "TetrisData.h"

int main(int argc, char** argv, char** environ)
{
    const int windowWidth = 720;    
    const int windowHeight = 512;    

    const int arenaStartOffsetX = windowWidth / 2 - STAGE_WIDTH * TILE_SIZE / 2;
    const int arenaStartOffsetY = windowHeight / 2 - STAGE_HEIGHT * TILE_SIZE / 2;

    const int tetrominoStartCellX = STAGE_WIDTH / 2;
    const int tetrominoStartCellY = 0;

    time_t unixTime;
    time(&unixTime);
    SetRandomSeed(unixTime);

    int currentTetrominoCellX = tetrominoStartCellX;
    int currentTetrominoCellY = tetrominoStartCellY;

    int currentTetrominoType = GetRandomValue(0, TETROMINO_TYPES);
    int tetrominoRotation = 0;
    int tetrominoColor = GetRandomValue(1, COLORS);      // first color is for the stage

    float descentTimer = 1.0f;
    float tetrominoDescentTime = descentTimer;

    int score = 0;
    
    InitWindow(windowWidth, windowHeight, "Tetris");

    // Audio
    InitAudioDevice();

    // Music
    Music music = LoadMusicStream("TetrisMusic.mp3");
    music.looping = true;
    PlayMusicStream(music);

    // Sound effects
    Sound SFXDeleteLines = LoadSound("ClearLine.wav");         

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        descentTimer -= GetFrameTime();

        // INPUT
        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = tetrominoRotation;
            tetrominoRotation++;

            if (tetrominoRotation > 3)
            {
                tetrominoRotation = 0;
            }

            if (CheckCollision(currentTetrominoCellX, currentTetrominoCellY, tetrominoTypes[currentTetrominoType][tetrominoRotation]))
            {
                tetrominoRotation = lastRotation;
            }
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            // no need to check for overflow, it is blocked by the wall
            if(!CheckCollision(currentTetrominoCellX + 1, currentTetrominoCellY, tetrominoTypes[currentTetrominoType][tetrominoRotation]))
            {
                currentTetrominoCellX++;
            }
        }
        
        if (IsKeyPressed(KEY_LEFT))
        {
            // no need to check for overflow, it is blocked by the wall
            if(!CheckCollision(currentTetrominoCellX - 1, currentTetrominoCellY, tetrominoTypes[currentTetrominoType][tetrominoRotation]))
            {
                currentTetrominoCellX--;
            }
        }

        if (descentTimer <= 0 || IsKeyPressed(KEY_DOWN))
        {
            if (!CheckCollision(currentTetrominoCellX, currentTetrominoCellY + 1, tetrominoTypes[currentTetrominoType][tetrominoRotation]))
            {
                currentTetrominoCellY++;
                descentTimer = tetrominoDescentTime;
            }
            else
            {
                for (int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for (int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;
                        const int* tetromino = tetrominoTypes[currentTetrominoType][tetrominoRotation];

                        if (tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + currentTetrominoCellY) * STAGE_WIDTH + (x + currentTetrominoCellX);   

                            stage[offset_stage] = tetrominoColor + 1;
                        }
                    }
                }
                
                CheckDeleteLines(SFXDeleteLines, &score, &tetrominoDescentTime);

                // spawn new tetromino
                currentTetrominoCellX = tetrominoStartCellX;
                currentTetrominoCellY = tetrominoStartCellY;

                currentTetrominoType = GetRandomValue(0,  TETROMINO_TYPES);
                tetrominoRotation = 0;
                tetrominoColor = GetRandomValue(1, COLORS);
            }      
        }

        BeginDrawing();
        ClearBackground(RED);
        
        DrawArena(arenaStartOffsetX, arenaStartOffsetY);
        DrawTetromino(arenaStartOffsetX, arenaStartOffsetY, currentTetrominoCellX, currentTetrominoCellY, tetrominoTypes[currentTetrominoType][tetrominoRotation], colorsTypes[tetrominoColor]);

        DrawText(TextFormat("Score: %04i", score), SCORE_TEXT_X, SCORE_TEXT_Y, FONT_SIZE, WHITE);

        EndDrawing();
    }
    
    UnloadMusicStream(music);          
    CloseAudioDevice();     
    CloseWindow();
    return 0;
}