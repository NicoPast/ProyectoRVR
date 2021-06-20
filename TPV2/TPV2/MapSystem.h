#pragma once

#include <SDL.h>
#include <cstdint>

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class MapSystem : public System{
public:
    MapSystem();
    virtual ~MapSystem();
    void init() override;
    void update() override;
    void recieve(const msg::Message& msg) override;
private:
    double width;
    double height;
    int rows;
    int cols;
};