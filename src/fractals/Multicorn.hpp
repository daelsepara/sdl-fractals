#ifndef __TRICORN2_HPP__
#define __TRICORN2_HPP__

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
            auto dx = (double)(this->parameters.max_x - this->parameters.min_x) / (double)(this->parameters.x_pixels);

            auto dy = (double)(this->parameters.max_y - this->parameters.min_y) / (double)(this->parameters.y_pixels);

            // calculate tricorn fractal
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    Uint8 t = 0;

                    auto cx = this->parameters.min_x + (double)x * dx;

                    // calculate location (cx, cy) on complex plane
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

                    auto zx = cx;

                    auto zy = cy;

                    while ((zx * zx + zy * zy) < this->parameters.escape_value_threshold && t < this->parameters.escape_time_threshold)
                    {
                        // complex conjugate
                        zy = -zy;
                        
                        auto oldx = zx;

                        auto oldy = zy;

                        if ((int)this->parameters.exponent == 0)
                        {
                            zx = 1.0;

                            zy = 1.0;
                        }
                        else
                        {
                            for (auto i = 0; i < this->parameters.exponent - 1; i++)
                            {
                                Fractal::Multiply(zx, zy, oldx, oldy, zx, zy);
                            }
                        }

                        zx += cx;

                        zy += cy;

                        t++;
                    }

                    if (t != this->parameters.escape_time_threshold)
                    {
                        // set escape-time color
                        this->grid[y][x] = (int)((double)this->parameters.escape_time_threshold / (double)t * 255.0);
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
