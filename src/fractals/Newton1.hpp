#ifndef __NEWTON1_HPP__
#define __NEWTON1_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Newton1 : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // calculate newton fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    if (this->parameters.invert_y)
                    {
                        zy = this->parameters.min_y + (double)y * dy;
                    }

                    auto tmp = 1.0;

                    while (tmp > this->parameters.tolerance && ++t < this->parameters.escape_time_threshold)
                    {
                        auto oldx = zx;

                        auto oldy = zy;

                        auto zxx = zx * zx;

                        auto zyy = zy * zy;

                        tmp = (zxx + zyy) * (zxx + zyy);

                        auto tmp3 = 3.0 * tmp;

                        zx = ((zx + zx) * tmp + zxx - zyy) / tmp3;

                        zy = ((zy + zy) * (tmp - oldx)) / tmp3;

                        auto zx1 = zx - oldx;

                        auto zy1 = zy - oldy;

                        tmp = (zx1 * zx1 + zy1 * zy1);
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
        Newton1(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
