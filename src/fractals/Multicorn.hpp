#ifndef __MULTICORN_HPP__
#define __MULTICORN_HPP__

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Multicorn
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
            auto dx = this->parameters.dx();

            auto dy = this->parameters.dy();

            // calculate multi-corn fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                // calculate location cy on complex plane
                auto cy = this->parameters.scaled_y(y, dy);

                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    auto t = 0;

                    // calculate location cx on complex plane
                    auto cx = this->parameters.scaled_x(x, dx);

                    auto zx = cx;

                    auto zy = cy;

                    while ((zx * zx + zy * zy) < this->parameters.escape_value_threshold && t < this->parameters.escape_time_threshold)
                    {
                        // complex conjugate
                        zy = -zy;

                        Fractal::Power(zx, zy, this->parameters.exponent);

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    if (t != this->parameters.escape_time_threshold)
                    {
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
                    else
                    {
                        this->grid[y][x] = this->parameters.inside_color;
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

        Multicorn(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
