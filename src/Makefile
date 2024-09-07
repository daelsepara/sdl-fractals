LINKER_FLAGS=-O3 -std=c++17 -lSDL2 -lSDL2_image
INCLUDES=-I/usr/include/SDL2
FS_LIB=-lstdc++fs
CC=clang++

UNAME_S=$(shell uname -s)
UNAME_M=$(shell uname -m)

ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS += -stdlib=libc++
	INCLUDES += -I/usr/local/include/SDL2
	FS_LIB=
else ifeq ($(UNAME_M),aarch64)
	CC=g++
else ifeq ($(UNAME_M),aarch32)
	CC=g++
endif

all: main

main:
	$(CC) Fractals.cpp $(LINKER_FLAGS) $(FS_LIB) $(INCLUDES) -o Fractals.exe

clean:
	rm -f *.exe *.o
