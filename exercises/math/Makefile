CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror
LDLIBS += -lstdc++ -lm

Out.txt: math
	./math > Out.txt

math: math.cc sfuns.cc sfuns.h
	$(CXX) math.cc sfuns.cc -o math

.PHONY: clean

clean:
	rm -rf Out.txt math sfuns