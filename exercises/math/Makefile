CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror
LDLIBS += -lstdc++ -lm

math: math.o sfuns.o
	$(CXX) $(CXXFLAGS) math.o sfuns.o -o math 
	./math > Out.txt

math.o: math.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c math.cc -o math.o 

sfuns.o: sfuns.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o 

.PHONY: clean

clean:
	rm -rf Out.txt math math.o sfuns.o