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
            // set inputs/result filter
            this->map_filters();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pre-calculate shift value
            auto shift_value = this->parameters.shift_value * this->parameters.shift_value;

            // pointer to complex function
            auto ApplyFunction1 = Fractal::MapFunction(this->parameters.function);

            auto ApplyFunction2 = Fractal::MapFunction(this->parameters.function2);

            // calculate mandelbrot set
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
                        this->FilterInputs(zx, zy);

                        if (Fractal::Mag2(zx, zy) < shift_value)
                        {
                            ApplyFunction1(zx, zy);
                        }
                        else
                        {
                            ApplyFunction2(zx, zy);
                        }

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        this->FilterResult(zx, zy);

                        Fractal::Multiply(zx, zy, cx, cy, zx, zy);

                        if (Fractal::Mag2(zx, zy) > this->parameters.orbit)
                        {
                            break;
                        }

                        t++;
                    }

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        MandelbrotFn12(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
