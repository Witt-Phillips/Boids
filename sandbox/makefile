CXX      = g++
CFLAGS   = -Wall -Wextra -O2
INCLUDES = -I/usr/include/GLFW -Iimgui -Iimgui/backends
LIBS     = -L/usr/lib/x86_64-linux-gnu -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

# ImGui source files
IMGUI_SOURCES = imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp

all: simulate boid-test

simulate: vector.o boid.o flock.o simulate.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${IMGUI_SOURCES} ${LIBS}

boid-test: vector.o boid.o flock.o boid-test.o
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ $^ ${IMGUI_SOURCES} ${LIBS}

clean:
	${RM} simulate boid-test *.o *.dSYM
