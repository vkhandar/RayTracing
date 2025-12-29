#pragma once
#include "vec3.h"

struct Ray {
    Vec3 origin;
    Vec3 direction;

    __host__ __device__
    Vec3 at(float t) const {
        return origin + direction * t;
    }
};
