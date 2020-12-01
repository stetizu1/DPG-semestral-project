# CMake standard
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)

# Project name.
set(NAME project)
project(${NAME})

# Find GLUT and OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT)

# Set general compiler flags.
if (WIN32)
  add_definitions(-D__WINDOWS__ -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
elseif (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -framework GLUT -std=c++20")
else () # linux
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
endif (WIN32)


# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add all files to executable.
add_executable(${NAME}
    src/main.cpp
    src/color/Color.cpp src/color/Color.h
    src/point/Point3d.cpp src/point/Point3d.h
    src/vector/Vector3d.cpp src/vector/Vector3d.h
    src/ray/Ray.cpp src/ray/Ray.h
    )

# Use freeglut on Windows.
if (WIN32)
  if (NOT GLUT_FOUND)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(GLUT_LIB_PATH exe/freeglut/lib/x64)
    else (CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(GLUT_LIB_PATH exe/freeglut/lib)
    endif (CMAKE_SIZEOF_VOID_P EQUAL 8)
    find_library(GLUT_LIBRARIES
        NAMES freeglut
        PATHS
        ${GLUT_LIB_PATH}
        DOC "The GLUT library"
        )
    find_path(GLUT_INCLUDE_DIR GL/glut.h
        exe/freeglut/include
        DOC "The directory where GL/glut.h resides"
        )
  endif (NOT GLUT_FOUND)
endif (WIN32)

# Add include directories.
set(SGL_INCLUDE_DIR ./sgl)
include_directories(SYSTEM
    ${SGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    )

# Link libraries.
if (WIN32)
  target_link_libraries(${NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
elseif (APPLE)
  target_link_libraries(${NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} pthread)
else ()
  target_link_libraries(${NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GL GLU pthread)
endif (WIN32)

# Set output directory.
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/exe")

# Properties.
set_target_properties(${NAME} PROPERTIES
    DEBUG_OUTPUT_NAME ${NAME}_d
    RELEASE_OUTPUT_NAME ${NAME}
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}
    )
