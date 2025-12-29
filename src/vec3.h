#pragma once
#include <cmath>

struct Vec3 {
    float x, y, z;

    __host__ __device__
    Vec3() : x(0), y(0), z(0) {}

    __host__ __device__
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}

    __host__ __device__
    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    __host__ __device__
    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    __host__ __device__
    Vec3 operator*(float t) const {
        return Vec3(x * t, y * t, z * t);
    }
};

__host__ __device__
inline float dot(const Vec3& a, const Vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

__host__ __device__
inline Vec3 normalize(const Vec3& v) {
    float len = sqrtf(dot(v, v));
    return v * (1.0f / len);
}
