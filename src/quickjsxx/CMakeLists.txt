add_library(quickjsxx INTERFACE)
add_library(QuickJS::quickjsxx ALIAS quickjsxx)
# -------------- sources & properties --------------
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
# ------------- install --------------
install(
    TARGETS quickjsxx
    EXPORT QuickJSXXTargets
    FILE_SET HEADERS
)

install(
       EXPORT QuickJSXXTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
    NAMESPACE QuickJS::
)
