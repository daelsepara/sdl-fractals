#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot : public Fractal::Base
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

            // pre-calculate escape orbit
            auto threshold = this->parameters.orbit * this->parameters.orbit;

            // pointer to complex function
            auto ApplyFunction = Fractal::MapFunction(this->parameters.function);

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate cy coordinate on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate cx coordinate on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = 0.0;

                    auto zy = 0.0;

                    // generate escape time fractal
                    while (t < this->parameters.max_iterations)
                    {
                        this->FilterInputs(zx, zy);

                        ApplyFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        this->FilterResult(zx, zy);

                        zx += cx;

                        zy += cy;

                        if (Fractal::Mag2(zx, zy) > threshold)
                        {
                            break;
                        }

                        t++;
                    }

                    if (this->parameters.decomp)
                    {
                        this->decomp(t, x, y, zx, zy);
                    }
                    else
                    {
                        this->set_color(t, x, y, zx, zy);
                    }
                }
            }
        }

    public:
        Mandelbrot(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
