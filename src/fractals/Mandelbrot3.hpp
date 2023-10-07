#ifndef __MANDELBROT3_HPP__
#define __MANDELBROT3_HPP__

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot3
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
                    // initial condition z0 (zx, zy)
                    auto zx = 0.0;
                    auto zy = 0.0;
                    auto xx = 0.0;
                    auto yy = 0.0;
                    // generate escape time fractal
                    while ((zx + zy) <= parameters.escape_value_threshold * parameters.escape_value_threshold && (t < parameters.escape_time_threshold))
                    {
                        yy = 2 * xx * yy + cy;
                        xx = zx - zy + cx;
                        zx = xx * xx;
                        zy = yy * yy;
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

        Mandelbrot3() {}
    };
}

#endif
