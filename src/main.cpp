#include <iostream>
#include <fstream>
#include <cuda_runtime.h>

#include "vec3.h"
#include "sphere.h"
#include "camera.h"

extern __global__ void rayTraceKernel(
    Vec3*, Sphere*, int, int, int, Camera);

int main() {
    const int width = 800;
    const int height = 600;
    const int numPixels = width * height;

    Vec3* framebuffer;
    cudaMallocManaged(&framebuffer, numPixels * sizeof(Vec3));

    Sphere h_spheres[2] = {
        {{0, 0, -1}, 0.5f, {1, 0, 0}},
        {{0, -100.5f, -1}, 100, {0.8f, 0.8f, 0}}
    };

    Sphere* d_spheres;
    cudaMalloc(&d_spheres, 2 * sizeof(Sphere));
    cudaMemcpy(d_spheres, h_spheres, 2 * sizeof(Sphere), cudaMemcpyHostToDevice);

    Camera cam;
    cam.origin = Vec3(0, 0, 0);

    dim3 threads(16, 16);
    dim3 blocks((width + 15)/16, (height + 15)/16);

    rayTraceKernel<<<blocks, threads>>>(
        framebuffer, d_spheres, 2, width, height, cam);

    cudaDeviceSynchronize();

    std::ofstream out("output.ppm");
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < numPixels; i++) {
        int r = int(255.99 * framebuffer[i].x);
        int g = int(255.99 * framebuffer[i].y);
        int b = int(255.99 * framebuffer[i].z);
        out << r << " " << g << " " << b << "\n";
    }

    out.close();
    cudaFree(framebuffer);
    cudaFree(d_spheres);

    std::cout << "Rendered image saved to output.ppm\n";
}
