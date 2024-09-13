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

So when I draw them, I only need to specify the array index to get the tetromino:

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

The most complicated part was implementing the collisions



## How to use

The direcotry has a .bat file to compile, once executed the bin folder will be created inside which you will find the executable.














