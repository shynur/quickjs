cmake_minimum_required(VERSION 3.23)
project(QuickJS
    VERSION 0.26.0106
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
