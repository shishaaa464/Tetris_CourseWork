#pragma once
#include "include/raylib.h"
#include "Drawable.h"

class Tetromino : public Drawable {
public:
    int shape[4][4];
    int size;
    int x, y;
    Color color;

    Tetromino();
    Tetromino(const int tmpl[4][4], int size, Color color);

    bool CheckCollision(int dx, int dy, int rotate);
    void Rotate();
    void Draw() override;
};
