#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot : public Fractal::Base
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
            auto threshold = this->parameters.orbit * this->parameters.orbit;

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

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = 0.0;

                    auto zy = 0.0;

                    // generate escape time fractal
                    while (t < this->parameters.max_iterations)
                    {
                        ComplexFunction(zx, zy);

                        if (this->parameters.exponent != 1)
                        {
                            Fractal::Power(zx, zy, this->parameters.exponent);
                        }

                        zx += cx;

                        zy += cy;

                        if ((zx * zx + zy * zy) > threshold)
                        {
                            break;
                        }

                        t++;
                    }

                    // set escape-time color
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
            }
        }

    public:
        Mandelbrot(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
