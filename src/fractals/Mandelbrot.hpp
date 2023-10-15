#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pre-calculate escape orbit
            auto threshold = this->parameters.escape_value_threshold * this->parameters.escape_value_threshold;

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 1;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    // generate escape time fractal
                    while ((zx * zx + zy * zy) <= threshold && (t < this->parameters.escape_time_threshold))
                    {
                        Fractal::Power(zx, zy, this->parameters.exponent);

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    // set escape-time color
                    if (t != this->parameters.escape_time_threshold)
                    {
                        this->grid[y][x] = t;
                    }
                    else
                    {
                        this->grid[y][x] = 0;
                    }
                }
            }
        }

    public:
        Mandelbrot(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
