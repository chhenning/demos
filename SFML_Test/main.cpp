// SFML_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


extern void run_mandelbrot();
extern void run_julia_set();
extern void run_perlin_noise__1D();
extern void run_perlin_noise__2D();
extern void run_flowfield();
extern void run_particle_system();
extern void simple_2D();


int main()
{
    simple_2D();
    
    return 0;
}
