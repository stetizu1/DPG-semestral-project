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
add_definitions(-D__WINDOWS__ -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)


# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add all files to executable.
add_executable(${NAME}
    src/main.cpp
    src/color/Color.cpp src/color/Color.h
    src/point/Point3d.cpp src/point/Point3d.h
    src/vector/Vector3d.cpp src/vector/Vector3d.h
    src/vector/Vector4d.cpp src/vector/Vector4d.h
    src/ray/Ray.cpp src/ray/Ray.h
    src/heightmap-reader/HeightMapReader.cpp src/heightmap-reader/HeightMapReader.h
    src/matrix/Matrix4d.cpp src/matrix/Matrix4d.h
    src/heightmap/HeightMap.cpp src/heightmap/HeightMap.h
    src/scene.cpp src/light/Light.cpp src/light/Light.h src/scene.h)

if (NOT GLUT_FOUND)
  find_library(GLUT_LIBRARIES
      NAMES freeglut
      PATHS
      exe/freeglut/lib
      DOC "The GLUT library"
      )
  find_path(GLUT_INCLUDE_DIR GL/glut.h
      exe/freeglut/include
      DOC "The directory where GL/glut.h resides"
      )
endif (NOT GLUT_FOUND)

find_library(CORONA_LIBRARIES
    NAMES corona
    PATHS
    exe/corona-1.0.2-vc7/lib
    DOC "The CORONA library"
    )
find_path(CORONA_INCLUDE_DIR corona.h
    exe/corona-1.0.2-vc7/include
    DOC "The directory where corona.h resides"
    )

# Add include directories.
include_directories(SYSTEM
    ${CORONA_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    )

# Link libraries.
target_link_libraries(${NAME} ${CORONA_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

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
