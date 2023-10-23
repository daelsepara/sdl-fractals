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

            // pre-calculate escape orbit
            auto threshold = this->parameters.orbit * this->parameters.orbit;

            // pointer to complex function
            auto ComplexFunction = Fractal::MapFunction(this->parameters.function);

            // calculate julia set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    // generate escape time fractal
                    while (t < this->parameters.max_iterations)
                    {
                        if (this->parameters.absolute_inputs)
                        {
                            Fractal::Absolute(zx, zy);
                        }

                        ComplexFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        if (this->parameters.absolute_result)
                        {
                            Fractal::Absolute(zx, zy);
                        }

                        zx += this->parameters.cx;

                        zy += this->parameters.cy;

                        if (Fractal::Mag2(zx, zy) > threshold)
                        {
                            break;
                        }

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
        Julia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
