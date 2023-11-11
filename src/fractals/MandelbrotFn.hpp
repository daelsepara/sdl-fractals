#ifndef __MANDELBROT_FN_HPP__
#define __MANDELBROT_FN_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class MandelbrotFn : public Fractal::Base
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

            auto x = 0;

            auto y = 0;

            auto t = 0;

            auto cx = 0.0;

            auto cy = 0.0;

            auto zx = 0.0;

            auto zy = 0.0;

            // calculate mandelbrot set
            for (y = 0; y < this->parameters.YPixels; y++)
            {
                cy = this->parameters.ScaledY(y, dy);

                for (x = 0; x < this->parameters.XPixels; x++)
                {
                    cx = this->parameters.ScaledX(x, dx);

                    zx = cx;

                    zy = cy;

                    t = 0;

                    // generate escape time fractal
                    while (Fractal::Mag2(zx, zy) <= this->parameters.EscapeValue && t < this->parameters.MaxIterations)
                    {
                        this->FilterInputs(zx, zy);

                        this->ApplyFunction(zx, zy);

                        if (this->parameters.Exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.Exponent);
                        }

                        this->FilterResult(zx, zy);

                        Fractal::Multiply(zx, zy, cx, cy, zx, zy);

                        t++;
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        MandelbrotFn(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
