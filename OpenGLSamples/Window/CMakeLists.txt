cmake_minimum_required(VERSION 3.9.1)

project(windows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

set(PROJECT_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/../libs")

if (EMSCRIPTEN)
  target_link_libraries(${PROJECT_NAME}  PUBLIC "-s USE_GLFW=3")
  target_link_libraries(${PROJECT_NAME}  PUBLIC "-s USE_WEBGL2=1")
  target_link_libraries(${PROJECT_NAME}  PUBLIC "-s WASM=1")

  # Copy the index.html file.
  foreach(file "index.html" "run_webassembly.py")
    configure_file(src/${file} ${file})
  endforeach(file)

  foreach(file "shader/shader.frag" "shader/shader.vert")
    configure_file(${file} ${file})
  endforeach(file)

  # Allow the directories /shader and /data to be fetched by the web browser.
  set_property(TARGET ${PROJECT_NAME}  APPEND_STRING PROPERTY LINK_FLAGS
    "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/shader/@/shader/")
  
else() # Not Web

  # glfw
  add_subdirectory(${CMAKE_SOURCE_DIR}/../thirdparty/glfw EXCLUDE_FROM_ALL)

  # glew
  add_definitions(-DGLEW_STATIC)
  add_subdirectory(${CMAKE_SOURCE_DIR}/../thirdparty/glew EXCLUDE_FROM_ALL)

endif()

# glm
add_subdirectory(${CMAKE_SOURCE_DIR}/../thirdparty/glm EXCLUDE_FROM_ALL)

# Executable
add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/main.cpp")
target_link_libraries(${PROJECT_NAME} PUBLIC
   glfw
   glew
   glm
   PRIVATE ${CMAKE_DL_LIBS})
   # CMAKE_DL_LIBS -> is the library libdl which helps to link dynamic
   # libraries. We need it in order to use GLAD.