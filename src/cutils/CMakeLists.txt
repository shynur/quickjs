add_library(cutils OBJECT)

target_sources(cutils
    PRIVATE
        cutils.c
    PUBLIC
        FILE_SET HEADERS
)

set_target_properties(cutils
    PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
)
