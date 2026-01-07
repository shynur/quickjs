add_library(cutils OBJECT)

target_sources(cutils
    PRIVATE
        cutils.c
    PUBLIC
        FILE_SET HEADERS
)

if(BUILD_SHARED_LIBS)
    set_target_properties(cutils
        PROPERTIES
            POSITION_INDEPENDENT_CODE TRUE
    )
endif()
