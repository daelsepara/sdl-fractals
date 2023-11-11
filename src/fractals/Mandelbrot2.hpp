#ifndef __MANDELBROT2_HPP__
#define __MANDELBROT2_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot2 : public Fractal::Base
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

            // calculate mandelbrot set
            for (auto y = 0; y < this->parameters.YPixels; y++)
            {
                // calculate cy coordinate on complex plane
                auto cy = this->parameters.ScaledY(y, dy);

                for (auto x = 0; x < this->parameters.XPixels; x++)
                {
                    auto t = 1;

                    // calculate cx coordinate on complex plane
                    auto cx = this->parameters.ScaledX(x, dx);

                    // initial condition z0 (zx, zy)
                    auto zx = cx;

                    auto zy = cy;

                    // generate escape time fractal
                    while (Fractal::Mag2(zx, zy) <= this->parameters.EscapeValue && (t < this->parameters.MaxIterations))
                    {
                        this->FilterInputs(zx, zy);

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
        Mandelbrot2(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
