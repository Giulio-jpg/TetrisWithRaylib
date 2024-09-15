# Tetris raylib 👾

This project was done to familiarise myself with the C language when I started studying it, so the idea was to recreate a very simple game.

The [raylib](https://www.raylib.com/) library was used to make it.

https://github.com/user-attachments/assets/162fa99c-5a2e-4b9d-832a-b0b1b265c142

## Tetromino and rotations

The stage and the Tetrominos were implemented using an array of integers where 0 is empty and 1 is a block

``` c                                                                        
int stage[] = 
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
```
Example of one tetromino:

``` c                                                                        
const int lTetromino0[] = 
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int lTetromino90[] = 
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino180[] = 
{
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino270[] = 
{
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
```

The tetrominos are then saved in an array that will contain all 7 types of tetrominos and their rotations:

``` c                                                                        
const int *tetrominoTypes[7][4] =
{
    {zTetromino0, zTetromino90, zTetromino180, zTetromino270},
    {sTetromino0, sTetromino90, sTetromino180, sTetromino270},
    {tTetromino0, tTetromino90, tTetromino180, tTetromino270},
    {iTetromino0, iTetromino90, iTetromino0, iTetromino90},
    {jTetromino0, jTetromino90, jTetromino180, jTetromino270},
    {lTetromino0, lTetromino90, lTetromino180, lTetromino270},
    {oTetromino, oTetromino, oTetromino, oTetromino},
};
```

So when I need to perform operations on the current tetromino(like checking collisions or drawing it), I will be able to access it via two variables, its type and its rotation:

``` c                                                                        
tetrominoTypes[currentTetrominoType][tetrominoRotation]
```

This approach is also useful for managing rotations, I only need to increase a value to get the new rotation:

``` c                                                                        
if (IsKeyPressed(KEY_SPACE))
{
    const int lastRotation = tetrominoRotation;
    tetrominoRotation++

    if (tetrominoRotation > 3)
    {
        tetrominoRotation = 0;
    }
    
    if (CheckCollision(currentTetrominoCellX, currentTetrominoCellY, tetrominoTypes[currentTetrominoType][tetrominoRotation]))
    {
        tetrominoRotation = lastRotation;
    }
}
```

A bit of a tricky part for me was implementing the deletion of a line when it is complete.

It is a recursive function, because if dropping the pieces fills another line, you have to delete that one too.

``` c                                                                        
void CheckDeleteLines(Sound SFXDeleteLines, int* score, float* descentTime)
{
    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
                // line has an empty position
                checkLine = 0;
                break;
            }
        }

        if (checkLine)
        {
            const int offset = y * STAGE_WIDTH + 1;

            memset(stage + offset, 0, (STAGE_WIDTH - 2) * sizeof(int));

            ResetLines(y);
            PlaySound(SFXDeleteLines);
            UpdateScore(score, descentTime);
        }
    }
}
```

My idea was to check all lines and if the line I'm checking has at least one 0 (an empty position), I can move on to the next line.

But when I delete a line, I must also drop all the pieces above that line, so I thought of making a loop that starts from the line I deleted and goes to the top of the stage:

``` c                                                                        
void ResetLines(const int startLineY)
{
    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int offsetBelow = (y + 1) * STAGE_WIDTH + x;

            if (stage[offsetBelow] == 0 && stage[offset] > 0)
            {
                stage[offsetBelow] = stage[offset];
                stage[offset] = 0;
            }
        }
    }
}
```

Calling this function each time I delete a line, I can delete several lines if I complete them together.

https://github.com/user-attachments/assets/6beb1235-304b-420d-8213-107e8719c0a5


## How to use

The direcotry has a .bat file to compile, once executed the bin folder will be created inside which you will find the executable.














