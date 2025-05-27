#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    bool gameOver;
    Grid grid;
    int score;

private:
    bool IsBlockOutside();
    bool BlockFits();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesCleared , int moveDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};