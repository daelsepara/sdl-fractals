#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Mandelbrot
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

            // pre-calculate orbit
            auto threshold = this->parameters.escape_value_threshold * this->parameters.escape_value_threshold;

            // calculate mandelbrot set
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    // calculate location (cx, cy) on complex plane
                    auto cx = this->parameters.min_x + (double)x * dx;

                    if (this->parameters.invert_x)
                    {
                        // reverse x-location on image, i.e. - to + runs from right to left of the image
                        cx = this->parameters.min_x + (double)(this->parameters.x_pixels - x - 1) * dx;
                    }

                    // reverse y-location on image, i.e. - to + runs from top to bottom of the image
                    auto cy = this->parameters.min_y + (double)(this->parameters.y_pixels - y - 1) * dy;

                    if (this->parameters.invert_y)
                    {
                        cy = this->parameters.min_y + (double)y * dy;
                    }

                    auto zx = 0.0;

                    auto zy = 0.0;

                    // generate escape time fractal
                    while ((zx * zx + zy * zy) <= threshold && (t < this->parameters.escape_time_threshold))
                    {
                        Fractal::Power(zx, zy, this->parameters.exponent);

                        zx += cx;

                        zy += cy;

                        t++;
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

        Mandelbrot(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
