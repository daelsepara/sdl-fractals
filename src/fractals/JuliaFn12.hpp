#ifndef __JULIA_FN12_HPP__
#define __JULIA_FN12_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class JuliaFn12 : public Fractal::Base
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

            // pre-calculate shift value
            auto shift_value = this->parameters.shift_value * this->parameters.shift_value;

            // pointer to complex function
            auto ComplexFunction1 = Fractal::MapFunction(this->parameters.function);
            auto ComplexFunction2 = Fractal::MapFunction(this->parameters.function2);

            // calculate julia set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    auto t = 0;

                    // generate escape time fractal
                    while (t < this->parameters.max_iterations)
                    {
                        if (Fractal::Mag2(zx, zy) < shift_value)
                        {
                            ComplexFunction1(zx, zy);
                        }
                        else
                        {
                            ComplexFunction2(zx, zy);
                        }

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        Fractal::Multiply(zx, zy, this->parameters.cx, this->parameters.cy, zx, zy);

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
        JuliaFn12(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
