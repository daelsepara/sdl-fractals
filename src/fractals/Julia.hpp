#ifndef __JULIA_HPP__
#define __JULIA_HPP__

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Julia
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

                    if (this->parameters.invert_x)
                    {
                        // reverse x-location on image, i.e. - to + runs from right to left of the image
                        zx = this->parameters.min_x + (double)(this->parameters.x_pixels - x - 1) * dx;
                    }

                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto zy = this->parameters.min_y + (double)(this->parameters.y_pixels - y - 1) * dy;

                    if (this->parameters.invert_y)
                    {
                        zy = this->parameters.min_y + (double)y * dy;
                    }

                    while ((zx * zx + zy * zy) <= this->parameters.escape_value_threshold * this->parameters.escape_value_threshold && (t < this->parameters.escape_time_threshold))
                    {
                        auto xtemp = zx * zx - zy * zy + this->parameters.cx;
                        zy = 2 * zx * zy + this->parameters.cy;
                        zx = xtemp;
                        t++;
                    }

                    // set escape-time color
                    if (this->parameters.log_coloring)
                    {
                        this->grid[y][x] = Fractal::LogColor(t, this->parameters.escape_time_threshold);
                    }
                    else if (this->parameters.normalized_coloring)
                    {
                        this->grid[y][x] = Fractal::NormalizedColor(t, this->parameters.escape_time_threshold);
                    }
                    else
                    {
                        this->grid[y][x] = Fractal::Clamp(t);
                    }
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

        Julia(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
