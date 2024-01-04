CXX	 = g++
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I/usr/include/GLFW
LIBS = -L/usr/lib/x86_64-linux-gnu -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

all: simulate boid-test

simulate: simulate.o boid.o vector.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

boid-test: boid.o vector.o boid-test.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

clean:
	${RM} simulate boid-test *.0 *.dSYM