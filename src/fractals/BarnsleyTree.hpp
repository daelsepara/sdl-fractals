#ifndef __BARNSLEY_TREE_HPP__
#define __BARNSLEY_TREE_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class BarnsleyTree : public Fractal::Base
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

            // pointer to complex function
            auto ApplyFunction = this->parameters.Functions.size() > 0 ? Fractal::MapFunction(this->parameters.Functions[0]) : Fractal::Identity;

            // calculate julia set
            for (y = 0; y < this->parameters.YPixels; y++)
            {
                for (x = 0; x < this->parameters.XPixels; x++)
                {
                    t = 0;

                    // calculate location (zx, zy) on complex plane
                    zx = this->parameters.ScaledX(x, dx);

                    zy = this->parameters.ScaledY(y, dy);

                    // generate escape time fractal
                    while (Fractal::Mag2(zx, zy) <= this->parameters.EscapeValue && t < this->parameters.MaxIterations)
                    {
                        this->FilterInputs(zx, zy);

                        zx -= (double)Fractal::Sign(zx);

                        Fractal::Multiply(zx, zy, this->parameters.cx, this->parameters.cy, zx, zy);

                        this->FilterResult(zx, zy);

                        t++;
                    }

                    this->SetColor(t, x, y, zx, zy);
                }
            }
        }

    public:
        BarnsleyTree(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
