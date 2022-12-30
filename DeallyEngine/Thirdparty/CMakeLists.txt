execute_process( COMMAND git submodule update --init --recursive )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)



  set( GLFW_STATIC OFF CACHE BOOL "Build the static GLFW library" )
  set( GLFW_SHARED ON CACHE BOOL "Build the shared GLFW library" )
  add_subdirectory( GLFW )

  set( glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library" )
  set( glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library" )
  set( glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library" )
  set( glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Build the multi context glew library" )

  add_subdirectory( glew )



INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/imgui/)

add_library (imgui SHARED ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp)

