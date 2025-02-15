all: conan build

.PHONY: conan
conan:
	conan install . --output-folder=build --build=missing

.PHONY: build
build:
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -Bbuild/build/Release -G "Unix Makefiles"
	cmake --build build/build/Release --parallel 8 --target cpp_victory --

.PHONY: clean
clean:
	rm -rf build
