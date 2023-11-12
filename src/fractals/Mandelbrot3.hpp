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
            // set apply/inputs/result function filter
            this->MapFunctions();

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

            auto xx = 0.0;

            auto yy = 0.0;

            // calculate mandelbrot set
            for (y = 0; y < this->parameters.YPixels; y++)
            {
                // calculate cy coordinate on complex plane
                cy = this->parameters.ScaledY(y, dy);

                for (x = 0; x < this->parameters.XPixels; x++)
                {
                    t = 1;

                    // calculate cx coordinate on complex plane
                    cx = this->parameters.ScaledX(x, dx);

                    // initial condition z0 (zx, zy)
                    zx = cx * cx;

                    zy = cy * cy;

                    xx = cx;

                    yy = cy;

                    // generate escape time fractal
                    while ((zx + zy) <= this->parameters.EscapeValue && t < this->parameters.MaxIterations)
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
