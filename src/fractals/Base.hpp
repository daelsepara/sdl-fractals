#ifndef __FRACTALS_BASE_HPP__
#define __FRACTALS_BASE_HPP__

#include <string>

#include "../ComplexFunctions.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    const double PI = 3.14159265358979323846;

    const double PI2 = Fractal::PI * 2.0;

    class Base
    {
    protected:
        Fractal::Parameters parameters;

        Fractal::Grid grid;

        Fractal::FunctionPointer FilterInputs;

        Fractal::FunctionPointer FilterResult;

        Fractal::FunctionPointer ApplyFunction;

        virtual void Generate() {}

        void MapFunctions()
        {
            // set default function
            this->ApplyFunction = this->parameters.Functions.size() > 0 ? Fractal::MapFunction(this->parameters.Functions[0]) : Fractal::Identity;

            // set inputs/result filter
            this->FilterInputs = Fractal::MapFunction(this->parameters.InputsFilter);

            this->FilterResult = Fractal::MapFunction(this->parameters.ResultFilter);
        }

        inline void SetColor(int x, int y, int c)
        {
            this->grid[y][x] = c;
        }

        inline void SetColor(int x, int y)
        {
            this->SetColor(x, y, this->parameters.InsideColor);
        }

        void SetColor(int t, int x, int y, double zx, double zy)
        {
            if (t != this->parameters.MaxIterations)
            {
                if (this->parameters.Decomp)
                {
                    auto d = std::atan2(zy, zx);

                    if (d < 0)
                    {
                        d += Fractal::PI2;
                    }

                    auto color = int(double(this->parameters.MaxIterations) * (d / Fractal::PI2));

                    this->SetColor(x, y, color);
                }
                else if (std::abs(zx) < this->parameters.Bailout || std::abs(zy) < this->parameters.Bailout)
                {
                    this->SetColor(x, y, this->parameters.BailoutColor);
                }
                else
                {
                    this->SetColor(x, y, t);
                }
            }
            else
            {
                this->SetColor(x, y);
            }
        }

    public:
        void Render()
        {
            this->Generate();

            Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.MaxIterations);

            Fractal::RenderImage(this->grid, this->parameters);
        }

        void Save(std::string image)
        {
            this->Generate();

            if (image.length() > 0)
            {
                Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.MaxIterations);

                Fractal::SaveImage(this->grid, this->parameters, image);
            }
        }

        void Benchmark()
        {
            this->Generate();
        }

        Base() {}

        Base(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
