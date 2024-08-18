all: sample

DDNET_DIR = ../ddnet

CXX = clang++

CXX_FLAGS = -I$(DDNET_DIR)/src -I$(DDNET_DIR)/build/src -std=c++17

sample:	sample.cpp
	mkdir -p build
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC sample.cpp -o build/sample.o
	$(CXX) $(DEBUG) $(CXX_FLAGS) -shared -Wl,-soname,sample.so -o sample.so build/sample.o
	test -d $(DDNET_DIR)/debug && cp *.so ../debug || true
	test -d $(DDNET_DIR)/build && cp *.so ../build || true
	@COMPILE_JSON="$(shell find $(DDNET_DIR) -type f -name "compile_commands.json" -printf "%T@ %p\n" | sort -n | cut -d' ' -f 2- | tail -n 1)"; \
	[ "$$COMPILE_JSON" = "" ] || { cp "$$COMPILE_JSON" build; echo cp $$COMPILE_JSON build/; }

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

