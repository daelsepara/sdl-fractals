#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "nlohmann/json.hpp"

namespace Fractal
{
    typedef std::vector<double> Transformation;

    typedef std::vector<std::vector<double>> Transformations;

    typedef std::vector<int> GridRow;

    typedef std::vector<std::vector<int>> Grid;

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

        // log color mapping
        bool log_coloring = false;

        // normalized color mapping
        bool normalized_coloring = false;

        // modulus color mapping
        bool mod_coloring = false;

        // invert colors
        bool invert_colors = false;

        // invert axis
        bool invert_x = false;
        bool invert_y = false;

        // transformations
        Fractal::Transformations transforms = Fractal::Transformations();

        double dx()
        {
            return (double)(this->max_x - this->min_x) / (double)(this->x_pixels);
        }

        double dy()
        {
            return (double)(this->max_y - this->min_y) / (double)(this->y_pixels);
        }

        double scaled_x(int x, double dx)
        {
            if (this->invert_x)
            {
                return this->min_x + (double)(this->x_pixels - x - 1) * dx;
            }
            else
            {
                return this->min_x + (double)x * dx;
            }
        }

        double scaled_y(int y, double dy)
        {
            if (this->invert_y)
            {
                return this->min_y + (double)y * dy;
            }
            else
            {
                return this->min_y + (double)(this->y_pixels - y - 1) * dy;
            }
        }

        int pixel_x(double x, double dx)
        {
            if (this->invert_x)
            {
                return (this->x_pixels - (int)((x - this->min_x) / dx) + 1);
            }
            else
            {
                return (int)((x - this->min_x) / dx);
            }
        }

        int pixel_y(double y, double dy)
        {
            if (this->invert_y)
            {
                return (int)((y - this->min_y) / dy);
            }
            else
            {
                return (this->y_pixels - (int)((y - this->min_y) / dy) + 1);
            }
        }

        // load parameters from file
        void Load(std::string filename)
        {
            std::ifstream file(filename);

            if (file.good())
            {
                std::cerr << "Loading parameters from " << filename << std::endl;

                auto data = nlohmann::json::parse(file);

                // fractal type
                this->type = !data["type"].is_null() ? std::string(data["type"]) : std::string("mandelbrot");

                // window borders on the comlex plane
                this->min_x = !data["min_x"].is_null() ? (double)data["min_x"] : -2.5;
                this->max_x = !data["max_x"].is_null() ? (double)data["max_x"] : 2.5;
                this->min_y = !data["min_y"].is_null() ? (double)data["min_y"] : -2.5;
                this->max_y = !data["max_y"].is_null() ? (double)data["max_y"] : 2.5;

                // fractal dimensions (in pixels)
                this->x_pixels = !data["x_pixels"].is_null() ? (int)data["x_pixels"] : 2048;
                this->y_pixels = !data["y_pixels"].is_null() ? (int)data["y_pixels"] : 2048;

                // parameters for escape time type of fractals
                this->escape_time_threshold = !data["escape_time_threshold"].is_null() ? (int)data["escape_time_threshold"] : 255;
                this->escape_value_threshold = !data["escape_value_threshold"].is_null() ? (double)data["escape_value_threshold"] : std::numeric_limits<double>::quiet_NaN();

                // mandelbrot parameter
                this->exponent = !data["exponent"].is_null() ? (int)data["exponent"] : std::numeric_limits<int>::quiet_NaN();

                // newton parameter
                this->tolerance = !data["tolerance"].is_null() ? (double)data["tolerance"] : std::numeric_limits<double>::epsilon();

                // julia set
                this->cx = !data["cx"].is_null() ? (double)data["cx"] : std::numeric_limits<double>::quiet_NaN();
                this->cy = !data["cy"].is_null() ? (double)data["cy"] : std::numeric_limits<double>::quiet_NaN();

                // inside_color
                this->inside_color = !data["inside_color"].is_null() ? (int)data["inside_color"] : std::numeric_limits<int>::quiet_NaN();

                // invert axis
                this->invert_x = !data["invert_x"].is_null() ? (bool)data["invert_x"] : false;
                this->invert_y = !data["invert_y"].is_null() ? (bool)data["invert_y"] : false;

                // log coloring
                this->log_coloring = !data["log_coloring"].is_null() ? (bool)data["log_coloring"] : false;

                // normalized coloring
                this->normalized_coloring = !data["normalized_coloring"].is_null() ? (bool)data["normalized_coloring"] : false;

                // modulus coloring
                this->mod_coloring = !data["mod_coloring"].is_null() ? (bool)data["mod_coloring"] : false;

                // transforms
                if (!data["transforms"].is_null() && data["transforms"].is_array())
                {
                    this->transforms = Fractal::Transformations();

                    for (auto j = 0; j < data["transforms"].size(); j++)
                    {
                        if (!data["transforms"][j].is_null() && data["transforms"][j].is_array())
                        {
                            auto transform = Fractal::Transformation();

                            for (auto i = 0; i < data["transforms"][j].size(); i++)
                            {
                                auto val = !data["transforms"][j][i].is_null() ? (double)data["transforms"][j][i] : std::numeric_limits<double>::quiet_NaN();

                                transform.push_back(val);
                            }

                            this->transforms.push_back(transform);
                        }
                    }
                }

                file.close();
            }
            else
            {
                std::cerr << "Unable to laod parameters from " << filename << std::endl;
            }
        }

        Parameters() {}

        Parameters(std::string filename)
        {
            this->Load(filename);
        }
    };
}

#endif
