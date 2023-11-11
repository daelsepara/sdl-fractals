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

                        auto denx = zx;

                        auto deny = zy;

                        // n * z^(n-1)
                        Fractal::Power(denx, deny, this->parameters.Exponent - 1);

                        auto n = (double)this->parameters.Exponent;

                        denx *= n;

                        deny *= n;

                        // (n - 1) * z^n + 1.0
                        Fractal::Power(zx, zy, this->parameters.Exponent);

                        auto n1 = (double)this->parameters.Exponent - 1.0;

                        (zx *= n1) += 1.0;

                        zy *= n1;

                        // ((n - 1) * z^n + 1.0) / (n * z^(n-1))
                        Fractal::Divide(zx, zy, denx, deny, zx, zy);

                        this->FilterResult(zx, zy);

                        diff = Fractal::Mag2(zx - oldx, zy - oldy);
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        Newton(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
