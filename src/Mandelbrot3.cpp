#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "palette.hpp"

int main(int argc, char **argv)
{
    // size of fractal image
    auto x_pixels = 2048;
    auto y_pixels = 2048;

    // mandelbrot parameter(s)
    Uint8 escape_time_threshold = 255;
    auto escape_value_threshold = 2.0;
    auto exponent = 2.0;

    // complex plane window boundaries
    auto min_x = -2.5;
    auto max_x = 2.5;
    auto min_y = -2.5;
    auto max_y = 2.5;

    // calculate scaling factor
    auto dx = (double)(max_x - min_x) / (double)(x_pixels);
    auto dy = (double)(max_y - min_y) / (double)(y_pixels);

    // create complex plane
    auto grid = std::vector<std::vector<Uint8>>(y_pixels);

    // initialize grid
    for (auto y = 0; y < y_pixels; y++)
    {
        grid[y] = std::vector<Uint8>(x_pixels);
    }

    // calculate mandelbrot set
    for (auto y = 0; y < y_pixels; y++)
    {
        for (auto x = 0; x < x_pixels; x++)
        {
            Uint8 t = 0;

            // calculate location (cx, cy) on complex plane
            auto cx = min_x + (double)x * dx;
            // reverse y-location on image, i.e. - to + runs from top to bottom of the image
            auto cy = min_y + (double)(y_pixels - y - 1) * dy;
            // initial condition z0 (zx, zy)
            auto zx = 0.0;
            auto zy = 0.0;
            auto xx = 0.0;
            auto yy = 0.0;
            // generate escape time fractal
            while ((zx + zy) <= escape_value_threshold * escape_value_threshold && (t < escape_time_threshold))
            {
                yy = 2 * xx * yy + cy;
                xx = zx - zy + cx;
                zx = xx * xx;
                zy = yy * yy;
                t++;
            }

            // set escape-time color
            grid[y][x] = t;
        }
    }

    auto surface = SDL_CreateRGBSurface(0, x_pixels, y_pixels, 32, 0, 0, 0, 0);

    if (surface)
    {
        // write to ARGB surface
        for (auto y = 0; y < y_pixels; y++)
        {
            for (auto x = 0; x < x_pixels; x++)
            {
                // calculate target pixel
                Uint32 *const target = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
                // set alpha channel
                Uint8 a = 255;
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

        IMG_SavePNG(surface, "mandel3.png");

        IMG_Quit();

        // clean-up
        SDL_FreeSurface(surface);
    }

    return 0;
}
