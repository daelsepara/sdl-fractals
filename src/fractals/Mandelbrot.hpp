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

            // calculate scaling factor
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pre-calculate orbit
            auto threshold = this->parameters.escape_value_threshold * this->parameters.escape_value_threshold;

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = 0.0;

                    auto zy = 0.0;

                    // generate escape time fractal
                    while ((zx * zx + zy * zy) <= threshold && (t < this->parameters.escape_time_threshold))
                    {
                        Fractal::Power(zx, zy, this->parameters.exponent);

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    // set escape-time color
                    if (this->parameters.log_coloring)
                    {
                        this->grid[y][x] = Fractal::LogColor(t, this->parameters.escape_time_threshold);
                    }
                    else if (this->parameters.normalized_coloring)
                    {
                        this->grid[y][x] = Fractal::NormalizedColor(t, this->parameters.escape_time_threshold);
                    }
                    else
                    {
                        this->grid[y][x] = Fractal::Clamp(t);
                    }
                }
            }
        }

    public:
        Mandelbrot(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
