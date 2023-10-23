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
            auto InputsFilter = Fractal::MapFunction(this->parameters.inputs_filter);
            
            auto ResultFilter = Fractal::MapFunction(this->parameters.result_filter);

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // calculate tricorn fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    while (Fractal::Mag2(zx, zy) < this->parameters.orbit && t < this->parameters.max_iterations)
                    {
                        InputsFilter(zx, zy);

                        auto xtemp = zx * zx - zy * zy;

                        zy = -(zx + zx) * zy;

                        zx = xtemp;

                        ResultFilter(zx, zy);

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        Tricorn(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
