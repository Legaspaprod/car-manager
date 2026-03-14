.PHONY: all build clean run debug release

all: build

build:
	mkdir -p build && cd build && cmake .. && make

run: build
	./build/CarManager

debug:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

release:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make

clean:
	rm -rf build

rebuild: clean build