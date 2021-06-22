#pragma once

#include <SDL.h>
#include <vector>

#include "Bullet.h"
#include "Vector2D.h"

class SDLGame;

class BlockWall {

private:   
    SDLGame* game_;
    Vector2D position_; // posicion del primer bloque (esquina superior izquierda)
    Vector2D size_;     // (columnas, filas)
    std::vector<std::vector<bool>> exists_;
    std::vector<std::vector<SDL_Rect>> blocks_;

public:
    BlockWall(){}
    ~BlockWall(){}

    BlockWall(Vector2D size, SDLGame* game = nullptr);

    void Render();
    void Update();

    const SDL_Rect GetBlock(int row, int column) { return blocks_[row][column]; }
};