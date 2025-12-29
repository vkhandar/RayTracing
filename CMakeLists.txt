cmake_minimum_required(VERSION 3.18)
project(gpu_raytracer LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_executable(raytracer
    src/main.cpp
    src/raytracer.cu
)

set_target_properties(raytracer PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)
