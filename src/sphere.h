#pragma once
#include "vec3.h"
#include "ray.h"

struct Sphere
{
    Vec3 center;
    float radius;
    Vec3 color;
};

__device__ inline bool hitSphere(const Sphere &s, const Ray &r, float &t)
{
    Vec3 oc = r.origin - s.center;
    float a = dot(r.direction, r.direction);
    float b = 2.0f * dot(oc, r.direction);
    float c = dot(oc, oc) - s.radius * s.radius;
    float disc = b * b - 4 * a * c;

    if (disc < 0)
        return false;
    t = (-b - sqrtf(disc)) / (2.0f * a);
    return t > 0.001f;
}
