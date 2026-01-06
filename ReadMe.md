```bash
make clean

cmake -S src -B build
# Append '-DCMAKE_BUILD_TYPE=Release' for optimizations
# Append '-DBUILD_SHARED_LIBS=ON' for shared libraries

cmake --build build
cmake --install build --prefix /usr/local
```

The interpreter for ECMAScript will be located at `/usr/local/bin/qjs`.
