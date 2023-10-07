#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "nlohmann/json.hpp"
#include "palette.hpp"
#include "parameters.hpp"

namespace Fractal
{
    typedef std::vector<std::vector<Uint8>> Grid;

    Fractal::Parameters Load(std::string filename)
    {
        Fractal::Parameters parameters;

        std::ifstream file(filename);

        if (file.good())
        {
            auto data = nlohmann::json::parse(file);

            parameters.type = !data["type"].is_null() ? std::string(data["type"]) : std::string("mandelbrot");

            parameters.x_pixels = !data["x_pixels"].is_null() ? (int)data["x_pixels"] : 2048;
            parameters.y_pixels = !data["y_pixels"].is_null() ? (int)data["y_pixels"] : 2048;
            
            parameters.escape_time_threshold = !data["escape_time_threshold"].is_null() ? (int)data["escape_time_threshold"] : 255;
            parameters.escape_value_threshold = !data["escape_value_threshold"].is_null() ? (double)data["escape_value_threshold"] : 2.0;
            parameters.exponent = !data["exponent"].is_null() ? (double)data["exponent"] : 2.0;
            
            parameters.min_x = !data["min_x"].is_null() ? (double)data["min_x"] : -2.5;
            parameters.max_x = !data["max_x"].is_null() ? (double)data["max_x"] : 2.5;
            parameters.min_y = !data["min_y"].is_null() ? (double)data["min_y"] : -2.5;
            parameters.max_y = !data["max_y"].is_null() ? (double)data["max_y"] : 2.5;

            file.close();
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

    void SaveImage(Grid &grid, Fractal::Parameters &parameters, std::string filename)
    {
        auto surface = SDL_CreateRGBSurface(0, parameters.x_pixels, parameters.y_pixels, 32, 0, 0, 0, 0);

        if (surface)
        {
            std::cerr << "Saving fractal to '" << filename << "'" << std::endl;

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
                    Uint8 r = palette[c] * brightness;
                    Uint8 g = palette[c + 1] * brightness;
                    Uint8 b = palette[c + 2] * brightness;
                    // write pixel on surface
                    *target = (Uint32)(a << 24 | r << 16 | g << 8 | b);
                }
            }

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