#include "BlockWall.h"
#include "SDLGame.h"


BlockWall::BlockWall(Vector2D size, SDLGame* game) : size_(size), game_(game)
{
    // centro - (mitad tamano * tamano bloque) - mitad margen * (numerobloques -1)
    position_ = Vector2D((SCREEN_WIDTH * 0.5f) - (WALL_SIZE * size.getX() * 0.5f) - WALL_MARGIN * (size_.getX() - 1) * 0.5f, 
                        (SCREEN_HEIGHT * 0.5f) - (WALL_SIZE * size.getY() * 0.5f) - WALL_MARGIN * (size_.getY() - 1) * 0.5f);

    exists_ = std::vector<std::vector<bool>>(size_.getY(), std::vector<bool>(size_.getX(), true));
    blocks_ = std::vector<std::vector<SDL_Rect>>(size_.getY(), std::vector<SDL_Rect>(size_.getX(), {0, 0, WALL_SIZE, WALL_SIZE}));

    for(int i = 0; i < blocks_.size(); i++)
    {
        for(int j = 0; j< blocks_[i].size(); j++)
        {
            blocks_[i][j].x = position_.getX() + j * (WALL_SIZE + WALL_MARGIN);
            blocks_[i][j].y = position_.getY() + i * (WALL_SIZE + WALL_MARGIN);
        }
    }
}

void BlockWall::Update()
{

}

void BlockWall::Render()
{
    for(int i = 0; i < blocks_.size(); i++)
    {
        for(int j = 0; j< blocks_[i].size(); j++)
        {
            if(exists_[i][j])
            {
                SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
                SDL_RenderFillRect( game_->getRenderer(), &blocks_[i][j] );
            }
        }
    }
}