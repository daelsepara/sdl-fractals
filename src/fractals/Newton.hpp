#ifndef __NEWTON_HPP__
#define __NEWTON_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Newton : public Fractal::Base
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

            // calculate newton fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    auto diff = std::numeric_limits<double>::infinity();

                    while (diff > this->parameters.tolerance && ++t < this->parameters.max_iterations)
                    {
                        auto oldx = zx;

                        auto oldy = zy;

                        this->FilterInputs(zx, zy);

                        auto denx = zx;

                        auto deny = zy;

                        // n * z^(n-1)
                        Fractal::Power(denx, deny, this->parameters.exponent - 1);

                        denx *= (double)this->parameters.exponent;

                        deny *= (double)this->parameters.exponent;

                        // (n - 1) * z^n + 1.0
                        Fractal::Power(zx, zy, this->parameters.exponent);

                        zx = ((double)this->parameters.exponent - 1.0) * zx + 1.0;

                        zy *= (double)this->parameters.exponent - 1.0;

                        // ((n - 1) * z^n + 1.0) / (n * z^(n-1))
                        Fractal::Divide(zx, zy, denx, deny, zx, zy);

                        this->FilterResult(zx, zy);
                        
                        diff = Fractal::Mag2(zx - oldx, zy - oldy);
                    }

                    this->set_color(t, x, y, zx, zy);
                }
            }
        }

    public:
        Newton(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
