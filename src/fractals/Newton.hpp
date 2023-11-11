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
            this->MapFunctions();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.DeltaX();

            auto dy = this->parameters.DeltaY();

            auto exp1 = this->parameters.Exponent - 1;

            auto n = double(this->parameters.Exponent);

            auto n1 = double(exp1);

            auto x = 0;

            auto y = 0;

            auto t = 0;

            auto zx = 0.0;

            auto zy = 0.0;

            auto oldx = 0.0;

            auto oldy = 0.0;

            auto diff = 0.0;

            auto denx = 0.0;

            auto deny = 0.0;

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

                    while (diff > this->parameters.Tolerance && t++ < this->parameters.MaxIterations)
                    {
                        oldx = zx;

                        oldy = zy;

                        this->FilterInputs(zx, zy);

                        denx = zx;

                        deny = zy;

                        // n * z^(n-1)
                        Fractal::Power(denx, deny, exp1);

                        denx *= n;

                        deny *= n;

                        // (n - 1) * z^n + 1.0
                        Fractal::Power(zx, zy, this->parameters.Exponent);

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
