#ifndef __ITERATED_FUNCTION_SYSTEM_HPP__
#define __ITERATED_FUNCTION_SYSTEM_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"
#include "../Random.hpp"

namespace Fractal
{
    class IteratedFunctionSystem : public Fractal::Base
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

            auto x = 0.0;

            auto y = 0.0;

            auto random = Random::Base();

            random.UniformDistribution();

            auto xn = 0.0;

            auto yn = 0.0;

            for (auto t = 0; t < this->parameters.MaxIterations; t++)
            {
                this->FilterInputs(xn, yn);

                Fractal::Transform(random.NextDouble(), x, y, this->parameters.Transforms, xn, yn);

                this->FilterResult(xn, yn);

                auto xp = this->parameters.PixelX(xn, dx);

                auto yp = this->parameters.PixelY(yn, dy);

                if (xp >= 0 && xp < this->parameters.XPixels && yp >= 0 && yp < this->parameters.YPixels)
                {
                    this->SetColor(xp, yp);
                }

                x = xn;

                y = yn;
            }
        }

    public:
        IteratedFunctionSystem(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
