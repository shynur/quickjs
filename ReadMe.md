# Introduction

QuickJSXX is a fork of QuickJS, which does **NOT modify any public APIs** of libquickjs (i.e., `quickjs.h` and `quickjs-libc.h`).

This project is intended to
- **restructure** the source code architecture of QuickJS;
- adopt **CMake** as its build system;
- provide a **C++ wrapper** (`target_link_libraries(yourTarget QuickJS::quickjsxx)`).

This makes the source code of QuickJS easier to read and learn,
and also enables it to be seamlessly integrated into C/C++ projects.
CPack can be used to generate various installation packages (RPM/DEB/etc.)

# INSTALL
## Use CMake (Recommended)

```bash
make clean

cmake -S src -B build -DCMAKE_BUILD_TYPE=Release
# Append '-DBUILD_SHARED_LIBS=ON' to build `libquickjs.so` instead of the static library.

cmake --build build --parallel
cmake --install build --prefix /usr/local
```

<details>
  <summary>The artifacts will be placed at</summary>
  <pre>
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
  </pre>
</details>

## Use ConanFile

(Use conan v1 latest.)

```bash
cd src
conan create . username/channel
```

When packaging, the test program will be built and run,
which may require the latest version of G++ or Clang compiler.
If the test fails, you may delete the `test_package` folder.

### How to Use

See <https://github.com/shynur/quickjs/wiki/Conan-Example>.
