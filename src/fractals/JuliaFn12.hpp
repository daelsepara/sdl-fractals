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
                        if (this->parameters.absolute_inputs)
                        {
                            Fractal::Absolute(zx, zy);
                        }

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

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        JuliaFn12(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
