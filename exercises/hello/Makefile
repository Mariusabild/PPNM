CXXFLAGS = -Wall -Wextra -Werror - std=c++17 -O
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ - lm

Out.txt : hello             
	./hello > Out.txt        
hello: hello.cc                 
	c++ -o hello hello.cc  
clean:
	rm -f Out.txt hello