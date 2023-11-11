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

            auto cx = 0.0;

            auto cy = 0.0;

            auto zx = 0.0;

            auto zy = 0.0;

            // calculate tricorn fractal
            for (y = 0; y < parameters.YPixels; y++)
            {
                // calculate cy coordinate on complex plane
                cy = this->parameters.ScaledY(y, dy);

                for (x = 0; x < parameters.XPixels; x++)
                {
                    t = 0;

                    // calculate cx coordinate on complex plane
                    cx = this->parameters.ScaledX(x, dx);

                    zx = cx;

                    zy = cy;

                    while (Fractal::Mag2(zx, zy) <= this->parameters.EscapeValue && t < this->parameters.MaxIterations)
                    {
                        this->FilterInputs(zx, zy);

                        Fractal::Conjugate(zx, zy);

                        Fractal::Sqr(zx, zy);

                        this->FilterResult(zx, zy);

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        Tricorn(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
