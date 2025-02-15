all: conan build

.PHONY: conan
conan:
	conan install . --output-folder=build --build=missing

.PHONY: build
build:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
	cmake --build build

.PHONY: clean
clean:
	rm -rf build
