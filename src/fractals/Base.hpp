#ifndef __FRACTALS_BASE_HPP__
#define __FRACTALS_BASE_HPP__

#include <string>

#include "../Parameters.hpp"
#include "../Utilities.hpp"

namespace Fractal
{
    class Base
    {
    protected:
        Fractal::Parameters parameters;

        Fractal::Grid grid;

        virtual void generate() {}

    public:
        void render(std::string palette)
        {
            this->generate();

            Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.max_iterations);

            Fractal::RenderImage(this->grid, this->parameters, palette);
        }

        void save(std::string image, std::string palette)
        {
            this->generate();

            if (image.length() > 0)
            {
                Fractal::FinalizeColors(this->grid, this->parameters, this->parameters.max_iterations);

                Fractal::SaveImage(this->grid, this->parameters, image, palette);
            }
        }

        void benchmark()
        {
            this->generate();
        }

        Base() {}

        Base(Fractal::Parameters parameters)
        {
            this->parameters = parameters;
        }
    };
}

#endif
