#pragma once
#include "ray.h"

struct Camera {
    Vec3 origin;

    __host__ __device__
    Ray getRay(float u, float v) const {
        Vec3 dir = Vec3(u, v, -1.0f);
        return {origin, normalize(dir)};
    }
};
