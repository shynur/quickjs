cmake_minimum_required(VERSION 3.23)
project(PackageTest
    LANGUAGES  CXX
)

message(STATUS
    "Using C++ Compiler: ${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options(--gcc-install-dir=/usr/lib/gcc/x86_64-linux-gnu/14)
endif()

add_executable(example)
target_sources(example
    PRIVATE
        src/main.cpp
        src/print_pkg_info.cpp
    PRIVATE
        FILE_SET  HEADERS
        BASE_DIRS include
)
target_link_libraries(example
    PRIVATE
        stdc++
        QuickJS::quickjsxx
)
if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL GNU)
    target_compile_options(example
        PRIVATE
            -std=c++26
    )
endif()

find_package(QuickJS CONFIG REQUIRED)
