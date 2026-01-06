cmake_minimum_required(VERSION 3.23)

file(READ "${CMAKE_SOURCE_DIR}/../Version.txt" QuickJS_VERSION)
string(STRIP "${QuickJS_VERSION}" QuickJS_VERSION)
message(STATUS "QuickJS v${QuickJS_VERSION}")

project(QuickJS
    VERSION ${QuickJS_VERSION}
    LANGUAGES C
)
#-------------- configuration --------------
add_compile_options(-fwrapv)

add_compile_definitions(
    _GNU_SOURCE
    CONFIG_VERSION=\"${PROJECT_VERSION}\"
)

if(MINGW)
    add_compile_definitions(
        __USE_MINGW_ANSI_STDIO
    )
endif()
# -------------- options --------------

# ------------- subdirectories --------------
add_subdirectory(cutils)
add_subdirectory(dtoa)
add_subdirectory(list)
add_subdirectory(libregexp)
add_subdirectory(libunicode)
add_subdirectory(quickjs)
add_subdirectory(qjs)
add_subdirectory(qjsc)
#add_subdirectory(run-test262)
