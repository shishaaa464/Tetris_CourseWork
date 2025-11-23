#include "include/Game.h"
#include "include/utils.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
    srand(time(NULL));
    current = RandomTetromino();
    next = RandomTetromino();
    dropTimer = 0;
    score = 0;
    gameOver = false;
}

Tetromino Game::RandomTetromino() {
    int id = rand() % 7;
    return Tetromino(templates[id], 4, templateColors[id]);
}

void Game::Update() {
    if (gameOver) {
        if (IsKeyPressed(KEY_R)) {
            gameOver = false;
            score = 0;
            dropTimer = 0;
            
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    Field::cells[i][j] = 0;
                }
            }
            
            current = RandomTetromino();
            next = RandomTetromino();
        }
        return;
    }

    dropTimer += GetFrameTime();

    if (IsKeyPressed(KEY_LEFT) && !current.CheckCollision(-1, 0, 0))
        current.x--;

    if (IsKeyPressed(KEY_RIGHT) && !current.CheckCollision(1, 0, 0))
        current.x++;

    if (IsKeyPressed(KEY_DOWN) && !current.CheckCollision(0, 1, 0)) {
        current.y++;
        score += 1;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        int dropDistance = 0;
        while (!current.CheckCollision(0, 1, 0)) {
            current.y++;
            dropDistance++;
        }
        score += dropDistance * 2;
        field.LockTetromino(current);
        score += 10;
        
        int linesCleared = field.ClearLines();
        if (linesCleared > 0) {
            int linePoints = 0;
            switch (linesCleared) {
                case 1: linePoints = 100; break;
                case 2: linePoints = 300; break;
                case 3: linePoints = 500; break;
                case 4: linePoints = 800; break;
            }
            score += linePoints;
        }
        
        current = next;
        next = RandomTetromino();
        
        if (current.CheckCollision(0, 0, 0)) {
            gameOver = true;
        }
        
        dropTimer = 0;
    }

    if (IsKeyPressed(KEY_UP))
        current.Rotate();

    if (dropTimer > 0.5f) {
        dropTimer = 0;

        if (!current.CheckCollision(0, 1, 0)) {
            current.y++;
        } else {
            field.LockTetromino(current);
            score += 10;
            
            int linesCleared = field.ClearLines();
            if (linesCleared > 0) {
                int linePoints = 0;
                switch (linesCleared) {
                    case 1: linePoints = 100; break;
                    case 2: linePoints = 300; break;
                    case 3: linePoints = 500; break;
                    case 4: linePoints = 800; break;
                }
                score += linePoints;
            }

            current = next;
            next = RandomTetromino();
            
            if (current.CheckCollision(0, 0, 0)) {
                gameOver = true;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    const int fieldWidth = COLS * BLOCK_SIZE;
    const int fieldHeight = ROWS * BLOCK_SIZE;
    const int offsetX = (GetScreenWidth() - (fieldWidth + 300)) / 2;
    const int offsetY = (GetScreenHeight() - fieldHeight) / 2;

    DrawRectangle(offsetX - 5, offsetY - 5, fieldWidth + 10, fieldHeight + 10, DARKGRAY);
    DrawRectangle(offsetX, offsetY, fieldWidth, fieldHeight, BLACK);

    for (int i = 0; i <= ROWS; i++) {
        DrawLine(offsetX, offsetY + i * BLOCK_SIZE, 
                 offsetX + fieldWidth, offsetY + i * BLOCK_SIZE, 
                 Color{50, 50, 50, 255});
    }
    for (int j = 0; j <= COLS; j++) {
        DrawLine(offsetX + j * BLOCK_SIZE, offsetY,
                 offsetX + j * BLOCK_SIZE, offsetY + fieldHeight,
                 Color{50, 50, 50, 255});
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (Field::cells[i][j]) {
                DrawRectangle(offsetX + j * BLOCK_SIZE, 
                             offsetY + i * BLOCK_SIZE,
                             BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                             Field::colors[i][j]);
                
                DrawRectangle(offsetX + j * BLOCK_SIZE, 
                             offsetY + i * BLOCK_SIZE,
                             BLOCK_SIZE - 1, 2,
                             Color{255, 255, 255, 100});
                DrawRectangle(offsetX + j * BLOCK_SIZE, 
                             offsetY + i * BLOCK_SIZE,
                             2, BLOCK_SIZE - 1,
                             Color{255, 255, 255, 100});
                
                DrawRectangle(offsetX + j * BLOCK_SIZE, 
                             offsetY + (i + 1) * BLOCK_SIZE - 2,
                             BLOCK_SIZE - 1, 2,
                             Color{0, 0, 0, 100});
                DrawRectangle(offsetX + (j + 1) * BLOCK_SIZE - 2, 
                             offsetY + i * BLOCK_SIZE,
                             2, BLOCK_SIZE - 1,
                             Color{0, 0, 0, 100});
            }
        }
    }

    if (!gameOver) {
        for (int i = 0; i < current.size; i++) {
            for (int j = 0; j < current.size; j++) {
                if (current.shape[i][j] && current.y + i >= 0) {
                    int xPos = offsetX + (current.x + j) * BLOCK_SIZE;
                    int yPos = offsetY + (current.y + i) * BLOCK_SIZE;
                    
                    DrawRectangle(xPos, yPos, BLOCK_SIZE - 1, BLOCK_SIZE - 1, current.color);
                    
                    DrawRectangle(xPos, yPos, BLOCK_SIZE - 1, 2, Color{255, 255, 255, 150});
                    DrawRectangle(xPos, yPos, 2, BLOCK_SIZE - 1, Color{255, 255, 255, 150});
                    
                    DrawRectangle(xPos, yPos + BLOCK_SIZE - 2, BLOCK_SIZE - 1, 2, Color{0, 0, 0, 150});
                    DrawRectangle(xPos + BLOCK_SIZE - 2, yPos, 2, BLOCK_SIZE - 1, Color{0, 0, 0, 150});
                }
            }
        }
    }

    int panelX = offsetX + fieldWidth + 20;
    int panelY = offsetY;

    DrawRectangle(panelX, panelY, 250, 100, Color{40, 40, 40, 255});
    DrawRectangleLines(panelX, panelY, 250, 100, GOLD);
    DrawText("SCORE", panelX + 10, panelY + 10, 24, GOLD);
    DrawText(TextFormat("%08d", score), panelX + 10, panelY + 40, 32, WHITE);

    if (!gameOver) {
        int nextPanelY = panelY + 120;
        DrawRectangle(panelX, nextPanelY, 250, 180, Color{40, 40, 40, 255});
        DrawRectangleLines(panelX, nextPanelY, 250, 180, GOLD);
        DrawText("NEXT", panelX + 10, nextPanelY + 10, 24, GOLD);

        int previewX = panelX + (250 - next.size * BLOCK_SIZE) / 2;
        int previewY = nextPanelY + 60;

        for (int i = 0; i < next.size; i++) {
            for (int j = 0; j < next.size; j++) {
                if (next.shape[i][j]) {
                    DrawRectangle(previewX + j * BLOCK_SIZE, 
                                 previewY + i * BLOCK_SIZE,
                                 BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                                 next.color);
                }
            }
        }

        int controlsY = nextPanelY + 200;
        DrawRectangle(panelX, controlsY, 250, 120, Color{40, 40, 40, 255});
        DrawRectangleLines(panelX, controlsY, 250, 120, BLUE);
        DrawText("CONTROLS", panelX + 10, controlsY + 10, 20, BLUE);
        DrawText("<- -> : Move", panelX + 20, controlsY + 35, 16, LIGHTGRAY);
        DrawText("Up : Rotate", panelX + 20, controlsY + 55, 16, LIGHTGRAY);
        DrawText("Down : Soft Drop", panelX + 20, controlsY + 75, 16, LIGHTGRAY);
        DrawText("SPACE : Hard Drop", panelX + 20, controlsY + 95, 16, LIGHTGRAY);
    }

    if (gameOver) {
        DrawRectangle(offsetX, offsetY, fieldWidth, fieldHeight, Color{0, 0, 0, 200});
        
        DrawText("GAME OVER", 
                 offsetX + fieldWidth/2 - MeasureText("GAME OVER", 40)/2, 
                 offsetY + fieldHeight/2 - 50, 
                 40, RED);
        
        DrawText("FINAL SCORE:", 
                 offsetX + fieldWidth/2 - MeasureText("FINAL SCORE:", 24)/2, 
                 offsetY + fieldHeight/2, 
                 24, WHITE);
        
        DrawText(TextFormat("%d", score), 
                 offsetX + fieldWidth/2 - MeasureText(TextFormat("%d", score), 36)/2, 
                 offsetY + fieldHeight/2 + 30, 
                 36, YELLOW);
        
        DrawText("Press R to restart", 
                 offsetX + fieldWidth/2 - MeasureText("Press R to restart", 20)/2, 
                 offsetY + fieldHeight/2 + 80, 
                 20, GREEN);
    }

    EndDrawing();
}