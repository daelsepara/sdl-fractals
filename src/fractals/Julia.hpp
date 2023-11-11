#ifndef __JULIA_HPP__
#define __JULIA_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Julia : public Fractal::Base
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

            // pointer to complex function
            auto ApplyFunction = Fractal::MapFunction(this->parameters.Function1);

            // calculate julia set
            for (auto y = 0; y < this->parameters.YPixels; y++)
            {
                for (auto x = 0; x < this->parameters.XPixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.ScaledX(x, dx);

                    auto zy = this->parameters.ScaledY(y, dy);

                    // generate escape time fractal
                    while (Fractal::Mag2(zx, zy) <= this->parameters.EscapeValue && t < this->parameters.MaxIterations)
                    {
                        this->FilterInputs(zx, zy);

                        ApplyFunction(zx, zy);

                        if (this->parameters.Exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.Exponent);
                        }

                        this->FilterResult(zx, zy);

                        zx += this->parameters.cx;

                        zy += this->parameters.cy;

                        t++;
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        Julia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
