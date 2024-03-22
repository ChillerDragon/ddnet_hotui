all: sample

CXX = clang++

CXX_FLAGS = -I../ddnet/src -I../ddnet/build/src -std=c++17

sample:	sample.cpp
	mkdir -p build
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC sample.cpp -o build/sample.o
	$(CXX) $(DEBUG) $(CXX_FLAGS) -shared -Wl,-soname,sample.so -o sample.so build/sample.o
	test -d ../ddnet/debug && cp *.so ../debug
	test -d ../ddnet/build && cp *.so ../build

debug: DEBUG=-g

debug: sample

clean:
	find . -type f \
		\( \
			-name '*.o' -o \
			-name '*.so' -o \
			-name '*.ghc' \
		\) \
		-exec rm '{}' \;

