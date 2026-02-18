CXXFLAGS += -Wall -Werror -Wextra -std=c++23 -O
LDLIBS += -lstdc++ -lm

all: fig1.svg fig2.svg fig3.svg
	
generated.data: main
	./main > generated.data

main: main.cc

fig1.svg: fig1.gpi generated.data 
	gnuplot $<

fig2.svg: fig2.gpi generated.data
	gnuplot $<

fig3.svg: fig3.gpi generated.data
	gnuplot $<

.PHONY:clean

clean:
	rm -rf generated.data fig1.svg fig2.svg main
