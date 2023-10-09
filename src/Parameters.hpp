#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include <string>
#include <vector>

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
        int exponent = 2;

        // complex plane window boundaries
        double min_x = -2.5;
        double max_x = 2.5;
        double min_y = -2.5;
        double max_y = 2.5;

        // Newton parameters
        double tolerance = 0.000001;

        // Julia set parameters
        double cx = -0.8;
        double cy = 0.156;

        // inside color
        int inside_color = 128;

        // invert axis
        bool invert_x = false;
        bool invert_y = false;

        // transformations
        std::vector<std::vector<double>> transforms = std::vector<std::vector<double>>();
    };
}

#endif
