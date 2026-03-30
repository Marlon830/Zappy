cmake_minimum_required(VERSION 3.27)
include(FetchContent)

project(
    ZOAT
    VERSION     0.1
    DESCRIPTION "Zombie Outbreak Alert Terminal"
    LANGUAGES   C CXX
)

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 20)

set(ZOAT_DIR_ROOT       "${CMAKE_CURRENT_SOURCE_DIR}")
set(ZOAT_DIR_LIB        "${ZOAT_DIR_ROOT}/lib")
set(ZOAT_DIR_SERVER     "${ZOAT_DIR_ROOT}/server")
set(ZOAT_DIR_AI         "${ZOAT_DIR_ROOT}/ai")
set(ZOAT_DIR_GUI        "${ZOAT_DIR_ROOT}/gui")

add_subdirectory(${ZOAT_DIR_LIB})
add_subdirectory(${ZOAT_DIR_SERVER})
add_subdirectory(${ZOAT_DIR_AI})
add_subdirectory(${ZOAT_DIR_GUI})
