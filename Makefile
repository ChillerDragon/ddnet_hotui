all: sample

DDNET_DIR = ../ddnet

CXX = clang++

CXX_FLAGS = -I$(DDNET_DIR)/src -I$(DDNET_DIR)/build/src -std=c++17

sample:	sample.cpp
	mkdir -p build
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC sample.cpp -o build/sample.o
	$(CXX) $(DEBUG) $(CXX_FLAGS) -shared -Wl,-soname,sample.so -o sample.so build/sample.o
	test -d $(DDNET_DIR)/debug && cp *.so ../debug
	test -d $(DDNET_DIR)/build && cp *.so ../build

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

