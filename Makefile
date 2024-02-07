all: sample

CXX = clang++

CXX_FLAGS = -I../ddnet/src -std=c++17

sample:	sample.cpp
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC sample.cpp -o sample.o
	$(CXX) $(DEBUG) $(CXX_FLAGS) -shared -Wl,-soname,sample.so -o sample.so sample.o
	test -d ../ddnet/debug && cp *.so ../debug
	test -d ../ddnet/build && cp *.so ../build

debug: DEBUG=-g

debug: sample

clean:
	rm *.o
	rm *.so
	rm *.gch
