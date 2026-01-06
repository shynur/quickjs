add_library(unicode)

target_sources(unicode
    PRIVATE
        libunicode.c
    PUBLIC
        FILE_SET HEADERS
        FILES libunicode.h
)

target_link_libraries(unicode
    PRIVATE
        cutils
)

install(
    TARGETS  unicode
    FILE_SET HEADERS
)
