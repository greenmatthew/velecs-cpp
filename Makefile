.PHONY: build-solution build-release

build-solution:
	if not exist bin mkdir solution
	cmake -S . -B solution -G "Visual Studio 17 2022"

build-release: build-solution
	cmake --build solution --config Release
