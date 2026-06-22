CXXFLAGS += -Wall -Werror -std=c++23 -O

all: main timing timing.png

main: main.cc
	g++ $< $(CXXFLAGS) -o main
	./main > Out.txt
	cat Out.txt

timing: timing.cc matrix.h svd.h
	g++ $(CXXFLAGS) $< -o $@

out.times.data: timing
	rm -f $@
	for N in $$(seq 20 20 300); do \
		/usr/bin/time -f "$$N %e" -ao $@ ./timing -size $$N ; \
	done

timing.png: out.times.data
	gnuplot timing.gpi

.PHONY:clean

clean:
	rm main Out.txt
