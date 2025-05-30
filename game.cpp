#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
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
    currentBlock.Draw(11 , 11);
    switch(nextBlock.id)
    {
        case 6 :
            nextBlock.Draw(255 , 290);
            break;
        case 7 : 
            nextBlock.Draw(255 , 280);
            break;
        default :
            nextBlock.Draw(270,270);
    }
}

void Game::HandleInput()
{
    int keypressed = GetKeyPressed();
    if(gameOver && keypressed != 0)
    {
        gameOver = false;
        Reset();
    }
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
        UpdateScore(0,1);
        break;
        case KEY_R:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0,-1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0,1);
            
        }
    }
    
}
void Game::MoveBlockRight()
{
    if(!gameOver)
    {
        currentBlock.Move(0,1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0,-1);
            
        
        }
    }
    
}
void Game::MoveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1,0);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
    
    
}
void Game::RotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
            LockBlock();
        }
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
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared , 0);
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


bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        if(grid.IsCellEmpty(item.row , item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialise();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
        case 1 :
            score += 100;
            break;
        case 2 :
            score += 300;
            break;
        case 3 : 
            score += 500;
            break;
        default :
            break;
    }
    score += moveDownPoints;
}
