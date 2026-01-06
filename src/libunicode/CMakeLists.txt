add_library(unicode OBJECT)

target_sources(unicode
    PRIVATE
        libunicode.c
    PUBLIC
        FILE_SET HEADERS
        #FILES libunicode.h
)

target_link_libraries(unicode
    PRIVATE
        cutils
)

#[[ install(
    TARGETS  unicode
    FILE_SET HEADERS
) ]]

set_target_properties(unicode
    PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
)
