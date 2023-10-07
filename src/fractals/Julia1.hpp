#ifndef __JULIA1_HPP__
#define __JULIA1_HPP__

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Julia1
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

            // calculate julia set
            for (auto y = 0; y < this->parameters.y_pixels; y++)
            {
                for (auto x = 0; x < this->parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    // calculate location (zx, zy) on complex plane
                    auto zx = this->parameters.min_x + (double)x * dx;
                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto zy = this->parameters.min_y + (double)(this->parameters.y_pixels - y - 1) * dy;
                    // generate escape time fractal
                    while ((zx * zx + zy * zy) <= this->parameters.escape_value_threshold * this->parameters.escape_value_threshold && (t < this->parameters.escape_time_threshold))
                    {
                        auto xtemp = zx * zx - zy * zy + this->parameters.cx;
                        zy = 2 * zx * zy + this->parameters.cy;
                        zx = xtemp;
                        t++;
                    }

                    // set escape-time color
                    this->grid[y][x] = t;
                }
            }
        }

        void generate(std::string image, std::string palette)
        {
            this->generate();

            if (image.length() > 0)
            {
                Fractal::SaveImage(this->grid, this->parameters, image, palette);
            }
        }

        Julia1(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
