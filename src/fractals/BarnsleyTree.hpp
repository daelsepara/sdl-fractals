#ifndef __BARNSLEY_TREE_HPP__
#define __BARNSLEY_TREE_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class BarnsleyTree : public Fractal::Base
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
                    while (Fractal::Mag2(zx, zy) <= threshold && t < this->parameters.max_iterations)
                    {
                        this->FilterInputs(zx, zy);

                        zx -= (double)Fractal::Sign(zx);

                        Fractal::Multiply(zx, zy, this->parameters.cx, this->parameters.cy, zx, zy);

                        this->FilterResult(zx, zy);

                        t++;
                    }

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        BarnsleyTree(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
