#pragma once
#include "math.hpp"
#include <cstdint>

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

    void bres_draw()
    {
        float x1 = a.x, y1 = a.y;
        float x2 = b.x, y2 = b.y;
        bool steep = (std::abs(y2 - y1) > std::abs(x2 - x1));
        // (or shallow when dy very small compared to dx)

        float dx = x2 - x1;
        float dy = y2 - y1;

        if (!steep)
        {
            float m = dy / dx;
            float c = (-m) * x1 + y1;
            uint8_t step = (m > 0) ? 1 : -1;
            uint16_t X = std::min(x1, x2);
            uint16_t Y = ((X == x1) ? y1 : y2);

            for (uint16_t i = X; i < std::max(x1, x2); i++)
            {
                float y = m * i + c;
                float d1 = y - Y;
                float d2 = Y + 1 - y;
                if (step == 1) {if ((d1 - d2) > 0){Y++;}}
                else {if (d2 - d1 > 50){Y--;}}
                s1.color[i + Y * WIDTH] = 255;
            }
        }
        else
        {
            float m = dx/dy;
            float c = (-m) * y1 + x1;
            uint8_t step = (m>0) ? 1: -1;
            uint16_t Y = std::min(y1, y2);
            uint16_t X = ((Y == y1) ? x1 : x2);

            for (uint16_t j = Y; j < std::max(y1, y2); j++)
            {
                float x = m*j + c;
                float d1 = x - X;
                float d2 = X+1 - x;
                if (step == 1){if (d1 - d2 >=0) {X++;}}
                else { if (d2 - d1 > 24 ) {X--;}}
                s1.color[X + j * WIDTH] = 255;
            }
        }
        return;
    }
};

// y = dy/dx (x-x1) + y1;
