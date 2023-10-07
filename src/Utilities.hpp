#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <fstream>
#include <limits>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "nlohmann/json.hpp"
#include "Palette.hpp"
#include "Parameters.hpp"

namespace Fractal
{
    typedef std::vector<std::vector<Uint8>> Grid;

    Fractal::Parameters Load(std::string filename)
    {
        Fractal::Parameters parameters;

        std::ifstream file(filename);

        if (file.good())
        {
            std::cerr << "Loading parameters from " << filename << std::endl;

            auto data = nlohmann::json::parse(file);

            // fractal type
            parameters.type = !data["type"].is_null() ? std::string(data["type"]) : std::string("mandelbrot");
            
            // window borders on the comlex plane
            parameters.min_x = !data["min_x"].is_null() ? (double)data["min_x"] : -2.5;
            parameters.max_x = !data["max_x"].is_null() ? (double)data["max_x"] : 2.5;
            parameters.min_y = !data["min_y"].is_null() ? (double)data["min_y"] : -2.5;
            parameters.max_y = !data["max_y"].is_null() ? (double)data["max_y"] : 2.5;
            
            // fractal dimensions (in pixels)
            parameters.x_pixels = !data["x_pixels"].is_null() ? (int)data["x_pixels"] : 2048;
            parameters.y_pixels = !data["y_pixels"].is_null() ? (int)data["y_pixels"] : 2048;
            
            // parameters for escape time type of fractals
            parameters.escape_time_threshold = !data["escape_time_threshold"].is_null() ? (int)data["escape_time_threshold"] : std::numeric_limits<int>::quiet_NaN();
            parameters.escape_value_threshold = !data["escape_value_threshold"].is_null() ? (double)data["escape_value_threshold"] : std::numeric_limits<double>::quiet_NaN();
            
            // mandelbrot parameter
            parameters.exponent = !data["exponent"].is_null() ? (double)data["exponent"] : std::numeric_limits<double>::quiet_NaN();

            // newton parameter
            parameters.tolerance = !data["tolerance"].is_null() ? (double)data["tolerance"] : std::numeric_limits<double>::epsilon();

            file.close();
        }
        else
        {
            std::cerr << "Unable to laod parameters from " << filename << std::endl;
        }

        return parameters;
    }

    Grid InitializeGrid(Fractal::Parameters &parameters)
    {
        // create complex plane
        auto grid = std::vector<std::vector<Uint8>>(parameters.y_pixels);

        // initialize grid
        for (auto y = 0; y < parameters.y_pixels; y++)
        {
            grid[y] = std::vector<Uint8>(parameters.x_pixels);
        }

        return grid;
    }

    SDL_Surface *GenerateSurface(Grid &grid, Fractal::Parameters &parameters)
    {
        auto surface = SDL_CreateRGBSurface(0, parameters.x_pixels, parameters.y_pixels, 32, 0, 0, 0, 0);

        if (surface)
        {
            // set fixed alpha channel value
            Uint8 a = 255;

            // write to ARGB surface
            for (auto y = 0; y < parameters.y_pixels; y++)
            {
                for (auto x = 0; x < parameters.x_pixels; x++)
                {
                    // calculate target pixel
                    Uint32 *const target = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

                    // clamp to values 0-255 and calculate index to palette
                    auto c = std::min(std::max((int)grid[y][x], 0), 255) * 3;

                    // get RGB color from palette and adjust color brightness
                    auto brightness = 4;
                    Uint8 r = Fractal::Palette[c] * brightness;
                    Uint8 g = Fractal::Palette[c + 1] * brightness;
                    Uint8 b = Fractal::Palette[c + 2] * brightness;

                    // write pixel on surface
                    *target = (Uint32)(a << 24 | r << 16 | g << 8 | b);
                }
            }
        }

        return surface;
    }

    void SaveImage(Grid &grid, Fractal::Parameters &parameters, std::string filename)
    {
        auto surface = Fractal::GenerateSurface(grid, parameters);

        if (surface)
        {
            std::cerr << "Saving fractal to '" << filename << "'" << std::endl;

            // save surface as png file
            IMG_Init(IMG_INIT_PNG);

            IMG_SavePNG(surface, filename.c_str());

            IMG_Quit();

            // clean-up
            SDL_FreeSurface(surface);
        }
    }
}

#endif
