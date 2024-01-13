CXX = g++
CFLAGS = -Wall -Wextra -O0 -ggdb
UNAME_S := $(shell uname -s)

# Default to an error message for unsupported OS,
# but override for supported OSes below.
BUILD_UNSUPPORTED := yes

ifeq ($(UNAME_S),Linux)
    LIBS = -L/usr/lib -lglfw -lGL -lGLEW
    INCLUDES = -I/path/to/linux/includes
    BUILD_UNSUPPORTED := no
endif

ifeq ($(UNAME_S),Darwin) # macOS
    LIBS = -L/usr/local/lib -lglfw -lGLEW -framework OpenGL
    INCLUDES = -I/usr/local/include
    BUILD_UNSUPPORTED := no
endif

# Terminate Makefile for unsupported OS
ifeq ($(BUILD_UNSUPPORTED),yes)
    $(error Unsupported operating system: $(UNAME_S))
endif

# Common build rules
all: simulate boid-test

simulate: vector.o boid.o flock.o solid.o obstacle.o simulate.o
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

boid-test: vector.o boid.o flock.o solid.o obstacle.o boid-test.o
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) simulate boid-test *.o *.dSYM
