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
            auto InputsFilter = Fractal::MapFunction(this->parameters.inputs_filter);
            
            auto ResultFilter = Fractal::MapFunction(this->parameters.result_filter);

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pre-calculate escape orbit
            auto threshold = this->parameters.orbit * this->parameters.orbit;

            // pointer to complex function
            auto ComplexFunction = Fractal::MapFunction(this->parameters.function);

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = 0.0;

                    auto zy = 0.0;

                    // generate escape time fractal
                    while (t < this->parameters.max_iterations)
                    {
                        InputsFilter(zx, zy);

                        ComplexFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        ResultFilter(zx, zy);

                        zx += cx;

                        zy += cy;

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
        Mandelbrot(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
