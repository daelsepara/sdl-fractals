#ifndef __ITERATED_FUNCTION_SYSTEM_HPP__
#define __ITERATED_FUNCTION_SYSTEM_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"
#include "../Random.hpp"

namespace Fractal
{
    class IteratedFunctionSystem : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            auto x = 0.0;

            auto y = 0.0;

            auto random = Random::Base();

            random.UniformDistribution();

            auto xn = 0.0;

            auto yn = 0.0;

            for (auto t = 0; t < this->parameters.escape_time_threshold; t++)
            {
                Fractal::Transform(random.NextDouble(), x, y, this->parameters.transforms, xn, yn);

                auto xp = this->parameters.pixel_x(xn, dx);

                auto yp = this->parameters.pixel_y(yn, dy);

                if (xp >= 0 && xp < this->parameters.x_pixels && yp >= 0 && yp < this->parameters.y_pixels)
                {
                    this->grid[yp][xp] = this->parameters.inside_color;
                }

                x = xn;

                y = yn;
            }
        }

    public:
        IteratedFunctionSystem(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
