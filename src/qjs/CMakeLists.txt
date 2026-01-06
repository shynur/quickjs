add_executable(qjs)

target_sources(qjs
    PRIVATE
        qjs.c
        repl.c
)

target_link_libraries(qjs
    PRIVATE
        quickjs
        cutils
)

add_custom_command(
    OUTPUT repl.c
    COMMAND qjsc -s -c -o repl.c -m ${CMAKE_CURRENT_SOURCE_DIR}/repl.js
    DEPENDS qjsc repl.js
    VERBATIM
)

install(
    TARGETS qjs
)
