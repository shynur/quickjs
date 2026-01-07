cmake_minimum_required(VERSION 3.23)
project(PackageTest CXX)

add_executable(example)
target_sources(example
    PRIVATE
        src/example.cpp
)
target_link_libraries(example
    PRIVATE
        QuickJS::quickjsxx
)

find_package(QuickJS CONFIG REQUIRED)
