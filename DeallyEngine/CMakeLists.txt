#
#  Author: jiaxiaobo
#

cmake_minimum_required(VERSION 3.1)

project (Engine)

# The engine executable
add_executable(Engine
Engine/src/Application.cpp
Engine/src/Application.cpp
Engine/src/MyApplication.cpp
Engine/src/MyApplication.cpp
Engine/src/glError.h
Engine/src/glError.cpp
Engine/src/main.cpp
Engine/src/Shader.h
Engine/src/Shader.cpp
)

if (EMSCRIPTEN)
  target_link_libraries(Engine PUBLIC "-s USE_GLFW=3")
  target_link_libraries(Engine PUBLIC "-s USE_WEBGL2=1")
  target_link_libraries(Engine PUBLIC "-s WASM=1")

  # Copy the index.html file.
  foreach(file "index.html" "run_webassembly.py")
    configure_file(src/${file} ${file})
  endforeach(file)

  foreach(file "shader/shader.frag" "shader/shader.vert")
    configure_file(${file} ${file})
  endforeach(file)

  # Allow the directories /shader and /data to be fetched by the web browser.
  set_property(TARGET Engine APPEND_STRING PROPERTY LINK_FLAGS
    "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/shader/@/shader/")
  
else() # Not Web

  # glfw
  add_subdirectory(Thirdparty/glfw EXCLUDE_FROM_ALL)
  target_link_libraries(Engine PRIVATE glfw)

  # glew
  add_definitions(-DGLEW_STATIC)
  add_subdirectory(Thirdparty/glew EXCLUDE_FROM_ALL)
  target_link_libraries(Engine PRIVATE libglew_static)

endif()

# glm
add_subdirectory(Thirdparty/glm EXCLUDE_FROM_ALL)
target_link_libraries(Engine PRIVATE glm)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/src/asset.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/Engine/src/asset.h
)
target_include_directories(Engine
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Engine/src
)


