Out.txt: kommando
	./hello > Out.txt

kommando: test.cc
	g++ test.cc -o hello

.PHONY: clean

clean:
	rm -rf Out.txt hello