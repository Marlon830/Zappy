set(ZOAT_DIR_SERVER_SRC "${ZOAT_DIR_SERVER}/src")
set(ZOAT_DIR_SERVER_INC "${ZOAT_DIR_SERVER}/include")
set(ZOAT_HEXAGON_LIB "${ZOAT_DIR_LIB}/hexagon")
set(ZOAT_HEXAGON_LIB_INC "${ZOAT_HEXAGON_LIB}/include")

file(GLOB_RECURSE ZOAT_SERVER_SRC "${ZOAT_DIR_SERVER_SRC}/*.c" "${ZOAT_DIR_SERVER_INC}/*.h")

include_directories(${ZOAT_DIR_SERVER_INC} ${ZOAT_HEXAGON_LIB_INC})

add_executable(
    zappy_server
    ${ZOAT_SERVER_SRC}
)

set_target_properties(
    zappy_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ZOAT_DIR_ROOT}"
)

target_link_libraries(
    zappy_server
    hexagon
)
