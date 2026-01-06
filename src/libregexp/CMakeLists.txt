add_library(regexp OBJECT)

target_sources(regexp
    PRIVATE
        libregexp.c
    PUBLIC
        FILE_SET HEADERS
        #FILES libregexp.h
)

target_link_libraries(regexp
    PRIVATE
        cutils
        unicode
)

#[[ install(
    TARGETS  regexp
    FILE_SET HEADERS
) ]]

set_target_properties(regexp
    PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
)
