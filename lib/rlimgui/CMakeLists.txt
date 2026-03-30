include(FetchContent)

FetchContent_Declare(
  rlimgui
  GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
  GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)
FetchContent_GetProperties(rlimgui)

add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
target_link_libraries(rlimgui raylib imgui)
message(STATUS "rlimgui_SOURCE_DIR: ${rlimgui_SOURCE_DIR}")
set(rlimgui_INCLUDE_DIRS ${rlimgui_SOURCE_DIR} CACHE INTERNAL "")