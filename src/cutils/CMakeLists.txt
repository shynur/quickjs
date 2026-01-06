add_library(cutils OBJECT)

target_sources(cutils
    PRIVATE
        cutils.c
    PUBLIC
        FILE_SET HEADERS
)
