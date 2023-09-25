#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv)
{
    // from: https://github.com/Raffaello/sdl2-vga-terminal/blob/master/sdl2-vga-terminal/src/vgapalette.h
    Uint8 palette[768] =
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x2a, 0x00, 0x00, 0x2a, 0x2a, 0x2a, 0x00, 0x00, 0x2a, 0x00, 0x2a, 0x2a, 0x15, 0x00, 0x2a, 0x2a, 0x2a,
            0x15, 0x15, 0x15, 0x15, 0x15, 0x3f, 0x15, 0x3f, 0x15, 0x15, 0x3f, 0x3f, 0x3f, 0x15, 0x15, 0x3f, 0x15, 0x3f, 0x3f, 0x3f, 0x15, 0x3f, 0x3f, 0x3f,
            0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x08, 0x08, 0x08, 0x0b, 0x0b, 0x0b, 0x0e, 0x0e, 0x0e, 0x11, 0x11, 0x11, 0x14, 0x14, 0x14, 0x18, 0x18, 0x18,
            0x1c, 0x1c, 0x1c, 0x20, 0x20, 0x20, 0x24, 0x24, 0x24, 0x28, 0x28, 0x28, 0x2d, 0x2d, 0x2d, 0x32, 0x32, 0x32, 0x38, 0x38, 0x38, 0x3f, 0x3f, 0x3f,
            0x00, 0x00, 0x3f, 0x10, 0x00, 0x3f, 0x1f, 0x00, 0x3f, 0x2f, 0x00, 0x3f, 0x3f, 0x00, 0x3f, 0x3f, 0x00, 0x2f, 0x3f, 0x00, 0x1f, 0x3f, 0x00, 0x10,
            0x3f, 0x00, 0x00, 0x3f, 0x10, 0x00, 0x3f, 0x1f, 0x00, 0x3f, 0x2f, 0x00, 0x3f, 0x3f, 0x00, 0x2f, 0x3f, 0x00, 0x1f, 0x3f, 0x00, 0x10, 0x3f, 0x00,
            0x00, 0x3f, 0x00, 0x00, 0x3f, 0x10, 0x00, 0x3f, 0x1f, 0x00, 0x3f, 0x2f, 0x00, 0x3f, 0x3f, 0x00, 0x2f, 0x3f, 0x00, 0x1f, 0x3f, 0x00, 0x10, 0x3f,
            0x1f, 0x1f, 0x3f, 0x27, 0x1f, 0x3f, 0x2f, 0x1f, 0x3f, 0x37, 0x1f, 0x3f, 0x3f, 0x1f, 0x3f, 0x3f, 0x1f, 0x37, 0x3f, 0x1f, 0x2f, 0x3f, 0x1f, 0x27,

            0x3f, 0x1f, 0x1f, 0x3f, 0x27, 0x1f, 0x3f, 0x2f, 0x1f, 0x3f, 0x37, 0x1f, 0x3f, 0x3f, 0x1f, 0x37, 0x3f, 0x1f, 0x2f, 0x3f, 0x1f, 0x27, 0x3f, 0x1f,
            0x1f, 0x3f, 0x1f, 0x1f, 0x3f, 0x27, 0x1f, 0x3f, 0x2f, 0x1f, 0x3f, 0x37, 0x1f, 0x3f, 0x3f, 0x1f, 0x37, 0x3f, 0x1f, 0x2f, 0x3f, 0x1f, 0x27, 0x3f,
            0x2d, 0x2d, 0x3f, 0x31, 0x2d, 0x3f, 0x36, 0x2d, 0x3f, 0x3a, 0x2d, 0x3f, 0x3f, 0x2d, 0x3f, 0x3f, 0x2d, 0x3a, 0x3f, 0x2d, 0x36, 0x3f, 0x2d, 0x31,
            0x3f, 0x2d, 0x2d, 0x3f, 0x31, 0x2d, 0x3f, 0x36, 0x2d, 0x3f, 0x3a, 0x2d, 0x3f, 0x3f, 0x2d, 0x3a, 0x3f, 0x2d, 0x36, 0x3f, 0x2d, 0x31, 0x3f, 0x2d,
            0x2d, 0x3f, 0x2d, 0x2d, 0x3f, 0x31, 0x2d, 0x3f, 0x36, 0x2d, 0x3f, 0x3a, 0x2d, 0x3f, 0x3f, 0x2d, 0x3a, 0x3f, 0x2d, 0x36, 0x3f, 0x2d, 0x31, 0x3f,
            0x00, 0x00, 0x1c, 0x07, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x15, 0x00, 0x1c, 0x1c, 0x00, 0x1c, 0x1c, 0x00, 0x15, 0x1c, 0x00, 0x0e, 0x1c, 0x00, 0x07,
            0x1c, 0x00, 0x00, 0x1c, 0x07, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x15, 0x00, 0x1c, 0x1c, 0x00, 0x15, 0x1c, 0x00, 0x0e, 0x1c, 0x00, 0x07, 0x1c, 0x00,
            0x00, 0x1c, 0x00, 0x00, 0x1c, 0x07, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x15, 0x00, 0x1c, 0x1c, 0x00, 0x15, 0x1c, 0x00, 0x0e, 0x1c, 0x00, 0x07, 0x1c,

            0x0e, 0x0e, 0x1c, 0x11, 0x0e, 0x1c, 0x15, 0x0e, 0x1c, 0x18, 0x0e, 0x1c, 0x1c, 0x0e, 0x1c, 0x1c, 0x0e, 0x18, 0x1c, 0x0e, 0x15, 0x1c, 0x0e, 0x11,
            0x1c, 0x0e, 0x0e, 0x1c, 0x11, 0x0e, 0x1c, 0x15, 0x0e, 0x1c, 0x18, 0x0e, 0x1c, 0x1c, 0x0e, 0x18, 0x1c, 0x0e, 0x15, 0x1c, 0x0e, 0x11, 0x1c, 0x0e,
            0x0e, 0x1c, 0x0e, 0x0e, 0x1c, 0x11, 0x0e, 0x1c, 0x15, 0x0e, 0x1c, 0x18, 0x0e, 0x1c, 0x1c, 0x0e, 0x18, 0x1c, 0x0e, 0x15, 0x1c, 0x0e, 0x11, 0x1c,
            0x14, 0x14, 0x1c, 0x16, 0x14, 0x1c, 0x18, 0x14, 0x1c, 0x1a, 0x14, 0x1c, 0x1c, 0x14, 0x1c, 0x1c, 0x14, 0x1a, 0x1c, 0x14, 0x18, 0x1c, 0x14, 0x16,
            0x1c, 0x14, 0x14, 0x1c, 0x16, 0x14, 0x1c, 0x18, 0x14, 0x1c, 0x1a, 0x14, 0x1c, 0x1c, 0x14, 0x1a, 0x1c, 0x14, 0x18, 0x1c, 0x14, 0x16, 0x1c, 0x14,
            0x14, 0x1c, 0x14, 0x14, 0x1c, 0x16, 0x14, 0x1c, 0x18, 0x14, 0x1c, 0x1a, 0x14, 0x1c, 0x1c, 0x14, 0x1a, 0x1c, 0x14, 0x18, 0x1c, 0x14, 0x16, 0x1c,
            0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 0x00, 0x10, 0x0c, 0x00, 0x10, 0x10, 0x00, 0x10, 0x10, 0x00, 0x0c, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04,
            0x10, 0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 0x00, 0x10, 0x0c, 0x00, 0x10, 0x10, 0x00, 0x0c, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04, 0x10, 0x00,

            0x00, 0x10, 0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 0x00, 0x10, 0x0c, 0x00, 0x10, 0x10, 0x00, 0x0c, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04, 0x10,
            0x08, 0x08, 0x10, 0x0a, 0x08, 0x10, 0x0c, 0x08, 0x10, 0x0e, 0x08, 0x10, 0x10, 0x08, 0x10, 0x10, 0x08, 0x0e, 0x10, 0x08, 0x0c, 0x10, 0x08, 0x0a,
            0x10, 0x08, 0x08, 0x10, 0x0a, 0x08, 0x10, 0x0c, 0x08, 0x10, 0x0e, 0x08, 0x10, 0x10, 0x08, 0x0e, 0x10, 0x08, 0x0c, 0x10, 0x08, 0x0a, 0x10, 0x08,
            0x08, 0x10, 0x08, 0x08, 0x10, 0x0a, 0x08, 0x10, 0x0c, 0x08, 0x10, 0x0e, 0x08, 0x10, 0x10, 0x08, 0x0e, 0x10, 0x08, 0x0c, 0x10, 0x08, 0x0a, 0x10,
            0x0b, 0x0b, 0x10, 0x0c, 0x0b, 0x10, 0x0d, 0x0b, 0x10, 0x0f, 0x0b, 0x10, 0x10, 0x0b, 0x10, 0x10, 0x0b, 0x0f, 0x10, 0x0b, 0x0d, 0x10, 0x0b, 0x0c,
            0x10, 0x0b, 0x0b, 0x10, 0x0c, 0x0b, 0x10, 0x0d, 0x0b, 0x10, 0x0f, 0x0b, 0x10, 0x10, 0x0b, 0x0f, 0x10, 0x0b, 0x0d, 0x10, 0x0b, 0x0c, 0x10, 0x0b,
            0x0b, 0x10, 0x0b, 0x0b, 0x10, 0x0c, 0x0b, 0x10, 0x0d, 0x0b, 0x10, 0x0f, 0x0b, 0x10, 0x10, 0x0b, 0x0f, 0x10, 0x0b, 0x0d, 0x10, 0x0b, 0x0c, 0x10,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    auto scale_x = 1024;
    auto scale_y = 1024;
    auto escape_time_threshold = 255;
    auto escape_value_threshold = 2.0;

    auto grid = std::vector<std::vector<short int>>(scale_y);

    // initialize grid
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

    // calculate mandelbrot set
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

            Uint8 c = grid[y][x];

            Uint8 a = 0;

            auto r = palette[c * 3];
            auto g = palette[c * 3 + 1];
            auto b = palette[c * 3 + 2];

            auto pixel = (Uint32)(a << 24 | r << 16 | g << 8 | b);

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
