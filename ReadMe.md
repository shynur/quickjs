# INSTALL

```bash
make clean

cmake -S src -B build
# Append '-DCMAKE_BUILD_TYPE=Release' for optimizations.
# Append '-DBUILD_SHARED_LIBS=ON' to build `libquickjs.so` instead of static library.

cmake --build build --parallel
cmake --install build --prefix /usr/local
```

The artifacts will be placed at

```
/usr/local
      |
      +-- bin
      |    |
      |    +-- qjs
      |    |
      |    +-- qjsc
      |
      +-- include
      |      |
      |      +-- quickjs.h
      |      |
      |      +-- quickjs-libc.h
      |
      +-- lib
           |
           +-- libquickjs.so or libquickjs.a
           |
           +-- cmake/QuickJS
```

You can use `find_package(QuickJS)` and `target_link_libraries(yourTarget QuickJS::quickjs)` in your CML.

# Use with ConanFile

See <https://github.com/shynur/quickjs/wiki/Conan-Example>
