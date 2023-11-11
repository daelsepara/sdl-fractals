#ifndef __MANDELBROT3_HPP__
#define __MANDELBROT3_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot3 : public Fractal::Base
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
                    auto zx = cx * cx;

                    auto zy = cy * cy;

                    auto xx = cx;

                    auto yy = cy;

                    // generate escape time fractal
                    while ((zx + zy) <= this->parameters.EscapeValue && (t < this->parameters.MaxIterations))
                    {
                        this->FilterInputs(xx, yy);

                        yy = (xx + xx) * yy;

                        xx = zx - zy;

                        this->FilterResult(xx, yy);

                        xx += cx;

                        yy += cy;

                        zx = xx * xx;

                        zy = yy * yy;

                        t++;
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        Mandelbrot3(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
