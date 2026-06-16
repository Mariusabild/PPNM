CXXFLAGS += -Wall -Wextra -std=c++23 -O3

all: main timing.png
	cat Out.txt

main: main.cc matrix.h qr.h
	g++ $(CXXFLAGS) $< -o main
	./main > Out.txt

timing.png: out.times.data timing.gpi
	gnuplot timing.gpi

out.times.data: timing
	>$@
	for N in $$(seq 300 100 1000); do \
		time --format "$$N %e" --output $@ --append \
		./timing -size $$N 1>out 2>err ;\
	done

timing: timing.cc matrix.h qr.h
	g++ $(CXXFLAGS) $< -o timing

.PHONY: clean
clean:
	rm -f Out.txt main timing out.times.data timing.png out err fit.log

	