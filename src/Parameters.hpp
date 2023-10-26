#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <unordered_map>
#include <SDL2/SDL.h>

#include "nlohmann/json.hpp"

namespace Fractal
{
    enum class ColorMode
    {
        DEFAULT = 0,
        NORMALIZED,
        LOG,
        HISTOGRAM,
        MODULUS
    };

    using Mapping = std::unordered_map<const char *, Fractal::ColorMode>;

    Fractal::Mapping ColorModeMapping = {
        {"none", Fractal::ColorMode::DEFAULT},
        {"default", Fractal::ColorMode::DEFAULT},
        {"norm", Fractal::ColorMode::NORMALIZED},
        {"normalized", Fractal::ColorMode::NORMALIZED},
        {"log", Fractal::ColorMode::LOG},
        {"logarithm", Fractal::ColorMode::LOG},
        {"hist", Fractal::ColorMode::HISTOGRAM},
        {"histogram", Fractal::ColorMode::HISTOGRAM},
        {"mod", Fractal::ColorMode::HISTOGRAM},
        {"modulus", Fractal::ColorMode::MODULUS}};

    typedef std::vector<double> Transformation;

    typedef std::vector<Fractal::Transformation> Transformations;

    typedef std::vector<int> GridRow;

    typedef std::vector<Fractal::GridRow> Grid;

    Fractal::ColorMode Find(Fractal::Mapping &unordered_map, const char *key)
    {
        auto result = Fractal::ColorMode::DEFAULT;

        for (auto &keys : unordered_map)
        {
            if (std::strcmp(keys.first, key) == 0)
            {
                result = keys.second;

                break;
            }
        }

        return result;
    }

    Fractal::ColorMode Find(Fractal::Mapping &unordered_map, std::string str)
    {
        return Fractal::Find(unordered_map, str.c_str());
    }

    class Parameters
    {
    public:
        std::string type;

        // image size
        int x_pixels = 2048;
        int y_pixels = 2048;

        // mandelbrot parameter(s)
        int max_iterations = 255;
        int exponent = 2;
        int bailout = -1;
        double orbit = 2.0;
        double shift_value = 0.0;

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
        int inside_color = 0;

        // bailout color
        int bailout_color = 0;

        // invert colors
        bool invert_colors = false;

        // invert axis
        bool invert_x = false;
        bool invert_y = false;

        // inputs/result filter
        std::string inputs_filter = "z";
        std::string result_filter = "z";

        // transformations
        Fractal::Transformations transforms = Fractal::Transformations();

        // function
        std::string function = "";
        std::string function2 = "";

        // palette / colormap to use
        std::string palette = "";

        // color mode
        Fractal::ColorMode color_mode = Fractal::ColorMode::DEFAULT;

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
                this->max_iterations = !data["max_iterations"].is_null() ? (int)data["max_iterations"] : 255;
                this->orbit = !data["orbit"].is_null() ? (double)data["orbit"] : std::numeric_limits<double>::quiet_NaN();
                this->shift_value = !data["shift_value"].is_null() ? (double)data["shift_value"] : std::numeric_limits<double>::quiet_NaN();
                this->bailout = !data["bailout"].is_null() ? (int)data["bailout"] : std::numeric_limits<int>::quiet_NaN();

                // mandelbrot parameter
                this->exponent = !data["exponent"].is_null() ? (int)data["exponent"] : std::numeric_limits<int>::quiet_NaN();

                // newton parameter
                this->tolerance = !data["tolerance"].is_null() ? (double)data["tolerance"] : std::numeric_limits<double>::epsilon();

                // julia set
                this->cx = !data["cx"].is_null() ? (double)data["cx"] : std::numeric_limits<double>::quiet_NaN();
                this->cy = !data["cy"].is_null() ? (double)data["cy"] : std::numeric_limits<double>::quiet_NaN();

                // inside_color
                this->inside_color = !data["inside_color"].is_null() ? (int)data["inside_color"] : 0;

                // bailout_color
                this->bailout_color = !data["bailout_color"].is_null() ? (int)data["bailout_color"] : 0;

                // invert axis
                this->invert_x = !data["invert_x"].is_null() ? (bool)data["invert_x"] : false;
                this->invert_y = !data["invert_y"].is_null() ? (bool)data["invert_y"] : false;

                // input/output filters
                this->inputs_filter = !data["inputs_filter"].is_null() ? std::string(data["inputs_filter"]) : std::string("z");
                this->result_filter = !data["result_filter"].is_null() ? std::string(data["result_filter"]) : std::string("z");

                // invert colors
                this->invert_colors = !data["invert_colors"].is_null() ? (bool)data["invert_colors"] : false;

                // functions
                this->function = !data["function"].is_null() ? std::string(data["function"]) : "";
                this->function2 = !data["function2"].is_null() ? std::string(data["function2"]) : "";

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

                // palette / colormap
                this->palette = !data["palette"].is_null() ? std::string(data["palette"]) : "";

                // color mode
                this->color_mode = !data["color_mode"].is_null() ? Fractal::Find(ColorModeMapping, std::string(data["color_mode"])) : Fractal::ColorMode::DEFAULT;

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
