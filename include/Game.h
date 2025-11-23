#pragma once
#include "Tetromino.h"
#include "Field.h"

class Game {
private:
    Field field;
    Tetromino current;
    Tetromino next;

    float dropTimer;
    int score;
    bool gameOver;

    Tetromino RandomTetromino();

public:
    Game();

    void Update();
    void Draw();
    bool IsGameOver() const { 
        return gameOver; 
    }
};