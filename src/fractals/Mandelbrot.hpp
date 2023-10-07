#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include <cmath>
#include <complex>

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot
    {
    private:
        Fractal::Parameters parameters;

    public:
        Fractal::Grid grid;

        void generate()
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factor
            auto dx = (double)(this->parameters.max_x - this->parameters.min_x) / (double)(this->parameters.x_pixels);

            auto dy = (double)(this->parameters.max_y - this->parameters.min_y) / (double)(this->parameters.y_pixels);

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    // calculate location (cx, cy) on complex plane
                    auto cx = this->parameters.min_x + (double)x * dx;
                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto cy = this->parameters.min_y + (double)(this->parameters.y_pixels - y - 1) * dy;
                    // generate escape time fractal
                    auto c = std::complex(cx, cy);
                    // initial condition (z0)
                    auto z = std::complex(0.0, 0.0);
                    // generate escape time fractal
                    while (abs(z) <= this->parameters.escape_value_threshold && (t < this->parameters.escape_time_threshold))
                    {
                        z = std::pow(z, this->parameters.exponent) + c;

                        t++;
                    }

                    // set escape-time color
                    this->grid[y][x] = t;
                }
            }
        }

        void generate(std::string image)
        {
            this->generate();

            if (image.length() > 0)
            {
                Fractal::SaveImage(this->grid, this->parameters, image);
            }
        }

        Mandelbrot(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
