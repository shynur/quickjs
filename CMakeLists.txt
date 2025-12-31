cmake_minimum_required(VERSION 3.23)
project(QuickJS
    VERSION 0.25.1231
    LANGUAGES C
)

#------- Configuration --------
add_compile_options(-fwrapv)
add_compile_definitions(CONFIG_VERSION=\"${PROJECT_VERSION}\")
add_compile_definitions(_GNU_SOURCE)

# ------- libquickjs -------------
add_library(quickjs)
target_sources(quickjs
    PRIVATE
        quickjs.c
        quickjs-libc.c
    PUBLIC
        FILE_SET HEADERS
        FILES quickjs.h
)
target_link_libraries(quickjs
    PRIVATE
        cutils
        dtoa
        regexp
        unicode
    INTERFACE
        m
)

# --------- executables ---------
add_executable(qjsc)
target_sources(qjsc
    PRIVATE
        qjsc.c
)
target_link_libraries(qjsc
    PRIVATE
        quickjs
        cutils
)

add_executable(qjs)
target_sources(qjs
    PRIVATE
        qjs.c
        repl.c
)
target_link_libraries(qjs
    PRIVATE
        quickjs
        cutils
)

# --------- misc ---------
add_library(cutils)
target_sources(cutils
    PRIVATE
        cutils.c
    PUBLIC
        FILE_SET HEADERS
        FILES    cutils.h
)

add_custom_command(
    OUTPUT repl.c
    COMMAND qjsc -s -c -o repl.c -m ${CMAKE_SOURCE_DIR}/repl.js
    DEPENDS qjsc repl.js
    VERBATIM
)

# --------- sub-projects listed on https://bellard.org/quickjs/ ---------
add_library(dtoa)
target_sources(dtoa
    PRIVATE
        dtoa.c
    PUBLIC
        FILE_SET HEADERS
        FILES    dtoa.h
)
target_link_libraries(dtoa
    PRIVATE
        cutils
    INTERFACE
        m
)

add_library(regexp)
target_sources(regexp
    PRIVATE
        libregexp.c
    PUBLIC
        FILE_SET HEADERS
        FILES libregexp.h
)
target_link_libraries(regexp PRIVATE cutils unicode)

add_library(unicode)
target_sources(unicode
    PRIVATE
        libunicode.c
    INTERFACE
        FILE_SET HEADERS
        FILES libunicode.h
)
target_link_libraries(unicode PRIVATE cutils)
