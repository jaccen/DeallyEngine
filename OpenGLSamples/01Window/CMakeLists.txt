cmake_minimum_required(VERSION 3.9.1)

project(ProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

set(PROJECT_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/../libs")

add_subdirectory(${CMAKE_SOURCE_DIR}/../thirdparty)
# Executable
add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/main.cpp")
target_link_libraries(${PROJECT_NAME} PUBLIC
   glad 
   ${SDL2_LIBRARIES} 
   imgui
   PRIVATE ${CMAKE_DL_LIBS})
   # CMAKE_DL_LIBS -> is the library libdl which helps to link dynamic
   # libraries. We need it in order to use GLAD.