#ifndef __JULIA_HPP__
#define __JULIA_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Julia : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // pre-calculate escape orbit
            auto threshold = this->parameters.escape_value_threshold * this->parameters.escape_value_threshold;

            // pointer to complex function
            void (*ComplexFunction)(double &, double &);

            if (this->parameters.function == "sin")
            {
                ComplexFunction = Fractal::Sin;
            }
            else if (this->parameters.function == "cos")
            {
                ComplexFunction = Fractal::Cos;
            }
            else if (this->parameters.function == "tan")
            {
                ComplexFunction = Fractal::Tan;
            }
            else if (this->parameters.function == "cot")
            {
                ComplexFunction = Fractal::Cot;
            }
            else if (this->parameters.function == "sec")
            {
                ComplexFunction = Fractal::Sec;
            }
            else if (this->parameters.function == "csc")
            {
                ComplexFunction = Fractal::Csc;
            }
            else if (this->parameters.function == "sinh")
            {
                ComplexFunction = Fractal::Sinh;
            }
            else if (this->parameters.function == "cosh")
            {
                ComplexFunction = Fractal::Cosh;
            }
            else if (this->parameters.function == "tanh")
            {
                ComplexFunction = Fractal::Tanh;
            }
            else if (this->parameters.function == "coth")
            {
                ComplexFunction = Fractal::Coth;
            }
            else if (this->parameters.function == "sech")
            {
                ComplexFunction = Fractal::Sech;
            }
            else if (this->parameters.function == "csch")
            {
                ComplexFunction = Fractal::Csch;
            }
            else if (this->parameters.function == "exp")
            {
                ComplexFunction = Fractal::Exp;
            }
            else if (this->parameters.function == "conj")
            {
                ComplexFunction = Fractal::Conjugate;
            }
            else
            {
                ComplexFunction = Fractal::Identity;
            }

            // calculate julia set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.scaled_x(x, dx);

                    auto zy = this->parameters.scaled_y(y, dy);

                    // generate escape time fractal
                    while (t < this->parameters.escape_time_threshold)
                    {
                        ComplexFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        zx += this->parameters.cx;

                        zy += this->parameters.cy;

                        if ((zx * zx + zy * zy) > threshold)
                        {
                            break;
                        }

                        t++;
                    }

                    // set escape-time color
                    if (t != this->parameters.escape_time_threshold)
                    {
                        this->grid[y][x] = t;
                    }
                    else
                    {
                        this->grid[y][x] = this->parameters.inside_color;
                    }
                }
            }
        }

    public:
        Julia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
