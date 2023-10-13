#ifndef __JULIA_HPP__
#define __JULIA_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Julia : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // calculate julia set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    while ((zx * zx + zy * zy) <= this->parameters.escape_value_threshold * this->parameters.escape_value_threshold && (t < this->parameters.escape_time_threshold))
                    {
                        auto xtemp = zx * zx - zy * zy + this->parameters.cx;

                        zy = 2 * zx * zy + this->parameters.cy;

                        zx = xtemp;

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
        Julia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
