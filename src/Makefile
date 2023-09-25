CC = clang++
SDLFRACTALS_SOURCE = SDLFractals.cpp
SDLFRACTALS_OUTPUT = SDLFractals.exe
LINKER_FLAGS=-O3 -std=c++17 -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDES=-I/usr/include/SDL2

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS += -stdlib=libc++
	INCLUDES += -I/usr/local/include/SDL2
else
	LINKER_FLAGS += -lstdc++fs
endif

all: clean fractals mandel

fractals:
	$(CC) $(SDLFRACTALS_SOURCE) $(LINKER_FLAGS) $(INCLUDES) -o $(SDLFRACTALS_OUTPUT)

mandel:
	$(CC) Mandelbrot.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot.exe

clean:
	rm -f *.exe *.o
