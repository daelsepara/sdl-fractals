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

            auto x = 0;

            auto y = 0;

            auto t = 0;

            auto zx = 0.0;

            auto zy = 0.0;

            auto diff = 0.0;

            auto oldx = 0.0;

            auto oldy = 0.0;

            auto zxx = 0.0;

            auto zyy = 0.0;

            auto tmp = 0.0;

            auto tmp3 = 0.0;

            // calculate newton fractal
            for (y = 0; y < parameters.YPixels; y++)
            {
                for (x = 0; x < parameters.XPixels; x++)
                {
                    t = 0;

                    // calculate location (zx, zy) on complex plane
                    zx = this->parameters.ScaledX(x, dx);

                    zy = this->parameters.ScaledY(y, dy);

                    diff = std::numeric_limits<double>::infinity();

                    while (diff > this->parameters.Tolerance && ++t < this->parameters.MaxIterations)
                    {
                        oldx = zx;

                        oldy = zy;

                        this->FilterInputs(zx, zy);

                        zxx = zx * zx;

                        zyy = zy * zy;

                        tmp = (zxx + zyy) * (zxx + zyy);

                        tmp3 = 3.0 * tmp;

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
