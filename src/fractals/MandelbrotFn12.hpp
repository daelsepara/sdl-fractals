#ifndef __MANDELBROT_FN12_HPP__
#define __MANDELBROT_FN12_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class MandelbrotFn12 : public Fractal::Base
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
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

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

                        Fractal::Multiply(zx, zy, cx, cy, zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

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
        MandelbrotFn12(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
