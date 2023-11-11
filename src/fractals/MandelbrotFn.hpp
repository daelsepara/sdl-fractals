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
            this->MapFilters();

            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.DeltaX();

            auto dy = this->parameters.DeltaY();

            // pointer to complex function
            auto ApplyFunction = Fractal::MapFunction(this->parameters.Function1);

            // calculate mandelbrot set
            for (auto y = 0; y < this->parameters.YPixels; y++)
            {
                auto cy = this->parameters.ScaledY(y, dy);

                for (auto x = 0; x < this->parameters.XPixels; x++)
                {
                    auto cx = this->parameters.ScaledX(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    auto t = 0;

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
