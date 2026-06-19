CXXFLAGS += -Wall -Wextra -std=c++23 -O

# default parameters
rmax = 10
dr = 0.4

all: main wave.dat
	cat Out.txt

# compile program
main: main.cc matrix.h jacobi.h
	g++ $(CXXFLAGS) $< -o main

# generate wavefunction data
wave.dat: main
	./main -rmax $(rmax) -dr $(dr) > Out.txt


# dr convergence test
dr.dat: main
	rm -f dr.dat
	for d in 0.7 0.5 0.4 0.3 0.2; do \
		./main -rmax 10 -dr $$d | grep "Ground state energy" | awk '{print $$4}' | xargs printf "$$d %s\n" >> dr.dat ; \
	done


# rmax convergence test
rmax.dat: main
	rm -f rmax.dat
	for r in 5 7 10 12 15; do \
		./main -rmax $$r -dr 0.3 | grep "Ground state energy" | awk '{print $$4}' | xargs printf "$$r %s\n" >> rmax.dat ; \
	done

timing: timing.cc matrix.h jacobi.h
	g++ $(CXXFLAGS) $< -o $@

out.times.data: timing
	rm -f $@
	for N in $$(seq 20 20 300); do \
		/usr/bin/time -f "$$N %e" -ao $@ ./timing -size $$N ; \
	done

timing.png: out.times.data
	gnuplot timing.gpi

# plots
plot: wave.dat dr.dat rmax.dat timing.png
	gnuplot wave.gnuplot

# run everything
all: plot

.PHONY: clean
clean:
	rm -f main wave.dat dr.dat rmax.dat *.png Out.txt timing timing.dat out.times.data