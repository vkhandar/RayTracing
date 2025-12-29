#include "sphere.h"
#include "camera.h"

__global__
void rayTraceKernel(
    Vec3* framebuffer,
    Sphere* spheres,
    int numSpheres,
    int width,
    int height,
    Camera cam)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return;

    int idx = y * width + x;

    float u = (x - width / 2.0f) / width;
    float v = (y - height / 2.0f) / height;

    Ray ray = cam.getRay(u, v);

    Vec3 pixelColor(0.1f, 0.1f, 0.1f);
    float closest = 1e20f;

    for (int i = 0; i < numSpheres; i++) {
        float t;
        if (hitSphere(spheres[i], ray, t) && t < closest) {
            closest = t;
            pixelColor = spheres[i].color;
        }
    }

    framebuffer[idx] = pixelColor;
}
