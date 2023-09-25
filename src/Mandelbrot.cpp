#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    auto scale_x = 512;
    auto scale_y = 512;
    auto escape_time_threshold = 255;
    auto escape_value_threshold = 2.0;

    auto grid = std::vector<std::vector<short int>>(scale_y);

    // initialize 100 x 100 grid
    for (auto y = 0; y < scale_y; y++)
    {
        grid[y] = std::vector<short int>(scale_x);
    }

    std::cout << "P3" << std::endl;
    std::cout << scale_x << " " << scale_y << std::endl;
    std::cout << "255" << std::endl;

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

            std::cout << r << " " << g << " " << b << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}