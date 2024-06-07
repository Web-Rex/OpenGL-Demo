init:
	rd /s /q build

init-config:
	cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=install-dir -DCMAKE_BUILD_TYPE=Debug

init-build:
	cmake --build build

init-install:
	cmake --target install

run:
	./build/src/3_0_lighting.exe