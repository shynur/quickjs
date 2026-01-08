cmake_minimum_required(VERSION 3.23)
# ------------- project --------------
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" QuickJS_VERSION)
string(STRIP "${QuickJS_VERSION}" QuickJS_VERSION)
message(STATUS "QuickJS v${QuickJS_VERSION}")

project(QuickJS
    VERSION ${QuickJS_VERSION}
    LANGUAGES C # 无需 CXX, 因为 quickjsxx 是 header-only 库.
)
# ------------- stdlib ---------------
include(GNUInstallDirs)
include(CheckSourceCompiles)
include(CheckIPOSupported)
include(CMakePackageConfigHelpers)
include(CheckIncludeFiles)
#-------------- configuration --------------
add_compile_options(-fwrapv)

add_compile_definitions(
    _GNU_SOURCE
    CONFIG_VERSION=\"${PROJECT_VERSION}\"
)

if(MINGW)
    add_compile_definitions(
        __USE_MINGW_ANSI_STDIO
    )  # for standard snprintf behavior
endif()
# -------------- options --------------

# ------------- subdirectories --------------
add_subdirectory(list)
add_subdirectory(cutils)
add_subdirectory(dtoa)
add_subdirectory(libregexp)
add_subdirectory(libunicode)
add_subdirectory(quickjs)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qjs/")
    add_subdirectory(qjs)
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qjsc/")
    add_subdirectory(qjsc)
endif()
#add_subdirectory(run-test262)
add_subdirectory(quickjsxx)
# ------------- install ---------------
install(
    FILES cmake/QuickJSConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QuickJSConfigVersion.cmake
    COMPATIBILITY ExactVersion
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/QuickJSConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QuickJS
)
