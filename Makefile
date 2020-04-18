.PHONY: all clean

all: build

clean:
	rm -r build

build: test_graphemesplitter.cpp graphemesplitter.cpp graphemesplitter.hpp
	mkdir -p build
	cd build && \
	cmake -g "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. && \
	cmake --build .