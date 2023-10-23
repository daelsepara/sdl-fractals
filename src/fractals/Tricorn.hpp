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

                    while (Fractal::Mag2(zx, zy) < this->parameters.orbit && t < this->parameters.max_iterations)
                    {
                        if (this->parameters.absolute_inputs)
                        {
                            Fractal::Absolute(zx, zy);
                        }

                        auto xtemp = zx * zx - zy * zy;

                        zy = -(zx + zx) * zy;

                        zx = xtemp;

                        if (this->parameters.absolute_result)
                        {
                            Fractal::Absolute(zx, zy);
                        }

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    // set escape-time color
                    if (t != this->parameters.max_iterations)
                    {
                        if (std::abs(zx) < this->parameters.bailout || std::abs(zy) < this->parameters.bailout)
                        {
                            this->grid[y][x] = this->parameters.bailout_color;
                        }
                        else
                        {
                            this->grid[y][x] = t;
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
