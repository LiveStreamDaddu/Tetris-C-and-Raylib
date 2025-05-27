#pragma once
#include<raylib.h>
#include<vector>

class Grid
{
    public:
        Grid();
        void Initialise();
        void Print();
        void Draw();
        bool IsCellOutside(int row , int column);
        bool IsCellEmpty(int row , int column);
        int ClearFullRows();
        int grid[20][10];
        
    private:
        int numRows;
        int numCols;
        int cellSize;
        bool IsRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row , int numRows);
        std::vector<Color> colors;
};