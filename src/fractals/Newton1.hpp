#ifndef __NEWTON1_HPP__
#define __NEWTON1_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Newton1 : public Fractal::Base
    {
    protected:
        void Generate() override
        {
            // set inputs/result filter
            this->MapFilters();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.DeltaX();

            auto dy = this->parameters.DeltaY();

            // calculate newton fractal
            for (auto y = 0; y < parameters.YPixels; y++)
            {
                for (auto x = 0; x < parameters.XPixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.ScaledX(x, dx);

                    auto zy = this->parameters.ScaledY(y, dy);

                    auto diff = std::numeric_limits<double>::infinity();

                    while (diff > this->parameters.Tolerance && ++t < this->parameters.MaxIterations)
                    {
                        auto oldx = zx;

                        auto oldy = zy;

                        this->FilterInputs(zx, zy);

                        auto zxx = zx * zx;

                        auto zyy = zy * zy;

                        auto tmp = (zxx + zyy) * (zxx + zyy);

                        auto tmp3 = 3.0 * tmp;

                        zx = ((zx + zx) * tmp + zxx - zyy) / tmp3;

                        zy = ((zy + zy) * (tmp - oldx)) / tmp3;

                        this->FilterResult(zx, zy);

                        diff = Fractal::Mag2(zx - oldx, zy - oldy);
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        Newton1(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
