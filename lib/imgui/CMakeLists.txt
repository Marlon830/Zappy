cmake_minimum_required(VERSION 3.20)
include(FetchContent)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY "https://github.com/ocornut/imgui"
	GIT_TAG master
)

FetchContent_MakeAvailable(imgui)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

FetchContent_GetProperties(imgui)
add_library(imgui STATIC
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui.h
	${imgui_SOURCE_DIR}/imstb_rectpack.h
	${imgui_SOURCE_DIR}/imstb_textedit.h
	${imgui_SOURCE_DIR}/imstb_truetype.h
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)
	
set(INSTALL_TARGETS imgui)
set(INSTALL_HEADERS ${imgui_SOURCE_DIR}/imgui.h ${imgui_SOURCE_DIR}/imconfig.h)

foreach(BACKEND glfw opengl3 sdl2 sdlrenderer2)
	set(NAME imgui_impl_${BACKEND})
	set(HEADER ${imgui_SOURCE_DIR}/backends/${NAME}.h)
	add_library(${NAME} STATIC ${imgui_SOURCE_DIR}/backends/${NAME}.cpp ${HEADER})
	target_link_libraries(${NAME} PUBLIC imgui)
	target_include_directories(${NAME} PUBLIC
	    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
	    $<INSTALL_INTERFACE:include>)
	LIST(APPEND INSTALL_TARGETS ${NAME})
	LIST(APPEND INSTALL_HEADERS ${HEADER})
endforeach()

target_link_libraries(imgui_impl_glfw PRIVATE glfw)
target_sources(imgui_impl_opengl3 PRIVATE ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h)
target_link_libraries(imgui_impl_opengl3 PRIVATE OpenGL::GL)
target_link_libraries(imgui_impl_sdl2 PRIVATE SDL2::SDL2)
target_link_libraries(imgui_impl_sdlrenderer2 PRIVATE SDL2::SDL2)

install(TARGETS ${INSTALL_TARGETS}
    EXPORT imgui-targets DESTINATION lib)
install(EXPORT imgui-targets
    FILE imgui-config.cmake
    NAMESPACE imgui::
    DESTINATION lib/cmake/imgui)
install(FILES ${INSTALL_HEADERS}
    DESTINATION include)
