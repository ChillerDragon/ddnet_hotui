all: sample main

CXX = clang++

CXX_FLAGS = -I../src -std=c++17

sample:	sample.cpp
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC sample.cpp -o sample.o
	$(CXX) $(DEBUG) $(CXX_FLAGS) -shared -Wl,-soname,sample.so -o sample.so sample.o
	test -d ../debug && cp *.so ../debug
	test -d ../build && cp *.so ../build

debug: DEBUG=-g

debug: sample main

main:		main.cpp
	$(CXX) $(DEBUG) main.cpp -o main -ldl $(CXX_FLAGS)

test: sample main
	LD_LIBRARY_PATH=. ./main

clean:
	rm *.o
	rm *.so
	rm *.gch
