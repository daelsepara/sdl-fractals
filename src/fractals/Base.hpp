#ifndef __FRACTALS_BASE_HPP__
#define __FRACTALS_BASE_HPP__

#include <string>

#include "../ComplexFunctions.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Base
    {
    protected:
        Fractal::Parameters parameters;

        Fractal::Grid grid;

        virtual void generate() {}

        void set_color(int x, int y)
        {
            this->grid[y][x] = this->parameters.inside_color;
        }

        void set_color(int t, int x, int y, double zx, double zy)
        {
            if (t != this->parameters.max_iterations)
            {
                if (std::abs(zx) < this->parameters.bailout || std::abs(zy) < this->parameters.bailout)
                {
                    this->grid[y][x] = this->parameters.bailout_color;
                }
                else
                {
                    this->grid[y][x] = t;
                }
            }
            else
            {
                this->grid[y][x] = this->parameters.inside_color;
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
