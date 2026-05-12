CXXFLAGS = -Wall -Wextra -Werror - std=c++17 -O
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ - lm

hello: hello.cc                 
	c++ -o hello hello.cc 
	./hello > Out.txt  
clean:
	rm -f Out.txt hello