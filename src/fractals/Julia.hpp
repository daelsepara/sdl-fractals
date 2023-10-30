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
            // set inputs/result filter
            this->map_filters();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pointer to complex function
            auto ApplyFunction = Fractal::MapFunction(this->parameters.function);

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
                    while (Fractal::Mag2(zx, zy) <= this->parameters.escape_value && t < this->parameters.max_iterations)
                    {
                        this->FilterInputs(zx, zy);

                        ApplyFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        this->FilterResult(zx, zy);

                        zx += this->parameters.cx;

                        zy += this->parameters.cy;

                        t++;
                    }

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        Julia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
