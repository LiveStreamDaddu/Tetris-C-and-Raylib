#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
};

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock() , JBlock() , LBlock() , TBlock() , SBlock() , ZBlock() , OBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput()
{
    int keypressed = GetKeyPressed();
    switch(keypressed)
    {
        case KEY_A:
        MoveBlockLeft();
        break;
        case KEY_D:
        MoveBlockRight();
        break;
        case KEY_S:
        MoveBlockDown();
        break;
        case KEY_R:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    currentBlock.Move(0,-1);
    if(IsBlockOutside())
    {
        currentBlock.Move(0,1);
    }
}
void Game::MoveBlockRight()
{
    currentBlock.Move(0,1);
    if(IsBlockOutside())
    {
        currentBlock.Move(0,-1);
        
    }
}
void Game::MoveBlockDown()
{
    currentBlock.Move(1,0);
    if(IsBlockOutside())
    {
        currentBlock.Move(-1,0);
        LockBlock();
    }
}
void Game::RotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside())
    {
        currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        if(grid.IsCellOutside(item.row , item.column))
        {
            return true;
        }
    }
    return false;
}


