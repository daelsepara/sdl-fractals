#ifndef __SIMPLE_JULIA_HPP__
#define __SIMPLE_JULIA_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class SimpleJulia : public Fractal::Base
    {
    protected:
        void generate() override
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factors
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            auto max_iterations = 510;

            auto attract = parameters.orbit * parameters.orbit;

            auto threshold = this->parameters.max_iterations * this->parameters.max_iterations;

            auto max_color = std::max(max_iterations, this->parameters.max_iterations);

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

                    auto cx = this->parameters.cx;

                    auto cy = this->parameters.cy;

                    while (t < max_iterations)
                    {
                        ComplexFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        zx += cx;

                        zy += cy;

                        auto mag = zx * zx + zy * zy;

                        if (mag < attract)
                        {
                            t = 0;

                            break;
                        }
                        else if (mag >= threshold)
                        {
                            break;
                        }

                        t++;
                    }

                    // set escape-time color
                    if (t != max_iterations)
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
            }

            this->parameters.max_iterations = max_color;
        }

    public:
        SimpleJulia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
