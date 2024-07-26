#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Palette.hpp"
#include "Parameters.hpp"

namespace Fractal
{
    Grid InitializeGrid(Fractal::Parameters &parameters)
    {
        // create complex plane
        return Fractal::Grid(parameters.YPixels, Fractal::GridRow(parameters.XPixels, 0));
    }

    SDL_Surface *GenerateSurface(Fractal::Grid &grid, Fractal::Parameters &parameters, Fractal::Palette &palette)
    {
        auto surface = SDL_CreateRGBSurface(0, parameters.XPixels, parameters.YPixels, 32, 0, 0, 0, 0);

        if (surface && grid.size() >= parameters.YPixels && grid[0].size() >= parameters.XPixels)
        {
            // set fixed alpha channel value
            Uint8 a = 255;

            auto color = 0;

            auto c = 0;

            Uint32 *target = NULL;

            Uint8 r, g, b;

            // write to ARGB surface
            for (auto y = 0; y < parameters.YPixels; y++)
            {
                for (auto x = 0; x < parameters.XPixels; x++)
                {
                    // calculate target pixel
                    target = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

                    color = grid[y][x];

                    // invert colors
                    if (parameters.InvertColors)
                    {
                        color = 255 - color;
                    }

                    // clamp to values 0-255 and calculate index to palette
                    c = std::min(std::max(color, 0), 255) * 3;

                    // get RGB color from palette and adjust color brightness
                    r = palette.Colors[c] * palette.Brightness;

                    g = palette.Colors[c + 1] * palette.Brightness;

                    b = palette.Colors[c + 2] * palette.Brightness;

                    // write pixel on surface
                    *target = (Uint32)(a << 24 | r << 16 | g << 8 | b);
                }
            }
        }

        return surface;
    }

    void RenderImage(Fractal::Grid &grid, Fractal::Parameters &parameters)
    {
        // window
        SDL_Window *window = NULL;

        // renderer
        SDL_Renderer *renderer = NULL;

        auto Width = 1280;

        auto Height = 1024;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;

            std::exit(1);
        }
        else
        {
            SDL_DisplayMode mode;

            SDL_GetCurrentDisplayMode(0, &mode);

            Width = mode.w;

            Height = mode.h;

            SDL_CreateWindowAndRenderer(Width, Height, (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), &window, &renderer);

            if (!window || !renderer)
            {
                std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;

                std::exit(1);
            }

            if (window)
            {
                SDL_SetWindowTitle(window, "SDL Fractals");
            }

            if (renderer)
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            auto palette = Fractal::Palette();

            if (parameters.Palette.length() > 0)
            {
                palette.Load(parameters.Palette);
            }

            auto surface = Fractal::GenerateSurface(grid, parameters, palette);

            if (surface)
            {
                /*
                // TODO: Implement scrolling
                SDL_Rect dst;
                dst.x = Width > surface->w ? (Width - surface->w) / 2 : 0;
                dst.y = Height > surface->h ? (Height - surface->h) / 2 : 0;
                dst.w = Width > surface->w ? surface->w : Width;
                dst.h = Height > surface->h ? surface->h : Height;

                SDL_Rect src;
                src.x = surface->w > Width ? (surface->w - Width) / 2 : 0;
                src.y = surface->h > Height ? (surface->h - Height) / 2 : 0;
                src.w = surface->w > Width ? Width : surface->w;
                src.h = surface->h > Height ? Height : surface->h;
                */

                auto texture = SDL_CreateTextureFromSurface(renderer, surface);

                if (texture)
                {
                    SDL_Event e;

                    auto quit = false;

                    while (!quit)
                    {
                        while (SDL_PollEvent(&e) != 0)
                        {
                            // User requests quit
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                            }
                            else if (e.type == SDL_KEYDOWN)
                            {
                                quit = true;
                            }

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                            SDL_RenderFillRect(renderer, NULL);

                            if (texture)
                            {
                                // TODO: Implement scrolling
                                // SDL_RenderCopy(renderer, texture, &src, &dst);
                                SDL_RenderCopy(renderer, texture, NULL, NULL);
                            }

                            SDL_RenderPresent(renderer);
                        }
                    }

                    SDL_DestroyTexture(texture);
                }

                SDL_FreeSurface(surface);
            }

            SDL_DestroyRenderer(renderer);

            SDL_DestroyWindow(window);
        }

        SDL_Quit();
    }

    void SaveImage(Fractal::Grid &grid, Fractal::Parameters &parameters, std::string filename)
    {
        auto palette = Fractal::Palette();

        if (parameters.Palette.length() > 0)
        {
            palette.Load(parameters.Palette);
        }

        auto surface = Fractal::GenerateSurface(grid, parameters, palette);

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

    int LogColor(int color, int max_value)
    {
        return int(std::log1p(double(color)) / std::log1p(double(max_value)) * 255.0);
    }

    int NormalizedColor(int color, int max_value)
    {
        return int(double(color) / double(max_value) * 255.0);
    }

    int ClampColor(int color)
    {
        return std::min(std::max(0, color), 255);
    }

    void Log(Fractal::Grid &grid, int max_color)
    {
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                grid[y][x] = Fractal::LogColor(grid[y][x], max_color);
            }
        }
    }

    void Normalize(Fractal::Grid &grid, int max_color)
    {
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                grid[y][x] = Fractal::NormalizedColor(grid[y][x], max_color);
            }
        }
    }

    void Mod(Fractal::Grid &grid)
    {
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                grid[y][x] = Uint8(grid[y][x] % 255);
            }
        }
    }

    void Clamp(Fractal::Grid &grid)
    {
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                grid[y][x] = Fractal::ClampColor(grid[y][x]);
            }
        }
    }

    void Histogram(Fractal::Grid &grid)
    {
        auto NumIterationsPerPixel = std::map<int, int>();

        auto total = 0;

        // pass 1: compute histogram and total counts
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                NumIterationsPerPixel[grid[y][x]]++;

                total++;
            }
        }

        // pass 2: compute hue
        auto hue = std::vector<std::vector<int>>(grid.size(), std::vector<int>(grid[0].size(), 0));

        auto color_scaler = 1.0 / double(total) * 255.0;

        // pass 3: map to color
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                for (auto i = NumIterationsPerPixel.begin(); i != NumIterationsPerPixel.end(); ++i)
                {
                    if (i->first <= grid[y][x])
                    {
                        hue[y][x] += i->second;
                    }
                }

                grid[y][x] = int(double(hue[y][x]) * color_scaler);
            }
        }
    }

    void FinalizeColors(Fractal::Grid &grid, Fractal::Parameters &parameters, int max_color)
    {
        if (parameters.ColorMode == Fractal::ColorMode::LOG)
        {
            Fractal::Log(grid, max_color);
        }
        else if (parameters.ColorMode == Fractal::ColorMode::NORMALIZED)
        {
            Fractal::Normalize(grid, max_color);
        }
        else if (parameters.ColorMode == Fractal::ColorMode::MODULUS)
        {
            Fractal::Mod(grid);
        }
        else if (parameters.ColorMode == Fractal::ColorMode::HISTOGRAM)
        {
            Fractal::Histogram(grid);
        }
        else
        {
            Fractal::Clamp(grid);
        }
    }
}

#endif
