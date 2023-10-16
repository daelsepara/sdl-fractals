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

            auto attract = parameters.escape_value_threshold * parameters.escape_value_threshold;

            auto threshold = this->parameters.escape_time_threshold * this->parameters.escape_time_threshold;

            auto max_color = std::max(max_iterations, this->parameters.escape_time_threshold);

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
                    this->grid[y][x] = t;
                }
            }

            this->parameters.escape_time_threshold = max_color;
        }

    public:
        SimpleJulia(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
