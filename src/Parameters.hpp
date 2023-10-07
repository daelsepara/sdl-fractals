#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include <string>

namespace Fractal
{
    class Parameters
    {
    public:
        std::string type;

        // image size
        int x_pixels = 2048;
        int y_pixels = 2048;

        // mandelbrot parameter(s)
        int escape_time_threshold = 255;
        double escape_value_threshold = 2.0;
        double exponent = 2.0;

        // complex plane window boundaries
        double min_x = -2.5;
        double max_x = 2.5;
        double min_y = -2.5;
        double max_y = 2.5;

        // Newton parameters
        double tolerance = 0.000001;
    };
}

#endif
