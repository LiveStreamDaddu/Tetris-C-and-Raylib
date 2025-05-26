#include <iostream>
#include <raylib.h>
#include "game.h"

using namespace std;

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    srand(time(0));
    Game game = Game();
    Color dark_blue = {44,44,127,255};
    InitWindow(300 , 600 , "Tetris");
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(dark_blue);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

