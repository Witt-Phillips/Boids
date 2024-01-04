CXX	 = g++



all: boid

boid: simulate.o boid.o vector.o
	${CXX} -o $@ $^

clean:
	${RM} boid *.0 *.dSYM