#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv)
{
    auto scale_x = 1024;
    auto scale_y = 1024;
    auto escape_time_threshold = 32;
    auto escape_value_threshold = 2.0;

    auto grid = std::vector<std::vector<short int>>(scale_y);

    // initialize 100 x 100 grid
    for (auto y = 0; y < scale_y; y++)
    {
        grid[y] = std::vector<short int>(scale_x);
    }

    auto min_x = -2.0;
    auto max_x = 1.0;
    auto min_y = -1.5;
    auto max_y = 1.5;

    auto dx = (double)(max_x - min_x) / (double)(scale_x);
    auto dy = (double)(max_y - min_y) / (double)(scale_y);

    // calculate escape time
    for (auto y = 0; y < scale_y; y++)
    {
        for (auto x = 0; x < scale_x; x++)
        {
            short int t = 0;

            auto z = std::complex(0.0, 0.0);
            auto cx = min_x + (double)x * dx;
            auto cy = min_y + (double)(scale_y - y - 1) * dy;
            auto c = std::complex(cx, cy);

            while (abs(z) <= escape_value_threshold && (t < escape_time_threshold))
            {
                z = pow(z, 2.0) + c;

                t++;
            }

            grid[y][x] = t;

            auto r = grid[y][x];
            auto g = grid[y][x];
            auto b = grid[y][x];
        }
    }

    auto surface = SDL_CreateRGBSurface(0, scale_x, scale_y, 32, 0, 0, 0, 0);

    // write to ARGB surface
    for (auto y = 0; y < scale_y; y++)
    {
        for (auto x = 0; x < scale_x; x++)
        {
            Uint32 *const target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

            // stretch color
            Uint8 c = (Uint8)((double)grid[y][x] / (double)escape_time_threshold * 255.0);

            Uint8 alpha = 0;

            auto pixel = (Uint32)(0 << 24 | c << 16 | c << 8 | c);

            *target_pixel = pixel;
        }
    }

    if (surface)
    {
        IMG_Init(IMG_INIT_PNG);

        IMG_SavePNG(surface, "mandel.png");

        IMG_Quit();

        SDL_FreeSurface(surface);

        surface = NULL;
    }

    return 0;
}
