#ifndef __ITERATED_FUNCTION_SYSTEM_HPP__
#define __ITERATED_FUNCTION_SYSTEM_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Random.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class IteratedFunctionSystem : public Fractal::Base
    {
    private:
        void ApplyTransformation(double x, double y, Fractal::Transformation &transform, double &xn, double &yn)
        {
            // transform[0] = x coefficient (xn)
            // transform[1] = y coefficient (xn)
            // transform[2] = x coefficient (yn)
            // transform[3] = y coefficient (yn)
            // transform[4] = constant (xn)
            // transform[5] = constant (yn)
            // transform[6] = probability
            if (transform.size() < 7)
            {
                return;
            }

            xn = transform[0] * x + transform[1] * y + transform[4];

            yn = transform[2] * x + transform[3] * y + transform[5];
        }

        void Transform(double p, double x, double y, Fractal::Transformations &transforms, double &xn, double &yn)
        {
            auto transform_p = 0.0;

            auto i = 0;

            for (auto i = 0; i < transforms.size(); i++)
            {
                if (transforms[i].size() >= 7)
                {
                    transform_p += transforms[i][6];

                    if (p < transform_p)
                    {
                        this->ApplyTransformation(x, y, transforms[i], xn, yn);

                        break;
                    }
                }
            }
        }

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

            // initialize random number generator
            auto random = Random::Base();

            random.UniformDistribution();

            auto x = 0.0;

            auto y = 0.0;

            auto xn = 0.0;

            auto yn = 0.0;

            auto xp = 0.0;

            auto yp = 0.0;

            for (auto t = 0; t < this->parameters.MaxIterations; t++)
            {
                this->FilterInputs(xn, yn);

                this->Transform(random.NextDouble(), x, y, this->parameters.Transforms, xn, yn);

                this->FilterResult(xn, yn);

                xp = this->parameters.PixelX(xn, dx);

                yp = this->parameters.PixelY(yn, dy);

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
