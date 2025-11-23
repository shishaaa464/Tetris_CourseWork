#pragma once
#include "include/raylib.h"
#include "Drawable.h"
#include "utils.h"

class Field : public Drawable {
public:
    static int cells[ROWS][COLS];
    static Color colors[ROWS][COLS];

    Field();

    void LockTetromino(const class Tetromino& t);
    int ClearLines();
    void Draw() override;
};
