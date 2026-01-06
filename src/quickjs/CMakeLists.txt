add_library(quickjs)

target_sources(quickjs
    PRIVATE
        quickjs.c
        quickjs-libc.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            quickjs.h
            quickjs-libc.h
)

target_link_libraries(quickjs
    PRIVATE
        list
        cutils
        dtoa
        regexp
        unicode
    PUBLIC
        m
)

install(
    TARGETS  quickjs
    FILE_SET HEADERS
)

if(NOT WIN32)
    include(CheckSourceCompiles)
    check_source_compiles(C
        [[
            #include <unistd.h>
            int main() {closefrom(3);}
        ]]
        HAVE_CLOSEFROM
    )
    if(HAVE_CLOSEFROM)
        target_compile_definitions(quickjs
            PRIVATE
                HAVE_CLOSEFROM
        )
    endif()
endif()
