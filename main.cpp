#include "include/Game.h"
#include "include/raylib.h"

int main() {
    InitWindow(800, 700, "Tetris");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}