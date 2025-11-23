#include "include/Tetromino.h"
#include "include/utils.h"
#include "include/Field.h"
#include <cstring>

Tetromino::Tetromino() {
    memset(shape, 0, sizeof(shape));
    size = 0;
    x = 0;
    y = 0;
    color = WHITE;
}

Tetromino::Tetromino(const int tmpl[4][4], int size, Color color) {
    this->size = size;
    this->color = color;
    memset(shape, 0, sizeof(shape));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            shape[i][j] = tmpl[i][j];
    
    x = COLS / 2 - 2;
    y = 0;
}

bool Tetromino::CheckCollision(int dx, int dy, int rotate) {
    int temp[4][4] = {0};
    
    if (rotate) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                temp[j][size - 1 - i] = shape[i][j];
    }

    for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
        int block = rotate ? temp[i][j] : shape[i][j];
        if (!block) continue;

        int nx = x + j + dx;
        int ny = y + i + dy;

        if (nx < 0 || nx >= COLS) return true;
        if (ny >= ROWS) return true;
        
        if (ny >= 0 && Field::cells[ny][nx]) return true;
    }
    return false;
}

void Tetromino::Rotate() {
    if (CheckCollision(0, 0, 1)) return;
    
    int temp[4][4] = {0};
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            temp[j][size - 1 - i] = shape[i][j];

    memcpy(shape, temp, sizeof(temp));
}

void Tetromino::Draw() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (shape[i][j] && y + i >= 0)
                DrawRectangle((x + j) * BLOCK_SIZE,
                              (y + i) * BLOCK_SIZE,
                              BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                              color);
}