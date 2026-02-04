CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror
LDLIBS += -lstdc++ -lm

Out.txt: math
	./math > Out.txt

math: math.cc sfuns.o
#	$(CXX) $(CXXFLAGS) math.cc sfuns.o -o math #BEMÆRK BEHØVES IKKE

sfuns.o: sfuns.cc sfuns.h
#	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o #BEMÆRK BEHØVES IKKE

.PHONY: clean

clean:
	rm -rf Out.txt math sfuns.o sfuns