add_executable(qjsc)

target_sources(qjsc
    PRIVATE
        qjsc.c
)

target_link_libraries(qjsc
    PRIVATE
        quickjs
        cutils
)

install(
    TARGETS qjsc
)
