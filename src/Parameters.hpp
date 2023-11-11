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
        // fractal type
        std::string Type;

        // image size
        int XPixels = 2048;

        int YPixels = 2048;

        // mandelbrot/julia parameter(s)
        int MaxIterations = 255;

        int Exponent = 2;

        int Bailout = -1;

        double EscapeValue = 4.0;

        double ShiftValue = 0.0;

        // Julia set parameters
        double cx = -0.8;

        double cy = 0.156;

        // complex plane window boundaries
        double MinX = -2.5;

        double MaxX = 2.5;

        double MinY = -2.5;

        double MaxY = 2.5;

        // Newton parameters
        double Tolerance = 0.000001;

        // inside color
        int InsideColor = 0;

        // bailout color
        int BailoutColor = 0;

        // invert colors
        bool InvertColors = false;

        // invert axis
        bool InvertX = false;

        bool InvertY = false;

        // inputs/result filter
        std::string InputsFilter = "z";

        std::string ResultFilter = "z";

        // transformations
        Fractal::Transformations Transforms = Fractal::Transformations();

        // functions
        std::vector<std::string> Functions = {"z"};

        // palette / colormap to use
        std::string Palette = "";

        // color mode
        Fractal::ColorMode ColorMode = Fractal::ColorMode::DEFAULT;

        // decomposition mode
        bool Decomp = false;

        double DeltaX()
        {
            return double(this->MaxX - this->MinX) / double(this->XPixels);
        }

        double DeltaY()
        {
            return double(this->MaxY - this->MinY) / double(this->YPixels);
        }

        double ScaledX(int x, double dx)
        {
            if (this->InvertX)
            {
                return this->MinX + double(this->XPixels - x - 1) * dx;
            }
            else
            {
                return this->MinX + double(x) * dx;
            }
        }

        double ScaledY(int y, double dy)
        {
            if (this->InvertY)
            {
                return this->MinY + double(y) * dy;
            }
            else
            {
                return this->MinY + double(this->YPixels - y - 1) * dy;
            }
        }

        int PixelX(double x, double dx)
        {
            if (this->InvertX)
            {
                return (this->XPixels - int((x - this->MinX) / dx) + 1);
            }
            else
            {
                return int((x - this->MinX) / dx);
            }
        }

        int PixelY(double y, double dy)
        {
            if (this->InvertY)
            {
                return int((y - this->MinY) / dy);
            }
            else
            {
                return (this->YPixels - int((y - this->MinY) / dy) + 1);
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
                this->Type = !data["type"].is_null() ? std::string(data["type"]) : std::string("mandelbrot");

                // borders on the complex plane
                this->MinX = !data["minX"].is_null() ? double(data["minX"]) : -2.5;

                this->MaxX = !data["maxX"].is_null() ? double(data["maxX"]) : 2.5;

                this->MinY = !data["minY"].is_null() ? double(data["minY"]) : -2.5;

                this->MaxY = !data["maxY"].is_null() ? double(data["maxY"]) : 2.5;

                // complex plane dimensions (in pixels)
                this->XPixels = !data["xPixels"].is_null() ? int(data["xPixels"]) : 2048;

                this->YPixels = !data["yPixels"].is_null() ? int(data["yPixels"]) : 2048;

                // parameters for escape time type of fractals
                this->MaxIterations = !data["maxIterations"].is_null() ? int(data["maxIterations"]) : 255;

                this->EscapeValue = !data["escapeValue"].is_null() ? double(data["escapeValue"]) : std::numeric_limits<double>::quiet_NaN();

                this->ShiftValue = !data["shiftValue"].is_null() ? double(data["shiftValue"]) : std::numeric_limits<double>::quiet_NaN();

                this->Bailout = !data["bailout"].is_null() ? int(data["bailout"]) : std::numeric_limits<int>::quiet_NaN();

                // mandelbrot parameter
                this->Exponent = !data["exponent"].is_null() ? int(data["exponent"]) : std::numeric_limits<int>::quiet_NaN();

                // newton parameter
                this->Tolerance = !data["tolerance"].is_null() ? double(data["tolerance"]) : std::numeric_limits<double>::epsilon();

                // julia set parameters
                this->cx = !data["cx"].is_null() ? double(data["cx"]) : std::numeric_limits<double>::quiet_NaN();

                this->cy = !data["cy"].is_null() ? double(data["cy"]) : std::numeric_limits<double>::quiet_NaN();

                // inside color
                this->InsideColor = !data["insideColor"].is_null() ? int(data["insideColor"]) : 0;

                // bailout color
                this->BailoutColor = !data["bailoutColor"].is_null() ? int(data["bailoutColor"]) : 0;

                // invert axis
                this->InvertX = !data["invertX"].is_null() ? bool(data["invertX"]) : false;

                this->InvertY = !data["invertY"].is_null() ? bool(data["invertY"]) : false;

                // input/output filters
                this->InputsFilter = !data["inputsFilter"].is_null() ? std::string(data["inputsFilter"]) : std::string("z");

                this->ResultFilter = !data["resultFilter"].is_null() ? std::string(data["resultFilter"]) : std::string("z");

                // invert colors
                this->InvertColors = !data["invertColors"].is_null() ? bool(data["invertColors"]) : false;

                // functions
                if (!data["functions"].is_null())
                {
                    this->Functions.clear();

                    if (data["functions"].is_array())
                    {
                        for (auto i = 0; i < data["functions"].size(); i++)
                        {
                            this->Functions.push_back(std::string(data["functions"][i]));
                        }
                    }
                    else
                    {
                        this->Functions.push_back(std::string(data["functions"]));
                    }
                }
                else
                {
                    this->Functions = {"z"};
                }

                // decomp
                this->Decomp = !data["decomp"].is_null() ? bool(data["decomp"]) : false;

                // transforms
                if (!data["transforms"].is_null() && data["transforms"].is_array())
                {
                    this->Transforms = Fractal::Transformations();

                    for (auto j = 0; j < data["transforms"].size(); j++)
                    {
                        if (!data["transforms"][j].is_null() && data["transforms"][j].is_array())
                        {
                            auto transform = Fractal::Transformation();

                            for (auto i = 0; i < data["transforms"][j].size(); i++)
                            {
                                auto val = !data["transforms"][j][i].is_null() ? double(data["transforms"][j][i]) : std::numeric_limits<double>::quiet_NaN();

                                transform.push_back(val);
                            }

                            this->Transforms.push_back(transform);
                        }
                    }
                }

                // palette / colormap
                this->Palette = !data["palette"].is_null() ? std::string(data["palette"]) : "";

                // color mode
                this->ColorMode = !data["colorMode"].is_null() ? Fractal::Find(ColorModeMapping, std::string(data["colorMode"])) : Fractal::ColorMode::DEFAULT;

                file.close();
            }
            else
            {
                std::cerr << "Unable to load parameters from " << filename << std::endl;
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
