CXXFLAGS += -Wall -Wextra -std=c++23 -O

main: main.cc matrix.h qr.h
	g++ $(CXXFLAGS) $< -o main
	./main

.PHONY: clean
clean:
	rm main