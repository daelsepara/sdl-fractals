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
            // set inputs/result filter
            this->map_filters();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // calculate tricorn fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate cy coordinate on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate cx coordinate on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    while (Fractal::Mag2(zx, zy) < this->parameters.orbit && t < this->parameters.max_iterations)
                    {
                        this->FilterInputs(zx, zy);

                        Fractal::Conjugate(zx, zy);

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
        Tricorn(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
