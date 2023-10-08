#ifndef __NEWTON1_HPP__
#define __NEWTON1_HPP__

#include <cmath>
#include <complex>

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Newton1
    {
    private:
        Fractal::Parameters parameters;

    public:
        Fractal::Grid grid;

        void generate()
        {
            // create complex plane (initialize grid)
            this->grid = Fractal::InitializeGrid(this->parameters);

            // calculate scaling factor
            auto dx = (double)(this->parameters.max_x - this->parameters.min_x) / (double)(this->parameters.x_pixels);

            auto dy = (double)(this->parameters.max_y - this->parameters.min_y) / (double)(this->parameters.y_pixels);

            // calculate newton fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    // calculate location (cx, cy) on complex plane
                    auto zx = this->parameters.min_x + (double)x * dx;
                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto zy = this->parameters.min_y + (double)(this->parameters.y_pixels - y - 1) * dy;

                    auto tmp = 1.0;

                    while (tmp > this->parameters.tolerance && ++t < this->parameters.escape_time_threshold)
                    {
                        auto oldx = zx;

                        auto oldy = zy;

                        tmp = (zx * zx + zy * zy) * (zx * zx + zy * zy);

                        zx = (2 * zx * tmp + zx * zx - zy * zy) / (3.0 * tmp);

                        zy = (2 * zy *  (tmp - oldx)) / (3.0 * tmp);

                        auto zx1 = zx - oldx;

                        auto zy1 = zy - oldy;

                        tmp = (zx1 * zx1 + zy1 * zy1);
                    }

                    // set escape-time color
                    this->grid[y][x] = t;
                }
            }
        }

        void generate(std::string palette)
        {
            this->generate();

            Fractal::RenderImage(this->grid, this->parameters, palette);
        }

        void generate(std::string image, std::string palette)
        {
            this->generate();

            if (image.length() > 0)
            {
                Fractal::SaveImage(this->grid, this->parameters, image, palette);
            }
        }

        Newton1(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
