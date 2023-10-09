#ifndef __BARNSLEY_FERN__
#define __BARNSLEY_FERN__

#include "../Parameters.hpp"
#include "../Utilities.hpp"
#include "../Random.hpp"

namespace Fractal
{
    class BarnsleyFern
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

            auto x = 0.0;

            auto y = 0.0;

            auto random = Random::Base();

            random.UniformDistribution();

            auto xn = 0.0;

            auto yn = 0.0;

            for (auto t = 0; t < this->parameters.escape_time_threshold; t++)
            {
                auto p = random.NextDouble();

                Fractal::Transform(p, x, y, this->parameters.transforms, xn, yn);

                auto xp = (int)((xn - this->parameters.min_x) / dx);

                if (this->parameters.invert_x)
                {
                    // reverse x-location on image, i.e. - to + runs from right to left of the image
                    xp = (this->parameters.x_pixels - (int)((xn - this->parameters.min_x) / dx) + 1);
                }

                auto yp = (this->parameters.y_pixels - (int)((yn - this->parameters.min_y) / dy) + 1);

                if (this->parameters.invert_y)
                {
                    yp = (int)((yn - this->parameters.min_y) / dy);
                }

                if (xp >= 0 && xp < this->parameters.x_pixels && yp >= 0 && yp < this->parameters.y_pixels)
                {
                    this->grid[yp][xp] = this->parameters.inside_color;
                }

                x = xn;
                y = yn;
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

        BarnsleyFern(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
