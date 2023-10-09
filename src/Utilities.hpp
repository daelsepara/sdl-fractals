#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Palette.hpp"
#include "Parameters.hpp"

namespace Fractal
{
    typedef std::vector<std::vector<Uint8>> Grid;

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

    SDL_Surface *GenerateSurface(Grid &grid, Fractal::Parameters &parameters, Fractal::Palette &palette)
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
                    Uint8 r = palette.Colors[c] * palette.Brightness;
                    Uint8 g = palette.Colors[c + 1] * palette.Brightness;
                    Uint8 b = palette.Colors[c + 2] * palette.Brightness;

                    // write pixel on surface
                    *target = (Uint32)(a << 24 | r << 16 | g << 8 | b);
                }
            }
        }

        return surface;
    }

    void RenderImage(Grid &grid, Fractal::Parameters &parameters, std::string palette_file)
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

            if (palette_file.length() > 0)
            {
                palette.Load(palette_file);
            }

            auto surface = Fractal::GenerateSurface(grid, parameters, palette);

            if (surface)
            {
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

                auto texture = SDL_CreateTextureFromSurface(renderer, surface);

                if (texture)
                {
                    // Event handler
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

                            SDL_RenderFillRect(renderer, &dst);

                            if (texture)
                            {
                                SDL_RenderCopy(renderer, texture, &src, &dst);
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

    void SaveImage(Grid &grid, Fractal::Parameters &parameters, std::string filename, std::string palette_file)
    {
        auto palette = Fractal::Palette();

        if (palette_file.length() > 0)
        {
            palette.Load(palette_file);
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

    void Multiply(double x, double y, double a, double b, double &zx, double &zy)
    {
        zx = (x * a - y * b);
        zy = (x * b + y * a);
    }

    void Divide(double x, double y, double a, double b, double &zx, double &zy)
    {
        auto denom = a * a + b * b;

        Fractal::Multiply(x / denom, y / denom, a, -b, zx, zy);
    }

    void Power(double &zx, double &zy, int exponent)
    {
        auto oldx = zx;

        auto oldy = zy;

        if (exponent == 0)
        {
            zx = 1.0;

            zy = 1.0;
        }
        else
        {
            for (auto i = 0; i < exponent - 1; i++)
            {
                Fractal::Multiply(zx, zy, oldx, oldy, zx, zy);
            }
        }
    }

    void ApplyTransformation(double x, double y, std::vector<double> &transform, double &xn, double &yn)
    {
        // transform[0] = probability
        // transform[1] = x coefficient (xn)
        // transform[2] = y coefficient (xn)
        // transform[3] = constant (xn)
        // transform[4] = x coefficient (yn)
        // transform[5] = y coefficient (yn)
        // transform[6] = constant (yn)
        if (transform.size() < 7)
        {
            return;
        }

        xn = transform[1] * x + transform[2] * y + transform[3];
        yn = transform[4] * x + transform[5] * y + transform[6];
    }

    void Transform(double p, double x, double y, std::vector<std::vector<double>> &transforms, double &xn, double &yn)
    {
        for (auto i = 0; i < transforms.size(); i++)
        {
            if (p < transforms[i][0])
            {
                Fractal::ApplyTransformation(x, y, transforms[i], xn, yn);

                break;
            }
        }
    }
}

#endif
