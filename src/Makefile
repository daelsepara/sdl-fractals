LINKER_FLAGS=-O3 -std=c++17 -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDES=-I/usr/include/SDL2

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS += -stdlib=libc++
	INCLUDES += -I/usr/local/include/SDL2
	CC = clang++
else
	LINKER_FLAGS += -lstdc++fs
	CC = g++
endif

all: main

main:
	$(CC) Fractals.cpp $(LINKER_FLAGS) $(INCLUDES) -o Fractals.exe

clean:
	rm -f *.exe *.o
