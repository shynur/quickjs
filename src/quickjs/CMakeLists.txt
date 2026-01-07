add_library(quickjs)
add_library(QuickJS::quickjs ALIAS quickjs)
# -------------- checks --------------
include(CheckSourceCompiles)

if(NOT WIN32)
    check_source_compiles(C
        [[
            #include <unistd.h>
            int main() {
                closefrom(3);
            }
        ]]
        HAVE_CLOSEFROM
    )
endif()
if(HAVE_CLOSEFROM)
    target_compile_definitions(quickjs
        PRIVATE
            HAVE_CLOSEFROM
    )
endif()
# -------------- sources & properties --------------
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
        pthread
)
if(NOT WIN32)
    target_link_libraries(quickjs
        PUBLIC
            dl
    )
endif()
# ------------- install --------------
install(
    TARGETS
        quickjs
        list cutils dtoa regexp unicode
    EXPORT QuickJSTargets
    FILE_SET HEADERS
)

include(GNUInstallDirs)

install(
       EXPORT QuickJSTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
    NAMESPACE QuickJS::
)

install(
    FILES cmake/QuickJSConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QuickJSConfigVersion.cmake
    COMPATIBILITY ExactVersion
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/QuickJSConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
)
