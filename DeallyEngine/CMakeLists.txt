#
#  Author: jiaxiaobo
#

cmake_minimum_required(VERSION 3.1)

project (Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(cotire)
include(${CP_CMAKE_DIR}/macros.cmake)

IF (ANDROID)
  include(${CP_CMAKE_DIR}/android.cmake)
ENDIF ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(Thirdparty)

set ( GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/GLFW/include )
set ( GLFW_LIBRARY glfw3 )

set ( GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/glew/include )
set ( GLEW_LIBRARIES libglew_shared )

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/glm/ )

#set ( WHEREAMI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/whereami/src/ )
#set ( WHEREAMI_LIBRARY whereami )

set ( IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/imgui/ )
set ( IMGUI_LIBRARY imgui )

#set ( FRETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/freetype/ )
#set ( FRETYPE_LIBRARY freetype)
IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/ -s TOTAL_MEMORY=38000000 -s USE_SDL=2 -std=c++1y")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/")

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSEIF (ANDROID)
 add_definitions( -DGLES2=1 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

  set(ENGINE_LIBS
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++1y")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARY}
    ${GLEW_LIBRARIES}
    ${IMGUI_LIBRARY}
   # ${FRETYPE_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    #${FRETYPE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )

ENDIF ()
include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_subdirectory(editor)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)

