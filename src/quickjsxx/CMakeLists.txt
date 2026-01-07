add_library(quickjsxx INTERFACE)
add_library(QuickJS::quickjsxx ALIAS quickjsxx)

file(GLOB_RECURSE
    QUICKJSXX_HPP_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

target_sources(quickjsxx
    INTERFACE
        FILE_SET HEADERS
        FILES    ${QUICKJSXX_HPP_FILES}
)

target_link_libraries(quickjsxx
    INTERFACE
        quickjs
)

install(
    TARGETS quickjsxx
    FILE_SET HEADERS
)
