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

        virtual void generate() {}

        void map_filters()
        {
            // set inputs/result filter
            this->FilterInputs = Fractal::MapFunction(this->parameters.inputs_filter);

            this->FilterResult = Fractal::MapFunction(this->parameters.result_filter);
        }

        void set_color(int x, int y, int c)
        {
            this->grid[y][x] = c;
        }

        void set_color(int x, int y)
        {
            this->set_color(x, y, this->parameters.inside_color);
        }

        void set_color(int t, int x, int y, double zx, double zy)
        {
            if (t != this->parameters.max_iterations)
            {
                if (this->parameters.decomp)
                {
                    auto d = std::atan2(zy, zx);

                    if (d < 0)
                    {
                        d += Fractal::PI2;
                    }

                    auto color = (int)((double)this->parameters.max_iterations * (d / Fractal::PI2));

                    this->set_color(x, y, color);
                }
                else if (std::abs(zx) < this->parameters.bailout || std::abs(zy) < this->parameters.bailout)
                {
                    this->grid[y][x] = this->parameters.bailout_color;
                }
                else
                {
                    this->set_color(x, y, t);
                }
            }
            else
            {
                this->set_color(x, y);
            }
        }

    public:
        void render()
        {
            this->generate();

            Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.max_iterations);

            Fractal::RenderImage(this->grid, this->parameters);
        }

        void save(std::string image)
        {
            this->generate();

            if (image.length() > 0)
            {
                Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.max_iterations);

                Fractal::SaveImage(this->grid, this->parameters, image);
            }
        }

        void benchmark()
        {
            this->generate();
        }

        Base() {}

        Base(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
