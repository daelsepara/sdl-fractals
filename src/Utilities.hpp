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
    typedef void (*FunctionPointer)(double &a, double &b);

    const double eps = std::numeric_limits<double>::epsilon();

    Grid InitializeGrid(Fractal::Parameters &parameters)
    {
        // create complex plane
        return Fractal::Grid(parameters.y_pixels, Fractal::GridRow(parameters.x_pixels, 0));
    }

    SDL_Surface *GenerateSurface(Fractal::Grid &grid, Fractal::Parameters &parameters, Fractal::Palette &palette)
    {
        auto surface = SDL_CreateRGBSurface(0, parameters.x_pixels, parameters.y_pixels, 32, 0, 0, 0, 0);

        if (surface && grid.size() >= parameters.y_pixels && grid[0].size() >= parameters.x_pixels)
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

                    auto color = (int)grid[y][x];

                    // invert colors
                    if (parameters.invert_colors)
                    {
                        color = 255 - color;
                    }

                    // clamp to values 0-255 and calculate index to palette
                    auto c = std::min(std::max(color, 0), 255) * 3;

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

            if (parameters.palette.length() > 0)
            {
                palette.Load(parameters.palette);
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

        if (parameters.palette.length() > 0)
        {
            palette.Load(parameters.palette);
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

    void Divide(double a, double b, double c, double d, double &zx, double &zy)
    {
        auto denom = c * c + d * d;

        zx = (a * c + b * d) / denom;

        zy = (b * c - a * d) / denom;
    }

    double Mag2(double zx, double zy)
    {
        return zx * zx + zy * zy;
    }

    double Abs(double zx, double zy)
    {
        return std::sqrt(Fractal::Mag2(zx, zy));
    }

    double Mag(double zx, double zy)
    {
        return Fractal::Abs(zx, zy);
    }

    void Reciprocal(double &zx, double &zy)
    {
        auto mag2 = Fractal::Mag2(zx, zy) + eps;

        zx = zx / mag2;

        zy = -zy / mag2;
    }

    void Sin(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::sin(oldx) * std::cosh(oldy);

        zy = std::cos(oldx) * std::sinh(oldy);
    }

    void Cos(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::cos(oldx) * std::cosh(oldy);

        zy = -std::sin(oldx) * std::sinh(oldy);
    }

    void Exp(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        auto expx = std::exp(oldx);

        zx = expx * std::cos(oldy);

        zy = expx * std::sin(oldy);
    }

    void Tan(double &zx, double &zy)
    {
        auto sinzx = zx;

        auto sinzy = zy;

        auto coszx = zx;

        auto coszy = zy;

        Fractal::Sin(sinzx, sinzy);

        Fractal::Cos(coszx, coszy);

        Fractal::Divide(sinzx, sinzy, coszx, coszy, zx, zy);
    }

    void Cot(double &zx, double &zy)
    {
        Fractal::Tan(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Sec(double &zx, double &zy)
    {
        Fractal::Cos(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Csc(double &zx, double &zy)
    {
        Fractal::Sin(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Sinh(double &zx, double &zy)
    {
        auto ezx = zx;

        auto ezy = zy;

        auto nzx = -zx;

        auto nzy = -zy;

        Fractal::Exp(ezx, ezy);

        Fractal::Exp(nzx, nzy);

        zx = (ezx - nzx) / 2.0;

        zy = (ezy - nzy) / 2.0;
    }

    void Cosh(double &zx, double &zy)
    {
        auto ezx = zx;

        auto ezy = zy;

        auto nzx = -zx;

        auto nzy = -zy;

        Fractal::Exp(ezx, ezy);

        Fractal::Exp(nzx, nzy);

        zx = (ezx + nzx) / 2.0;

        zy = (ezy + nzy) / 2.0;
    }

    void Tanh(double &zx, double &zy)
    {
        auto sinhzx = zx;

        auto sinhzy = zy;

        auto coshzx = zx;

        auto coshzy = zy;

        Fractal::Sinh(sinhzx, sinhzy);

        Fractal::Cosh(coshzx, coshzy);

        Fractal::Divide(sinhzx, sinhzy, coshzx, coshzy, zx, zy);
    }

    void Coth(double &zx, double &zy)
    {
        Fractal::Tanh(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Sech(double &zx, double &zy)
    {
        Fractal::Cosh(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Csch(double &zx, double &zy)
    {
        Fractal::Sinh(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Conjugate(double &zx, double &zy)
    {
        zy = -zy;
    }

    void Sqr(double &zx, double &zy)
    {
        auto xtemp = zx * zx - zy * zy;

        zy = (zx + zx) * zy;

        zx = xtemp;
    }

    void Power(double &zx, double &zy, int exponent)
    {
        if (exponent == 0)
        {
            zx = 1.0;

            zy = 1.0;
        }
        else if (exponent == 2)
        {
            Fractal::Sqr(zx, zy);
        }
        else if (exponent > 2)
        {
            auto oldx = zx;

            auto oldy = zy;

            for (auto i = 0; i < exponent - 1; i++)
            {
                Fractal::Multiply(zx, zy, oldx, oldy, zx, zy);
            }
        }
        else if (exponent < 0)
        {
            Fractal::Reciprocal(zx, zy);

            Fractal::Power(zx, zy, -exponent);
        }
    }

    void Absolute(double &zx, double &zy)
    {
        zx = std::abs(zx);

        zy = std::abs(zy);
    }

    void Identity(double &zx, double &zy)
    {
        zx = zx;

        zy = zy;
    }

    Fractal::FunctionPointer MapFunction(std::string function)
    {
        if (function == "sin")
        {
            return Fractal::Sin;
        }
        else if (function == "cos")
        {
            return Fractal::Cos;
        }
        else if (function == "tan")
        {
            return Fractal::Tan;
        }
        else if (function == "cot")
        {
            return Fractal::Cot;
        }
        else if (function == "sec")
        {
            return Fractal::Sec;
        }
        else if (function == "csc")
        {
            return Fractal::Csc;
        }
        else if (function == "sinh")
        {
            return Fractal::Sinh;
        }
        else if (function == "cosh")
        {
            return Fractal::Cosh;
        }
        else if (function == "tanh")
        {
            return Fractal::Tanh;
        }
        else if (function == "coth")
        {
            return Fractal::Coth;
        }
        else if (function == "sech")
        {
            return Fractal::Sech;
        }
        else if (function == "csch")
        {
            return Fractal::Csch;
        }
        else if (function == "exp")
        {
            return Fractal::Exp;
        }
        else if (function == "conj")
        {
            return Fractal::Conjugate;
        }
        else if (function == "sqr")
        {
            return Fractal::Sqr;
        }
        else if (function == "reciprocal")
        {
            return Fractal::Reciprocal;
        }
        else if (function == "abs")
        {
            return Fractal::Absolute;
        }
        else
        {
            return Fractal::Identity;
        }
    }

    void ApplyTransformation(double x, double y, Fractal::Transformation &transform, double &xn, double &yn)
    {
        // transform[0] = x coefficient (xn)
        // transform[1] = y coefficient (xn)
        // transform[2] = x coefficient (yn)
        // transform[3] = y coefficient (yn)
        // transform[4] = constant (xn)
        // transform[5] = constant (yn)
        // transform[6] = probability
        if (transform.size() < 7)
        {
            return;
        }

        xn = transform[0] * x + transform[1] * y + transform[4];
        yn = transform[2] * x + transform[3] * y + transform[5];
    }

    void Transform(double p, double x, double y, Fractal::Transformations &transforms, double &xn, double &yn)
    {
        auto transform_p = 0.0;

        for (auto i = 0; i < transforms.size(); i++)
        {
            if (transforms[i].size() >= 7)
            {
                transform_p += transforms[i][6];

                if (p < transform_p)
                {
                    Fractal::ApplyTransformation(x, y, transforms[i], xn, yn);

                    break;
                }
            }
        }
    }

    int LogColor(int color, int max_value)
    {
        return (int)(std::log1p((double)color) / std::log1p((double)max_value) * 255.0);
    }

    int NormalizedColor(int color, int max_value)
    {
        return (int)(((double)color / (double)max_value) * 255.0);
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
                grid[y][x] = (Uint8)(grid[y][x] % 255);
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

        // pass 1: compute histogram
        for (auto y = 0; y < grid.size(); y++)
        {
            for (auto x = 0; x < grid[y].size(); x++)
            {
                NumIterationsPerPixel[grid[y][x]]++;
            }
        }

        // pass 2: compute total counts
        auto total = 0;

        for (auto i = NumIterationsPerPixel.begin(); i != NumIterationsPerPixel.end(); ++i)
        {
            total += i->second;
        }

        // pass 3: compute hue
        auto hue = std::vector<std::vector<int>>(grid.size(), std::vector<int>(grid[0].size(), 0));

        auto color_scaler = 1.0 / (double)total * 255.0;

        // pass 4: map to color
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

                grid[y][x] = (int)((double)hue[y][x] * color_scaler);
            }
        }
    }

    void FinalizeColors(Fractal::Grid &grid, Fractal::Parameters &parameters, int max_color)
    {
        if (parameters.log_coloring)
        {
            Fractal::Log(grid, max_color);
        }
        else if (parameters.normalized_coloring)
        {
            Fractal::Normalize(grid, max_color);
        }
        else if (parameters.mod_coloring)
        {
            Fractal::Mod(grid);
        }
        else if (parameters.histogram_coloring)
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
