#include "include/Field.h"
#include "include/Tetromino.h"
#include <cstring>

int Field::cells[ROWS][COLS] = {0};
Color Field::colors[ROWS][COLS] = {0};

Field::Field() {}

void Field::LockTetromino(const Tetromino& t) {
    for (int i = 0; i < t.size; i++)
    for (int j = 0; j < t.size; j++)
    {
        if (t.shape[i][j] && t.y + i >= 0)
        {
            if (t.y + i < ROWS && t.x + j >= 0 && t.x + j < COLS) {
                cells[t.y + i][t.x + j] = 1;
                colors[t.y + i][t.x + j] = t.color;
            }
        }
    }
}

int Field::ClearLines() {
    int cleared = 0;

    for (int i = ROWS - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < COLS; j++) {
            if (!cells[i][j]) {
                full = false;
                break;
            }
        }

        if (full) {
            cleared++;
            
            for (int k = i; k > 0; k--) {
                memcpy(cells[k], cells[k - 1], sizeof(cells[0]));
                memcpy(colors[k], colors[k - 1], sizeof(colors[0]));
            }
            
            memset(cells[0], 0, sizeof(cells[0]));
            
            i++;
        }
    }

    return cleared;
}

void Field::Draw() {
    for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
        if (cells[i][j])
            DrawRectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
                           BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                           colors[i][j]);
}