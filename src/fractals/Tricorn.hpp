#ifndef __TRICORN_HPP__
#define __TRICORN_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Tricorn : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();
            ;

            // calculate tricorn fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    while ((zx * zx + zy * zy) < this->parameters.escape_value_threshold && t < this->parameters.escape_time_threshold)
                    {
                        auto xtemp = zx * zx - zy * zy + cx;

                        zy = -(zx + zx) * zy + cy;

                        zx = xtemp;

                        t++;
                    }

                    if (t != this->parameters.escape_time_threshold)
                    {
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
                    else
                    {
                        this->grid[y][x] = this->parameters.inside_color;
                    }
                }
            }
        }

    public:
        Tricorn(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
