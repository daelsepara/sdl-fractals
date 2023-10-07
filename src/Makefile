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

all: mandel1 mandel2 mandel3 main

mandel1:
	$(CC) Mandelbrot1.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot1.exe

mandel2:
	$(CC) Mandelbrot2.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot2.exe

mandel3:
	$(CC) Mandelbrot3.cpp $(LINKER_FLAGS) $(INCLUDES) -o Mandelbrot3.exe

main:
	$(CC) Fractals.cpp $(LINKER_FLAGS) $(INCLUDES) -o Fractals.exe

clean:
	rm -f *.exe *.o
