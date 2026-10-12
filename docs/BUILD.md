# Build Guide

Requirements: CMake 3.20+ and a C++23 compiler.

## Linux/macOS
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/forgearm_demo
```

## Windows
```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\forgearm_demo.exe
```

Build artifacts belong in `build/`, which is ignored by Git. Use a compiler with C++23 support.
