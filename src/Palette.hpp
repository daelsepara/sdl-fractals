#ifndef __PALETTE_HPP__
#define __PALETTE_HPP__

#include <cstdlib>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>

#include "nlohmann/json.hpp"

namespace Fractal
{
    class Palette
    {
    public:
        // from: https://github.com/Raffaello/sdl2-vga-terminal/blob/master/sdl2-vga-terminal/src/vgapalette.h
        Uint8 Colors[768] =
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

        int Brightness = 4;

        void Clear()
        {
            std::memset(this->Colors, 0, 768);
        }

        void Load(std::string palette)
        {
            std::ifstream file(palette);

            if (file.good())
            {
                std::cerr << "Loading palette from " << palette << std::endl;

                auto data = nlohmann::json::parse(file);

                if (!data["colors"].is_null() && data["colors"].is_array() && data["colors"].size() > 0 && data["colors"].size() <= 768)
                {
                    this->Clear();

                    for (auto i = 0; i < data["colors"].size(); i++)
                    {
                        this->Colors[i] = (int)data["colors"][i];
                    }
                }

                this->Brightness = !data["brightness"].is_null() ? (int)data["brightness"] : 1;
            }

            file.close();
        }
    };
}
#endif
