#ifndef __MANDELBROT2_HPP__
#define __MANDELBROT2_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot2 : public Fractal::Base
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

            // calculate mandelbrot set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                // calculate cy coordinate on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 1;

                    // calculate cx coordinate on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    // initial condition z0 (zx, zy)
                    auto zx = cx;

                    auto zy = cy;

                    // generate escape time fractal
                    while (Fractal::Mag2(zx, zy) <= threshold && (t < this->parameters.max_iterations))
                    {
                        this->FilterInputs(zx, zy);

                        Fractal::Sqr(zx, zy);

                        this->FilterResult(zx, zy);

                        zx += cx;

                        zy += cy;

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
        Mandelbrot2(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
