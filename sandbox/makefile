CXX	 = g++
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I/usr/include/GLFW
LIBS = -L/usr/lib/x86_64-linux-gnu -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

all: simulate boid-test

simulate: vector.o boid.o flock.o simulate.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

boid-test: vector.o boid.o flock.o boid-test.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

clean:
	${RM} simulate boid-test *.o *.dSYM
