CC = clang++
LINKER_FLAGS=-O3 -std=c++17 -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDES=-I/usr/include/SDL2

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS += -stdlib=libc++
	INCLUDES += -I/usr/local/include/SDL2
else
	LINKER_FLAGS += -lstdc++fs
endif

all: clean mandel mandel2

mandel:
	$(CC) Mandelbrot.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot.exe

mandel2:
	$(CC) Mandelbrot2.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot2.exe

clean:
	rm -f *.exe *.o
