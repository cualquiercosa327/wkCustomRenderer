cmake_minimum_required(VERSION 3.17)
project(wkCustomRenderer
        VERSION "0.0.0.0"
        DESCRIPTION "Experimental OpenGL custom renderer for Worms Armageddon"
        )

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/hacklib-patternscanner)

set(POLYHOOK_BUILD_STATIC_RUNTIME)
add_subdirectory(lib/PolyHook_2_0)
include_directories(include include/nlohmann_json_release lib/hacklib-patternscanner lib/PolyHook_2_0 lib/PolyHook_2_0/capstone/include)
link_directories(lib)

if(NOT(NOGIT))
    set(PRE_CONFIGURE_FILE "cmake/git.cc.in")
    set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/gen/git.cc")
    include(cmake/git_watcher.cmake)

    add_library(git STATIC ${POST_CONFIGURE_FILE})
    target_include_directories(git PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} cmake)
    add_dependencies(git check_git)
    configure_file(cmake/git.h ${CMAKE_CURRENT_BINARY_DIR}/gen/git.h)
endif()

configure_file(resource.rc.in resource.rc)

configure_file(cmake/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/gen/version.h)
add_definitions(-DLIBRARY_EXPORTS)
add_definitions(-DGLEW_STATIC)
add_library(${PROJECT_NAME} SHARED
        src/dllmain.cpp
        src/Config.cpp src/Config.h
        src/WaLibc.cpp src/WaLibc.h
        src/DevConsole.cpp src/DevConsole.h
        src/Hooks.cpp src/Hooks.h
        src/BitmapImage.cpp src/BitmapImage.h
        src/W2App.cpp src/W2App.h
        src/Sprites.cpp src/Sprites.h
        src/DrawingQueue.cpp src/DrawingQueue.h
        src/Screen.cpp src/Screen.h
        src/Backend.cpp src/Backend.h
        src/Drawing.cpp src/Drawing.h
        src/Zoom.cpp src/Zoom.h
        src/Keyboard.cpp src/Keyboard.h
        src/Utils.cpp src/Utils.h
        src/Shaders.cpp src/Shaders.h
        src/Debugf.h
        ${CMAKE_CURRENT_BINARY_DIR}/resource.rc
)
add_dependencies(${PROJECT_NAME} PolyHook_2)

if(NOT(NOGIT))
    add_dependencies(${PROJECT_NAME} PolyHook_2)
    set_property(TARGET ${PROJECT_NAME} git PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)
set_property(TARGET ${PROJECT_NAME} hacklib-patternscanner PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_link_libraries(${PROJECT_NAME} hacklib-patternscanner PolyHook_2 version git glew32s opengl32)
