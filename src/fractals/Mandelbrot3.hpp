#ifndef __MANDELBROT3_HPP__
#define __MANDELBROT3_HPP__

#include "Base.hpp"
#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot3 : public Fractal::Base
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

            // calculate mandelbrot set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    auto t = 1;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    // initial condition z0 (zx, zy)
                    auto zx = cx * cx;

                    auto zy = cy * cy;

                    auto xx = cx;

                    auto yy = cy;

                    // generate escape time fractal
                    while ((zx + zy) <= threshold && (t < this->parameters.max_iterations))
                    {
                        yy = (xx + xx) * yy + cy;

                        xx = zx - zy + cx;

                        zx = xx * xx;

                        zy = yy * yy;

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
        Mandelbrot3(Fractal::Parameters parameters) : Fractal::Base(parameters) {}
    };
}

#endif
