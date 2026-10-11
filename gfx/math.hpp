#pragma once

#include <cstdint>
#include <cstddef>
#include <cmath>
#include <algorithm>


struct vec2 {
    float x, y;

    vec2() : x(0), y(0){};
    vec2(float x, float y) : x(x), y(y){};
};


struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0){};
    vec3(float x, float y, float z) : x(x), y(y), z(z){};
};
