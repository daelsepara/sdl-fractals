#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include <cmath>
#include <complex>

#include "parameters.hpp"
#include "utilities.hpp"

namespace Fractal
{
    class Mandelbrot
    {
    public:
        void generate(Fractal::Parameters parameters, std::string image)
        {
            // create complex plane (initialize grid)
            auto grid = Fractal::InitializeGrid(parameters);

            // calculate scaling factor
            auto dx = (double)(parameters.max_x - parameters.min_x) / (double)(parameters.x_pixels);
            auto dy = (double)(parameters.max_y - parameters.min_y) / (double)(parameters.y_pixels);

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    // calculate location (cx, cy) on complex plane
                    auto cx = parameters.min_x + (double)x * dx;
                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto cy = parameters.min_y + (double)(parameters.y_pixels - y - 1) * dy;
                    // generate escape time fractal
                    auto c = std::complex(cx, cy);
                    // initial condition (z0)
                    auto z = std::complex(0.0, 0.0);
                    // generate escape time fractal
                    while (abs(z) <= parameters.escape_value_threshold && (t < parameters.escape_time_threshold))
                    {
                        z = std::pow(z, parameters.exponent) + c;

                        t++;
                    }

                    // set escape-time color
                    grid[y][x] = t;
                }
            }

            if (image.length() > 0)
            {
                Fractal::SaveImage(grid, parameters, image);
            }
        }

        Mandelbrot() {}
    };
}

#endif