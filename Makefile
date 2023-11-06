.PHONY: build-solution build-debug build-release

build-solution:
	@if not exist build mkdir build
	@cmake -S . -B build -G "Visual Studio 17 2022"

build-debug: build-solution
	@cmake --build build --config Debug

build-release: build-solution
	@cmake --build build --config Release
