include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)

FetchContent_GetProperties(raylib)
if(NOT raylib_POPULATED)
  FetchContent_Populate(raylib)
  add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()
