#pragma once

struct Color{
    int r;
    int g;
    int b;

    Color(int r, int g, int b) : r(r), g(g), b(b) {
        
    };

    Color() : Color(0,0,0){
        
    };
};