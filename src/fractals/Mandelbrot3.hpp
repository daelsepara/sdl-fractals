#ifndef __MANDELBROT3_HPP__
#define __MANDELBROT3_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot3 : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factor
            auto dx = this->parameters.dx();
            auto dy = this->parameters.dy();
            ;

            // calculate mandelbrot set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    // initial condition z0 (zx, zy)
                    auto zx = 0.0;
                    auto zy = 0.0;
                    auto xx = 0.0;
                    auto yy = 0.0;

                    // generate escape time fractal
                    while ((zx + zy) <= this->parameters.escape_value_threshold * this->parameters.escape_value_threshold && (t < this->parameters.escape_time_threshold))
                    {
                        yy = 2 * xx * yy + cy;
                        xx = zx - zy + cx;
                        zx = xx * xx;
                        zy = yy * yy;
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
        Mandelbrot3(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
