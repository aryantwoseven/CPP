#pragma once
#include "math.hpp"

const uint16_t WIDTH = 512;
const uint16_t HEIGHT = 512;

struct Scene {
    uint32_t color[WIDTH * HEIGHT]{};
    Scene(){};
};

struct Renderer {
    Scene s1;

    vec2 a{50, 424};
    vec2 b{444, 90};

    void draw()
    {
        float thresh = 200.00;
        float Y = b.y - a.y;
        float X = b.x - a.x;
        float c = (a.x * b.y) - (a.y * b.x);

        for (size_t i = (std::min(a.x, b.x)); i < WIDTH; i++)
        {
            if (i > std::max(a.x, b.x)){break;}
            float xY = i * Y;
            for (size_t j = (std::min(a.y, b.y)); j< HEIGHT; j++)
            {
                if ( j > std::max(a.y, b.y)){break;}
                int lhs = std::abs((float) ( j * X - xY + c));
                if (lhs < thresh){ s1.color[i + j * WIDTH] = 255; }
            }
        }
        return;
    }
};




// y-y1 = m (x - x1)
// thresh > m(x - x1) * denom - (y-y1)*denom
// denom = (y - y1)
