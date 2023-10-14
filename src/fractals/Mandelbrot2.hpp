#ifndef __MANDELBROT2_HPP__
#define __MANDELBROT2_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot2 : public Fractal::Base
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
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 1;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    // initial condition z0 (zx, zy)
                    auto zx = cx;

                    auto zy = cy;

                    // generate escape time fractal
                    while ((zx * zx + zy * zy) <= threshold && (t < this->parameters.escape_time_threshold))
                    {
                        auto xtemp = zx * zx - zy * zy + cx;

                        zy = (zx + zx) * zy + cy;

                        zx = xtemp;

                        t++;
                    }

                    // set escape-time color
                    if (t != this->parameters.escape_time_threshold)
                    {
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
                    else
                    {
                        this->grid[y][x] = 0;
                    }
                }
            }
        }

    public:
        Mandelbrot2(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
