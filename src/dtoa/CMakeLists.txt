add_library(dtoa OBJECT)

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
    PUBLIC
        m
)

#[[ install(
    TARGETS  dtoa
    FILE_SET HEADERS
) ]]

set_target_properties(dtoa
    PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
)
